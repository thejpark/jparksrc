#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <chrono>

namespace PITCH_CBOE {
namespace MESSAGE {
    constexpr int PREFIX_LEN = 1; // Prefix 'S' in the message
namespace ADD_ORDER {
enum FORMAT {
    TIME_STAMP_OFS = PREFIX_LEN,
    TIME_STAMP_LEN = 8,
    MESSAGE_TYPE_OFS = TIME_STAMP_OFS + TIME_STAMP_LEN,
    MESSAGE_TYPE_LEN = 1,
    ORDER_ID_OFS = MESSAGE_TYPE_OFS + MESSAGE_TYPE_LEN,
    ORDER_ID_LEN = 12,
    SIDE_INDICATOR_OFS = ORDER_ID_OFS + ORDER_ID_LEN,
    SIDE_INDICATOR_LEN = 1,
    SHARES_OFS = SIDE_INDICATOR_OFS + SIDE_INDICATOR_LEN,
    SHARES_LEN = 6,
    SYMBOL_OFS = SHARES_OFS + SHARES_LEN,
    SYMBOL_LEN = 6
};
constexpr char TYPE = 'A';
}

namespace ORDER_EXECUTED {
enum FORMAT : int {
    TIME_STAMP_OFS = PREFIX_LEN,
    TIME_STAMP_LEN = 8,
    MESSAGE_TYPE_OFS = TIME_STAMP_OFS + TIME_STAMP_LEN,
    MESSAGE_TYPE_LEN = 1,
    ORDER_ID_OFS = MESSAGE_TYPE_OFS + MESSAGE_TYPE_LEN,
    ORDER_ID_LEN = 12,
    SHARES_OFS = ORDER_ID_OFS + ORDER_ID_LEN,
    SHARES_LEN = 6
};
constexpr char TYPE = 'E';
}

namespace TRADE {
enum FORMAT : int {
    TIME_STAMP_OFS = PREFIX_LEN,
    TIME_STAMP_LEN = 8,
    MESSAGE_TYPE_OFS = TIME_STAMP_OFS + TIME_STAMP_LEN,
    MESSAGE_TYPE_LEN = 1,
    ORDER_ID_OFS = MESSAGE_TYPE_OFS + MESSAGE_TYPE_LEN,
    ORDER_ID_LEN = 12,
    SIDE_INDICATOR_OFS = ORDER_ID_OFS + ORDER_ID_LEN,
    SIDE_INDICATOR_LEN = 1,
    SHARES_OFS = SIDE_INDICATOR_OFS + SIDE_INDICATOR_LEN,
    SHARES_LEN = 6,
    SYMBOL_OFS = SHARES_OFS + SHARES_LEN,
    SYMBOL_LEN = 6
};
constexpr char TYPE = 'P';
}
} // namespace MESSAGE

// PITCH message wrapper interface.
// The user should call HasNext() and Next() method call to get the next message.

class MessageInterface {
public:
     ~MessageInterface() {}
    virtual bool HasNext() = 0;
    virtual void Next() = 0;
    virtual char Type() = 0;
    virtual std::string OrderId() = 0;
    virtual std::string Symbol() = 0;
    virtual int Share() = 0;
};

class Message : public MessageInterface {
private:
    // The input stream to read the message from.
    std::istream& mIn;
    // current message instance.
    std::string mMessage;
    using ADD = PITCH_CBOE::MESSAGE::ADD_ORDER::FORMAT;
    using EXE = PITCH_CBOE::MESSAGE::ORDER_EXECUTED::FORMAT;
    using TRD = PITCH_CBOE::MESSAGE::TRADE::FORMAT;

public:
    Message(std::istream& in) : mIn(in) {
    }
    bool HasNext() override {
        return std::getline(mIn, mMessage).good();
    }

    void Next() override {
        // do nothing at the moment.
    }

    char Type() override {
        // All message has same offset for the message type.
        return mMessage[ADD::MESSAGE_TYPE_OFS];
    }

    // return order id of the message.
    std::string OrderId() override {
        if (mMessage[ADD::MESSAGE_TYPE_OFS] == 'A') {
            return mMessage.substr(ADD::ORDER_ID_OFS, ADD::ORDER_ID_LEN);
        } else {
            return mMessage.substr(EXE::ORDER_ID_OFS, EXE::ORDER_ID_LEN);
        }
    }

    // return the symbol of the message.
    std::string Symbol() override {
        if (mMessage[ADD::MESSAGE_TYPE_OFS] == 'A') {
            return mMessage.substr(ADD::SYMBOL_OFS, ADD::SYMBOL_LEN);
        } else {
            return mMessage.substr(TRD::SYMBOL_OFS, TRD::SYMBOL_LEN);
        }
    }

    // return executed or traded shares.
    int Share() override {
        if (mMessage[ADD::MESSAGE_TYPE_OFS] == 'P') {
            return std::stoi(mMessage.substr(TRD::SHARES_OFS, TRD::SHARES_LEN));
        } else {
            return std::stoi(mMessage.substr(EXE::SHARES_OFS, EXE::SHARES_LEN));
        }
    }
};

class Solution {
private:
    // a map from order id to symbol name
    std::unordered_map<std::string, std::string> order_to_symbol;
    // for each symbol, the trade volume
    std::unordered_map<std::string, int> symbol_trade_volume;
    // message wrapper
    MessageInterface& mMsg;

public:
Solution(MessageInterface& message) : mMsg(message) {
}

std::vector<std::pair<std::string, int>>  CollectTopK(std::istream& in, int k) {
    namespace ADD_ORDER = PITCH_CBOE::MESSAGE::ADD_ORDER;
    namespace ORDER_EXECUTED = PITCH_CBOE::MESSAGE::ORDER_EXECUTED;
    namespace TRADE = PITCH_CBOE::MESSAGE::TRADE;
    // step 1: Compute the volume of each symbol, and store it in the symbol_trade_volume.
    while (mMsg.HasNext())
    {
      mMsg.Next();

      switch (mMsg.Type()) {
      case ADD_ORDER::TYPE:
        order_to_symbol[mMsg.OrderId()] = mMsg.Symbol();
        break;

      case TRADE::TYPE:
        symbol_trade_volume[mMsg.Symbol()] += mMsg.Share();
        break;

      case ORDER_EXECUTED::TYPE:
        {
          const std::string& symbol = order_to_symbol[mMsg.OrderId()];
          symbol_trade_volume[symbol] += mMsg.Share();
        }
        break;

      case 'X':
      default:
        // not handled in this coding test.
        break;
      }
    }

    using elem = std::pair<std::string, int>;
    auto comp = [](const elem &a, const elem& b) {
        return a.second > b.second;
    };

    // step 2: Partition the symbols using std::nth_element so that first k elements
    // are the top k. Time complexity is O(n).
    // Altinatively, implemented and tested with the minimum heap implementation
    // with the heap size of k (in this case, 10), but std::nth_element is slightly faster.
    // The time complexity for min heap is O(n logk) where k is 10, so the time complexity is almost O(n).
    // For optimisation, only considered adding to heap if the new element is larger than the top element.
    #if 1
    std::vector<elem> result{symbol_trade_volume.begin(), symbol_trade_volume.end()};
    if (result.size() > k) {
      std::nth_element(result.begin(), result.begin() + k - 1, result.end(), comp);
      result.resize(k);
    }

    // Then sort the k elements based on the volume size. Skip this if we do not want the result sorted.
    sort(result.begin(), result.end(), comp);
    return result;
    // Tested with the minimum heap implementation below, and this one is slightly faster.

     #else
    // use min heap to store top k. The size of heap is k where k is 10.
    // Time complexity is O(n logk) where k is 10, so the time complexity is O(n).
    std::priority_queue<elem, std::vector<elem>, decltype(comp)> min_heap(comp);
    for (auto& [symbol, size] : symbol_trade_volume) {
        if (min_heap.size() < k) {
            min_heap.push({symbol, size});
        } else {
            // if the size of heap is 10, then the top element is the smallest one.
            // For optimisation, only consider adding to heap if the new element is larger than the top element.
            if (min_heap.top().second < size) {
                min_heap.pop();
                min_heap.push({symbol, size});
            }
        }
    }
    // take top k out of min heap
    std::vector<elem> result;
    while (!min_heap.empty()) {
        result.push_back(min_heap.top());
        min_heap.pop();
    }
    reverse(result.begin(), result.end());
    return result;
    #endif
}
};

} // namespace PITCH_CBOE

int main() {
    std::ios_base::sync_with_stdio(false);
    // std::cin.tie(NULL);
    // std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    PITCH_CBOE::Message message(std::cin);
    PITCH_CBOE::Solution sol(message);
    auto result = sol.CollectTopK(std::cin, 10);

    // print top k from result, biggest to smallest.
    std::stringstream ss;
    for (auto &[symbol, size] : result) {
        ss << symbol << " " << size << std::endl;
    }

    std::cout << ss.str();
    // std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    // std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
}

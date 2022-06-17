#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <unordered_map>
#include <sstream>
#include <fstream>
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
}
} // namespace MESSAGE

// PITCH message wrapper
class Message {
private:
    std::istream& mIn;
    std::string mMessage;
    using ADD = PITCH_CBOE::MESSAGE::ADD_ORDER::FORMAT;
    using EXE = PITCH_CBOE::MESSAGE::ORDER_EXECUTED::FORMAT;
    using TRD = PITCH_CBOE::MESSAGE::TRADE::FORMAT;

public:
    Message(std::istream& in) : mIn(in) {
    }
    bool HasNext() {
        return std::getline(mIn, mMessage).good();
    }

    void Next() {
    }

    char Type() {
        return mMessage[ADD::MESSAGE_TYPE_OFS];
    }

    std::string OrderId() {
        if (mMessage[ADD::MESSAGE_TYPE_OFS] == 'A') {
            return mMessage.substr(ADD::ORDER_ID_OFS, ADD::ORDER_ID_LEN);
        } else {
            return mMessage.substr(EXE::ORDER_ID_OFS, EXE::ORDER_ID_LEN);
        }
    }

    std::string Symbol() {
        if (mMessage[ADD::MESSAGE_TYPE_OFS] == 'A') {
            return mMessage.substr(ADD::SYMBOL_OFS, ADD::SYMBOL_LEN);
        } else {
            return mMessage.substr(TRD::SYMBOL_OFS, TRD::SYMBOL_LEN);
        }
    }

    int Share() {
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

public:
std::vector<std::pair<std::string, int>>  CollectTopK(std::istream& in, int k) {
    Message message(in);

    // compute the volume of each symbol and store in a map symbol_trade_volume.
    while (message.HasNext())
    {
      message.Next();

      switch (message.Type()) {
      case 'A':
        // order added
        order_to_symbol[message.OrderId()] = message.Symbol();
        break;

      case 'P':
        // trade
        symbol_trade_volume[message.Symbol()] += message.Share();
        break;

      case 'E':
        // order executed
        {
          const std::string& symbol = order_to_symbol[message.OrderId()];
          symbol_trade_volume[symbol] += message.Share();
        }
        break;

      case 'X':
      default:
        break;
      }
    }

    using elem = std::pair<std::string, int>;
    auto comp = [](const elem &a, const elem& b) {
        return a.second > b.second;
    };
     #if 1
    // Partition the symbols so that first k elements are the top k. O(n).
    std::vector<elem> result{symbol_trade_volume.begin(), symbol_trade_volume.end()};
    if (result.size() > k) {
      std::nth_element(result.begin(), result.begin() + k - 1, result.end(), comp);
      result.resize(k);
    }

    // Then sort based on the volume size.
    sort(result.begin(), result.end(), comp);
    return result;
    // Tested with the minimum heap implementation below, and this one is slightly faster.

     #else
    // use min heap to store top k. The size of heap is k where k is 10.
    // Time complexity is O(n logk) where k is 10, so it is also O(n).
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
    std::cin.tie(NULL);
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    PITCH_CBOE::Solution sol;
    // auto fin = std::ifstream("pitch_example_data.txt");
    auto result = sol.CollectTopK(std::cin, 10);

    // print top k from result, biggest to smallest.
    std::stringstream ss;
    for (auto &[symbol, size] : result) {
        ss << symbol << " " << size << std::endl;
    }

    std::cout << ss.str();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
}

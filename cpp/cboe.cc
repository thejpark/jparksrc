#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <algorithm>
// #include <chrono>

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
enum FORMAT {
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
constexpr char TYPE = 'P';
}

namespace CANCEL_ORDER {
enum FORMAT {
    TIME_STAMP_OFS = PREFIX_LEN,
    TIME_STAMP_LEN = 8,
    MESSAGE_TYPE_OFS = TIME_STAMP_OFS + TIME_STAMP_LEN,
    MESSAGE_TYPE_LEN = 1,
    ORDER_ID_OFS = MESSAGE_TYPE_OFS + MESSAGE_TYPE_LEN,
    ORDER_ID_LEN = 12,
    SHARES_OFS = ORDER_ID_OFS + ORDER_ID_LEN,
    SHARES_LEN = 6,
};
constexpr char TYPE = 'X';
}

} // namespace MESSAGE

// PITCH message wrapper base, introduced for dependency injection (instead of using interface class).
// The user should call Next() method to get the next message.
template<typename Derived>
class MessageBase {
public:
    bool Next() { return (static_cast<Derived*>(this))->Next(); }
    char Type() { return (static_cast<Derived*>(this))->Type(); };
    std::string OrderId(int ofs) { return (static_cast<Derived*>(this))->OrderId(ofs); };
    std::string Symbol(int ofs) { return (static_cast<Derived*>(this))->Symbol(ofs); };
    int Share(int ofs) { return (static_cast<Derived*>(this))->Share(ofs); };
};

class Message : public MessageBase<Message> {
private:
    // The input stream to read the message from.
    std::istream& mIn;
    // current message instance.
    std::string mMessage;

public:
    Message(std::istream& in) : mIn(in) {
    }
    bool Next() {
        return std::getline(mIn, mMessage).good();
    }

    char Type() {
        // All messages have the same offset for the message type.
        return mMessage[PITCH_CBOE::MESSAGE::ADD_ORDER::FORMAT::MESSAGE_TYPE_OFS];
    }

    // return order id of the message.
    std::string OrderId(int ofs) {
        // All messages have the same order id length.
        return mMessage.substr(ofs, PITCH_CBOE::MESSAGE::ADD_ORDER::FORMAT::ORDER_ID_LEN);
    }

    // return the symbol of the message.
    std::string Symbol(int ofs) {
        // All messages have the same symbol length.
        return mMessage.substr(ofs, PITCH_CBOE::MESSAGE::ADD_ORDER::FORMAT::SYMBOL_LEN);
    }

    // return executed or traded shares.
    int Share(int ofs) {
        // All messages have the same share length.
        return std::stoi(mMessage.substr(ofs, PITCH_CBOE::MESSAGE::ADD_ORDER::FORMAT::SHARES_LEN));
    }
};

// T must be derived from MessageBase. For testing, need Mock class for the message.
template<typename T>
class Solution {
private:
    // message wrapper
    MessageBase<T>& mMsg;
    // a map from order id to the pair of (symbol name, share)
    std::unordered_map<std::string, std::pair<std::string, int>> order_to_symbol_share;
    // for each symbol, the trade volume
    std::unordered_map<std::string, int> symbol_trade_volume;

    using Elem = std::pair<std::string, int>;

public:
Solution(MessageBase<T>& message) : mMsg(message) {
}

std::vector<Elem>  CollectTopK(int k) {
    // step 1: Compute the volume of each symbol, and store it in the symbol_trade_volume.
    while (mMsg.Next())
    {
      switch (mMsg.Type()) {
      case PITCH_CBOE::MESSAGE::ADD_ORDER::TYPE: AddOrder();
        break;
      case PITCH_CBOE::MESSAGE::TRADE::TYPE: Trade();
        break;
      case PITCH_CBOE::MESSAGE::ORDER_EXECUTED::TYPE: Execute();
        break;
      case PITCH_CBOE::MESSAGE::CANCEL_ORDER::TYPE: CancelOrder();
        break;

      default:
        // not handled in this coding test.
        break;
     }
    }

    // step 2: Find the top k elements in the symbol_trade_volume.
    return TopK(k, symbol_trade_volume);
}

private:
std::vector<Elem> TopK(int k, const std::unordered_map<std::string, int>& symbol_trade_volume) {
    auto comp = [](const Elem &a, const Elem& b) {
        return a.second > b.second;
    };

    // Partition the symbols using std::nth_element so that first k elements
    // are the top k. Time complexity is O(n).
    // As an altinative, implemented and tested with the minimum heap implementation
    // with the heap size of k (in this case, 10, so time complexity is O(n) as well),
    // but std::nth_element is slightly little bit faster, so I choosed std::nth_element.
    std::vector<Elem> result{symbol_trade_volume.begin(), symbol_trade_volume.end()};
    if (result.size() > k) {
      std::nth_element(result.begin(), result.begin() + k - 1, result.end(), comp);
      result.resize(k);
    }

    // Then sort the k elements based on the volume size. Skip this if we do not want the result sorted.
    sort(result.begin(), result.end(), comp);
    return result;
}

void AddOrder() {
    using ADD = PITCH_CBOE::MESSAGE::ADD_ORDER::FORMAT;
    order_to_symbol_share[mMsg.OrderId(ADD::ORDER_ID_OFS)] =
        { mMsg.Symbol(ADD::SYMBOL_OFS), mMsg.Share(ADD::SHARES_OFS) };
}

void Trade() {
    using TRD = PITCH_CBOE::MESSAGE::TRADE::FORMAT;
    symbol_trade_volume[mMsg.Symbol(TRD::SYMBOL_OFS)] += mMsg.Share(TRD::SHARES_OFS);
}

void Execute() {
    using EXE = PITCH_CBOE::MESSAGE::ORDER_EXECUTED::FORMAT;
    const auto order_id = mMsg.OrderId(EXE::ORDER_ID_OFS);
    int executed_share = mMsg.Share(EXE::SHARES_OFS);
    auto& [symbol, share] = order_to_symbol_share[order_id];
    symbol_trade_volume[symbol] += executed_share;
    share -= executed_share;
    // if the remaining share is 0, remove the order from the map.
    if (share == 0) {
      order_to_symbol_share.erase(order_id);
    }
}

void CancelOrder() {
    using CCL = PITCH_CBOE::MESSAGE::CANCEL_ORDER::FORMAT;
    const auto order_id = mMsg.OrderId(CCL::ORDER_ID_OFS);
    int cancelled_share = mMsg.Share(CCL::SHARES_OFS);
    auto& [_, share] = order_to_symbol_share[order_id];
    share -= cancelled_share;
    // if the remaining share is 0, remove the order from the map.
    if (share == 0) {
      order_to_symbol_share.erase(order_id);
    }
}

};

} // namespace PITCH_CBOE

int main() {
    std::ios_base::sync_with_stdio(false);
    // std::cin.tie(NULL);
    // std::ifstream is("example_data.txt");
    PITCH_CBOE::Message message(std::cin);
    PITCH_CBOE::Solution<PITCH_CBOE::Message> sol(message);
    auto result = sol.CollectTopK(10);

    // print top k from result, biggest to smallest.
    for (const auto &[symbol, size] : result) {
        std::cout << symbol << " " << size << std::endl;
    }
}

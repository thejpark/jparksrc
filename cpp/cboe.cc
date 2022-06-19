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
    TIME_STAMP = PREFIX_LEN,
    TIME_STAMP_LEN = 8,
    MESSAGE_TYPE = TIME_STAMP + TIME_STAMP_LEN,
    MESSAGE_TYPE_LEN = 1,
    ORDER_ID = MESSAGE_TYPE + MESSAGE_TYPE_LEN,
    ORDER_ID_LEN = 12,
    SIDE_INDICATOR = ORDER_ID + ORDER_ID_LEN,
    SIDE_INDICATOR_LEN = 1,
    SHARES = SIDE_INDICATOR + SIDE_INDICATOR_LEN,
    SHARES_LEN = 6,
    SYMBOL = SHARES + SHARES_LEN,
    SYMBOL_LEN = 6
};
constexpr char TYPE = 'A';
} // namespace ADD_ORDER

namespace ORDER_EXECUTED {
enum FORMAT {
    TIME_STAMP = PREFIX_LEN,
    TIME_STAMP_LEN = 8,
    MESSAGE_TYPE = TIME_STAMP + TIME_STAMP_LEN,
    MESSAGE_TYPE_LEN = 1,
    ORDER_ID = MESSAGE_TYPE + MESSAGE_TYPE_LEN,
    ORDER_ID_LEN = 12,
    SHARES = ORDER_ID + ORDER_ID_LEN,
    SHARES_LEN = 6
};
constexpr char TYPE = 'E';
} // namespace ORDER_EXECUTED

namespace TRADE {
enum FORMAT {
    TIME_STAMP = PREFIX_LEN,
    TIME_STAMP_LEN = 8,
    MESSAGE_TYPE = TIME_STAMP + TIME_STAMP_LEN,
    MESSAGE_TYPE_LEN = 1,
    ORDER_ID = MESSAGE_TYPE + MESSAGE_TYPE_LEN,
    ORDER_ID_LEN = 12,
    SIDE_INDICATOR = ORDER_ID + ORDER_ID_LEN,
    SIDE_INDICATOR_LEN = 1,
    SHARES = SIDE_INDICATOR + SIDE_INDICATOR_LEN,
    SHARES_LEN = 6,
    SYMBOL = SHARES + SHARES_LEN,
    SYMBOL_LEN = 6
};
constexpr char TYPE = 'P';
} // namespace TRADE

namespace CANCEL_ORDER {
enum FORMAT {
    TIME_STAMP = PREFIX_LEN,
    TIME_STAMP_LEN = 8,
    MESSAGE_TYPE = TIME_STAMP + TIME_STAMP_LEN,
    MESSAGE_TYPE_LEN = 1,
    ORDER_ID = MESSAGE_TYPE + MESSAGE_TYPE_LEN,
    ORDER_ID_LEN = 12,
    SHARES = ORDER_ID + ORDER_ID_LEN,
    SHARES_LEN = 6,
};
constexpr char TYPE = 'X';
} // namespace CANCEL_ORDER

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
}; // class MessageBase

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
        return mMessage[PITCH_CBOE::MESSAGE::ADD_ORDER::FORMAT::MESSAGE_TYPE];
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
}; // class Message


// T must be derived from MessageBase. For testing, need Mock class for the message.
template<typename T>
class Solution {
private:
    // message wrapper
    MessageBase<T>& mMsg;
    // a map from order id to the pair of (symbol name, share)
    std::unordered_map<std::string, std::pair<std::string, int>> mOrderToSymbolShare;
    // for each symbol, the trade volume
    std::unordered_map<std::string, int> mSymbolTradeVolume;

    using Elem = std::pair<std::string, int>;

public:
Solution(MessageBase<T>& message) : mMsg(message) {}

std::vector<Elem>  CollectTopK(int k) {
    // step 1: Compute the volume of each symbol, and store it in the mSymbolTradeVolume.
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

    // step 2: Find the top k elements in the mSymbolTradeVolume.
    return TopK(k);
}

private:
std::vector<Elem> TopK(int k) {
    auto comp = [](const Elem &a, const Elem& b) {
        return a.second > b.second;
    };

    std::vector<Elem> result{mSymbolTradeVolume.begin(), mSymbolTradeVolume.end()};

    if (result.size() > k) {
        std::partial_sort(result.begin(), result.begin() + k, result.end(), comp);
        result.resize(k);
    } else {
        sort(result.begin(), result.end(), comp);
    }

    return result;
}

void AddOrder() {
    using ADD = PITCH_CBOE::MESSAGE::ADD_ORDER::FORMAT;
    mOrderToSymbolShare[mMsg.OrderId(ADD::ORDER_ID)] =
        { mMsg.Symbol(ADD::SYMBOL), mMsg.Share(ADD::SHARES) };
}

void Trade() {
    using TRD = PITCH_CBOE::MESSAGE::TRADE::FORMAT;
    mSymbolTradeVolume[mMsg.Symbol(TRD::SYMBOL)] += mMsg.Share(TRD::SHARES);
}

void Execute() {
    using EXE = PITCH_CBOE::MESSAGE::ORDER_EXECUTED::FORMAT;
    const auto order_id = mMsg.OrderId(EXE::ORDER_ID);
    int executed_share = mMsg.Share(EXE::SHARES);
    auto& [symbol, share] = mOrderToSymbolShare[order_id];
    mSymbolTradeVolume[symbol] += executed_share;
    share -= executed_share;
    // if the remaining share is 0, remove the order from the map.
    if (share == 0) {
      mOrderToSymbolShare.erase(order_id);
    }
}

void CancelOrder() {
    using CCL = PITCH_CBOE::MESSAGE::CANCEL_ORDER::FORMAT;
    const auto order_id = mMsg.OrderId(CCL::ORDER_ID);
    int cancelled_share = mMsg.Share(CCL::SHARES);
    auto& [_, share] = mOrderToSymbolShare[order_id];
    share -= cancelled_share;
    // if the remaining share is 0, remove the order from the map.
    if (share == 0) {
      mOrderToSymbolShare.erase(order_id);
    }
}

}; // class Solution

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

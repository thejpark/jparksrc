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
} // namespace MESSAGE

// PITCH message wrapper base, introduced for dependency injection (instead of using interface class).
// The user should call Next() method call to get the next message.
template<typename Derived>
class MessageBase {
public:
    bool Next() { return (static_cast<Derived*>(this))->Next(); }
    char Type() { return (static_cast<Derived*>(this))->Type(); };
    std::string OrderId() { return (static_cast<Derived*>(this))->OrderId(); };
    std::string Symbol() { return (static_cast<Derived*>(this))->Symbol(); };
    int Share() { return (static_cast<Derived*>(this))->Share(); };
};

class Message : public MessageBase<Message> {
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
    bool Next() {
        return std::getline(mIn, mMessage).good();
    }

    char Type() {
        // All messages have the same offset for the message type.
        return mMessage[ADD::MESSAGE_TYPE_OFS];
    }

    // return order id of the message.
    std::string OrderId() {
        if (Type() == PITCH_CBOE::MESSAGE::ADD_ORDER::TYPE) {
            return mMessage.substr(ADD::ORDER_ID_OFS, ADD::ORDER_ID_LEN);
        } else {
            return mMessage.substr(EXE::ORDER_ID_OFS, EXE::ORDER_ID_LEN);
        }
    }

    // return the symbol of the message.
    std::string Symbol() {
        if (Type() == PITCH_CBOE::MESSAGE::ADD_ORDER::TYPE) {
            return mMessage.substr(ADD::SYMBOL_OFS, ADD::SYMBOL_LEN);
        } else {
            return mMessage.substr(TRD::SYMBOL_OFS, TRD::SYMBOL_LEN);
        }
    }

    // return executed or traded shares.
    int Share() {
        if (Type() == PITCH_CBOE::MESSAGE::TRADE::TYPE) {
            return std::stoi(mMessage.substr(TRD::SHARES_OFS, TRD::SHARES_LEN));
        } else {
            return std::stoi(mMessage.substr(EXE::SHARES_OFS, EXE::SHARES_LEN));
        }
    }
};

// T must be derived from MessageBase. For testing, need Mock class for the message. 
template<typename T>
class Solution {
private:
    // message wrapper
    MessageBase<T>& mMsg;
    using Elem = std::pair<std::string, int>;

public:
Solution(MessageBase<T>& message) : mMsg(message) {
}

std::vector<Elem>  CollectTopK(int k) {
    // a map from order id to symbol name
    std::unordered_map<std::string, std::string> order_to_symbol;
    // for each symbol, the trade volume
    std::unordered_map<std::string, int> symbol_trade_volume;
    
    // step 1: Compute the volume of each symbol, and store it in the symbol_trade_volume.
    while (mMsg.Next())
    {
      switch (mMsg.Type()) {
      case PITCH_CBOE::MESSAGE::ADD_ORDER::TYPE:
        order_to_symbol[mMsg.OrderId()] = mMsg.Symbol();
        break;

      case PITCH_CBOE::MESSAGE::TRADE::TYPE:
        symbol_trade_volume[mMsg.Symbol()] += mMsg.Share();
        break;

      case PITCH_CBOE::MESSAGE::ORDER_EXECUTED::TYPE:
        {
          const std::string& symbol = order_to_symbol[mMsg.OrderId()];
          symbol_trade_volume[symbol] += mMsg.Share();
        }
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

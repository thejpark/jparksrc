#include <assert.h>
#include <vector>
#include <list>
#include <set>
#include <unordered_set>
#include <queue>
#include <iterator>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional> 
#include <math.h>
#include <climits>
#include <map>
#include <unordered_map>
#include <stack>
#include <memory>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <typeinfo>
#include <random>
#include <sstream>
// time_point::time_since_epoch
#include <chrono>

using namespace std;

class A {
 public:
  static std::shared_ptr<A> Start() {
    return std::shared_ptr<A>();  // build error on this line
  }
 private:
  A(){};
};

constexpr double foo(double x) { return x * x;}

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

class Message {
private:
    // The input stream to read the message from.
    std::istream& mIn;
    // current message instance.
    std::string mMessage;
    using ADD = PITCH_CBOE::MESSAGE::ADD_ORDER::FORMAT;
    using EXE = PITCH_CBOE::MESSAGE::ORDER_EXECUTED::FORMAT;
    using TRD = PITCH_CBOE::MESSAGE::TRADE::FORMAT;
    using CLE = PITCH_CBOE::MESSAGE::CANCEL_ORDER::FORMAT;

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
    template <typename T>
    std::string OrderId() {
        return mMessage.substr(T::ORDER_ID_OFS, T::ORDER_ID_LEN);
    }

    // return the symbol of the message.
    template <typename T>
    std::string Symbol() {
        return mMessage.substr(T::SYMBOL_OFS, T::SYMBOL_LEN);
    }

    // return executed or traded shares.
    template <typename T>
    int Share() {
        return std::stoi(mMessage.substr(T::SHARES_OFS, T::SHARES_LEN));
    }
};



int main() {

    string a = "000111";
    int x = 111;
    x += atoi(a.c_str());
    cout << x << endl;

    std::cout << foo(x) << std::endl;
    // the following line causes error because y is not known at compile time
    // constexpr double z = y * y;

    std::unordered_map<std::string, std::pair<std::string, int>> mm;
    mm["a"] = std::make_pair("b", 1);
    auto& e = mm["a"];
    std::cout << e.first << " " << e.second << std::endl;

    auto& p = mm["a"];
    p.second = 2;
    std::cout << p.first << " " << p.second << std::endl;


}

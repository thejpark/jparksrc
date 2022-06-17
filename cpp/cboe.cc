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

// todo:
// 1. getline bulk read, 2. use partition instead of pq?  3. stoi order id? 4. use trie instead of map for symbol search?
class Solution {
public:
std::vector<std::pair<std::string, int>>  CollectTopK(std::istream& in, int k) {
    using ADD = PITCH_CBOE::MESSAGE::ADD_ORDER::FORMAT;
    using EXE = PITCH_CBOE::MESSAGE::ORDER_EXECUTED::FORMAT;
    using TRD = PITCH_CBOE::MESSAGE::TRADE::FORMAT;

    std::string str;
    str.reserve(1024);
    while (std::getline(in, str))
    {
        switch(str[ADD::MESSAGE_TYPE_OFS]) {
            case 'A':
                // order added
                order_to_symbol[str.substr(ADD::ORDER_ID_OFS, ADD::ORDER_ID_LEN)] = str.substr(ADD::SYMBOL_OFS, ADD::SYMBOL_LEN);
                break;

            case 'P':
                // trade
                symbol_trade_volume[str.substr(TRD::SYMBOL_OFS, TRD::SYMBOL_LEN)] += std::stoi(str.substr(TRD::SHARES_OFS, TRD::SHARES_LEN));
                break;

            case 'E':
                // order executed
            {
                const std::string& symbol = order_to_symbol[str.substr(EXE::ORDER_ID_OFS, EXE::ORDER_ID_LEN)];
                symbol_trade_volume[symbol] += std::stoi(str.substr(EXE::SHARES_OFS, EXE::SHARES_LEN));
            }
                break;

            case 'X':
            default:
                break;

        }
    }

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    #if 0
    // use min heap to store top k. The size of heap is k where k is 10.
    // Time complexity is O(n logk) where k is 10, so it is almsot O(n).
    using elem = std::pair<std::string, int>;
    auto comp = [](const elem &a, const elem& b) {
        return a.second > b.second;
    };

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
    #else

    // partition the symbols so that first k elements are the top k.
    using elem = std::pair<std::string, int>;
    auto comp = [](const elem &a, const elem& b) {
        return a.second > b.second;
    };
    std::vector<elem> result{symbol_trade_volume.begin(), symbol_trade_volume.end()};
    if (result.size() > k) {
      std::nth_element(result.begin(), result.begin() + k - 1, result.end(), comp);
      result.resize(k);
    }
    // Then sort based on the volume size.
    sort(result.begin(), result.end(), comp);
    #endif

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    return result;

}

private:
    // a map from order id to symbol name
    std::unordered_map<std::string, std::string> order_to_symbol;
    // for each symbol, the trade volume
    std::unordered_map<std::string, int> symbol_trade_volume;
};

class Solution2 {
public:
std::vector<std::pair<std::string, int>>  CollectTopK(std::istream& in, int k) {
    using ADD = PITCH_CBOE::MESSAGE::ADD_ORDER::FORMAT;
    using EXE = PITCH_CBOE::MESSAGE::ORDER_EXECUTED::FORMAT;
    using TRD = PITCH_CBOE::MESSAGE::TRADE::FORMAT;

    std::string str;
    str.reserve(1024);
    while (std::getline(in, str))
    {
        int index = 0;
        switch(str[ADD::MESSAGE_TYPE_OFS]) {
            case 'A':
                // order added
                order_to_symbol_index[str.substr(ADD::ORDER_ID_OFS, ADD::ORDER_ID_LEN)] =
                    GetIndexToSymbol(std::string_view(&str[ADD::SYMBOL_OFS], ADD::SYMBOL_LEN));
                break;

            case 'P':
                // trade
                index = GetIndexToSymbol(std::string_view(&str[TRD::SYMBOL_OFS], TRD::SYMBOL_LEN));
                symbol_trade_volume[index] += std::stoi(str.substr(TRD::SHARES_OFS, TRD::SHARES_LEN));
                break;

            case 'E':
                // order executed
                index = order_to_symbol_index[str.substr(EXE::ORDER_ID_OFS, EXE::ORDER_ID_LEN)];
                symbol_trade_volume[index] += std::stoi(str.substr(EXE::SHARES_OFS, EXE::SHARES_LEN));
                break;

            case 'X':
            default:
                break;

        }
    }

    // use min heap to store top k
    using elem = std::pair<int, int>;
    auto comp = [](const elem &a, const elem& b) {
        return a.second > b.second;
    };

    std::priority_queue<elem, std::vector<elem>, decltype(comp)> min_heap(comp);
    for (int i = 0; i < symbol_trade_volume.size(); ++i) {
        if (min_heap.size() < k) {
            min_heap.push({i, symbol_trade_volume[i]});
        } else {
            if (min_heap.top().second < symbol_trade_volume[i]) {
                min_heap.pop();
                min_heap.push({i, symbol_trade_volume[i]});
            }
        }
    }

    // take top k out of min heap
    std::vector<std::pair<std::string, int>> result;
    while (!min_heap.empty()) {
        result.push_back({symbols[min_heap.top().first], min_heap.top().second});
        min_heap.pop();
    }

    reverse(result.begin(), result.end());
    return result;
}

private:
// a vector of symbol names
std::vector<std::string> symbols;
// a vector of trade volumes. symbol_trade_volume[i] is the trade volume of symbol symbols[i].
std::vector<int> symbol_trade_volume;
// a map from symbol name to the index in symbols (and symbol_trade_volume)
std::unordered_map<std::string, int> symbols_map;
// a map from order id to symbol index
std::unordered_map<std::string, int> order_to_symbol_index;


// If symbol is not in symbols, add it to symbols and return its index. otherwise return its index.
int GetIndexToSymbol(const std::string_view& sv) {
    std::string str(sv);
    if (auto it = symbols_map.find(str); it != symbols_map.end()) {
        return it->second;
    } else {
        symbols_map[str] = symbols.size();
        symbols.push_back(move(str));
        symbol_trade_volume.push_back(0);
        return symbols.size() - 1;
    }
}

};

class Message {
private:
    std::istream& mIn;
    std::string message;
    using ADD = PITCH_CBOE::MESSAGE::ADD_ORDER::FORMAT;
    using EXE = PITCH_CBOE::MESSAGE::ORDER_EXECUTED::FORMAT;
    using TRD = PITCH_CBOE::MESSAGE::TRADE::FORMAT;

public:
    Message(std::istream& in) : mIn(in) {
        message.reserve(128);
    }
    bool HasNext() {
        return std::getline(mIn, message).good();
    }

    void Next() {
    }

    char Type() {
        return message[ADD::MESSAGE_TYPE_OFS];
    }

    std::string OrderId() {
        if (message[ADD::MESSAGE_TYPE_OFS] == 'A') {
            return message.substr(ADD::ORDER_ID_OFS, ADD::ORDER_ID_LEN);
        } else {
            return message.substr(EXE::ORDER_ID_OFS, EXE::ORDER_ID_LEN);
        }
    }

    std::string Symbol() {
        if (message[ADD::MESSAGE_TYPE_OFS] == 'A') {
            return message.substr(ADD::SYMBOL_OFS, ADD::SYMBOL_LEN);
        } else {
            return message.substr(TRD::SYMBOL_OFS, TRD::SYMBOL_LEN);
        }
    }

    int Share() {
        if (message[ADD::MESSAGE_TYPE_OFS] == 'P') {
            return std::stoi(message.substr(TRD::SHARES_OFS, TRD::SHARES_LEN));
        } else {
            return std::stoi(message.substr(EXE::SHARES_OFS, EXE::SHARES_LEN));
        }
    }
};

class Solution3 {
public:

std::vector<std::pair<std::string, int>>  CollectTopK(std::istream& in, int k) {
    Message message(in);

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

     #if 0
    // use min heap to store top k. The size of heap is k where k is 10.
    // Time complexity is O(n logk) where k is 10, so it is almsot O(n).
    using elem = std::pair<std::string, int>;
    auto comp = [](const elem &a, const elem& b) {
        return a.second > b.second;
    };

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
    #else

    // partition the symbols so that first k elements are the top k.
    using elem = std::pair<std::string, int>;
    auto comp = [](const elem &a, const elem& b) {
        return a.second > b.second;
    };
    std::vector<elem> result{symbol_trade_volume.begin(), symbol_trade_volume.end()};
    if (result.size() > k) {
      std::nth_element(result.begin(), result.begin() + k - 1, result.end(), comp);
      result.resize(k);
    }
    // Then sort based on the volume size.
    sort(result.begin(), result.end(), comp);
    #endif

    return result;

}

private:
    // a map from order id to symbol name
    std::unordered_map<std::string, std::string> order_to_symbol;
    // for each symbol, the trade volume
    std::unordered_map<std::string, int> symbol_trade_volume;
};


} // namespace PITCH_CBOE

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    PITCH_CBOE::Solution3 sol;
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

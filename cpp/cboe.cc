#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <string.h>
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

class Solution {
public:
void PrintTop10() {
    std::string str;
    int x_cnt = 0;
    int a_cnt = 0;
    int e_cnt = 0;
    int p_cnt = 0;

    using ADD = PITCH_CBOE::MESSAGE::ADD_ORDER::FORMAT;
    using EXE = PITCH_CBOE::MESSAGE::ORDER_EXECUTED::FORMAT;
    using TRD = PITCH_CBOE::MESSAGE::TRADE::FORMAT;

    // std::ios::sync_with_stdio(false);
    auto fin = std::ifstream("pitch_example_data.txt");
    while (getline(fin, str))
    {
        int index = 0;
        switch(str[9]) {
            case 's':
                // symbol_trade_volume.erase(std::string(std::string_view(&str[10], 8)));
                // order_to_symbol.erase(std::string(std::string_view(&str[10], 8)));

            case 'A':
                // order added
                order_to_symbol[str.substr(ADD::ORDER_ID_OFS, ADD::ORDER_ID_LEN)] =
                    GetIndexToSymbol(std::string_view(&str[ADD::SYMBOL_OFS], ADD::SYMBOL_LEN));
                a_cnt++;
                break;

            case 'P':
                // trade
                index = GetIndexToSymbol(std::string_view(&str[TRD::SYMBOL_OFS], TRD::SYMBOL_LEN));
                symbol_trade_volume[index] += std::stoi(str.substr(TRD::SHARES_OFS, TRD::SHARES_LEN));

                p_cnt++;
                break;

            case 'E':
                // order executed
                index = order_to_symbol[str.substr(EXE::ORDER_ID_OFS, EXE::ORDER_ID_LEN)];
                symbol_trade_volume[index] += std::stoi(str.substr(EXE::SHARES_OFS, EXE::SHARES_LEN));

                e_cnt++;
                break;

            case 'X':
                // order cancelled
                x_cnt++;
                break;

            default:
                // std::cout << "unknown message type : " << str[9] << std::endl;
                break;

        }
    }

    // std::cout << "x_cnt: " << x_cnt << std::endl;
    // std::cout << "a_cnt: " << a_cnt << std::endl;
    // std::cout << "e_cnt: " << e_cnt << std::endl;
    // std::cout << "p_cnt: " << p_cnt << std::endl;
    using elem = std::pair<int, int>;
    auto comp = [](const elem &a, const elem& b) {
        return a.second > b.second;
    };

    std::priority_queue<elem, std::vector<elem>, decltype(comp)> min_heap(comp);
    for (int i = 0; i < symbol_trade_volume.size(); ++i) {
        if (min_heap.size() < 10) {
            min_heap.push({i, symbol_trade_volume[i]});
        } else {
            if (min_heap.top().second < symbol_trade_volume[i]) {
                min_heap.pop();
                min_heap.push({i, symbol_trade_volume[i]});
            }
        }
    }

    std::vector<elem> result;
    while (!min_heap.empty()) {
        result.push_back(min_heap.top());
        min_heap.pop();
    }

    std::stringstream ss;
    for (int i = result.size() - 1; i >= 0; --i) {
        ss << symbols[result[i].first] << " " << result[i].second << std::endl;
    }

    std::cout << ss.str();
}

private:
std::unordered_map<std::string, int> order_to_symbol;
std::unordered_map<std::string, int> symbols_map;
std::vector<std::string> symbols;
std::vector<int> symbol_trade_volume;


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

int ParseNumber(const std::string& str, int i, int n) {
    // this makes the performance worse. why?
    int r = 0;
    for (int j = i; j < n + i; ++j) {
        r = r * 10 + str[j] - '0';
    }

    return r;
}

};
} // namespace PITCH_CBOE

int main() {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    PITCH_CBOE::Solution sol;
    sol.PrintTop10();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
}

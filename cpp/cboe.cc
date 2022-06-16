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
// time_point::time_since_epoch
#include <chrono>

class Solution {

private:
std::unordered_map<std::string, int> order_to_symbol;
std::vector<std::string> symbols;
std::unordered_map<std::string, int> symbols_map;
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

public:
void PrintTop10() {
    std::string str;
    int x_cnt = 0;
    int a_cnt = 0;
    int e_cnt = 0;
    int p_cnt = 0;
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
                order_to_symbol[std::string(std::string_view(&str[10], 12))] = GetIndexToSymbol(std::string_view(&str[29], 6));
                a_cnt++;
                break;

            case 'P':
                // trade
                index = GetIndexToSymbol(std::string_view(&str[29], 6));
                symbol_trade_volume[index] += std::stoi(std::string(std::string_view(&str[23], 6)));
                p_cnt++;
                break;

            case 'E':
                // order executed
                index = order_to_symbol[std::string(std::string_view(&str[10], 12))];
                symbol_trade_volume[index] += std::stoi(std::string(std::string_view(&str[22], 6)));
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
};

int main() {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    Solution sol;
    sol.PrintTop10();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
}

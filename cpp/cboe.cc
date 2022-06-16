#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <string.h>
#include <sstream>
// time_point::time_since_epoch
#include <chrono>



int main() {
    std::unordered_map<std::string, std::string> order_to_symbol;
    std::unordered_map<std::string, int> symbol_trade_volume;

    std::string str;
    // std::ios::sync_with_stdio(false);
    // auto fin = std::ifstream("pitch_example_data.txt");
    int cnt = 0;
    while (getline(std::cin, str))
    {
        switch(str[9]) {
            case 's':
                symbol_trade_volume.erase(std::string(std::string_view(&str[10], 8)));
                order_to_symbol.erase(std::string(std::string_view(&str[10], 8)));

            case 'A':
                order_to_symbol[std::string(std::string_view(&str[10], 12))] = std::string_view(&str[29], 6);
                break;

            case 'P':
                symbol_trade_volume[std::string(std::string_view(&str[29], 6))] += std::stoi(std::string(std::string_view(&str[23], 6))); 
                break;

            case 'E':
            {
                const std::string& symbol = order_to_symbol[std::string(std::string_view(&str[10], 12))];
                symbol_trade_volume[symbol] += std::stoi(std::string(std::string_view(&str[22], 6))); 
            }
                break;

            case 'X':

            default:
                ++cnt;
                break;

        }
    }

    std::cout << "default case is " << cnt << std::endl;

    using elem = std::pair<std::string, int>;
    auto comp = [](elem &a, elem& b) {
        return a.second > b.second;
    };

    std::priority_queue<elem, std::vector<elem>, decltype(comp)> pq(comp);
    for (auto& [symbol, size] : symbol_trade_volume) {
        if (pq.size() < 10) {
            pq.push({symbol, size});
        } else {
            if (pq.top().second < size) {
                pq.pop();
                pq.push({symbol, size});
            }
        }
    }

    std::stack<elem> result;
    while (!pq.empty()) {
        result.push(pq.top());
        pq.pop();
    }

    while (!result.empty()) {
        std::cout << "(" << result.top().first << ", " << result.top().second << ")" << std::endl;
        result.pop();
    }
}

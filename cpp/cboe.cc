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


int main() {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    
    std::unordered_map<std::string, std::string> order_to_symbol;
    std::unordered_map<std::string, int> symbol_trade_volume;

    std::string str;
    int x_cnt = 0;
    int a_cnt = 0;
    int e_cnt = 0;
    int p_cnt = 0;
    // std::ios::sync_with_stdio(false);
    auto fin = std::ifstream("pitch_example_data.txt");
    while (getline(fin, str))
    {
        switch(str[9]) {
            case 's':
                // symbol_trade_volume.erase(std::string(std::string_view(&str[10], 8)));
                // order_to_symbol.erase(std::string(std::string_view(&str[10], 8)));

            case 'A':
                // order added
                order_to_symbol[std::string(std::string_view(&str[10], 12))] = std::string_view(&str[29], 6);
                a_cnt++;
                break;

            case 'P':
                // trade
                symbol_trade_volume[std::string(std::string_view(&str[29], 6))] += std::stoi(std::string(std::string_view(&str[23], 6))); 
                p_cnt++;
                break;

            case 'E':
                // order executed
            {
                const std::string& symbol = order_to_symbol[std::string(std::string_view(&str[10], 12))];
                symbol_trade_volume[symbol] += std::stoi(std::string(std::string_view(&str[22], 6))); 
                e_cnt++;
            }
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
    using elem = std::pair<std::string, int>;
    auto comp = [](const elem &a, const elem& b) {
        return a.second > b.second;
    };

    std::priority_queue<elem, std::vector<elem>, decltype(comp)> min_heap(comp);
    for (auto& [symbol, size] : symbol_trade_volume) {
        if (min_heap.size() < 10) {
            min_heap.push({symbol, size});
        } else {
            if (min_heap.top().second < size) {
                min_heap.pop();
                min_heap.push({symbol, size});
            }
        }
    }

    std::stack<elem> result;
    while (!min_heap.empty()) {
        result.push(min_heap.top());
        min_heap.pop();
    }

    while (!result.empty()) {
        auto& a = result.top();
        std::cout << a.first << ", " << a.second << std::endl;
        result.pop();
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;

}

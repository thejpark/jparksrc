#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct order {
    order(string id, string type, int price, int size) :
        m_id(id), m_type(type), m_price(price), m_size(size)
        {}
    string m_id;
    string m_type;
    int m_price;
    int m_size;
};

// map from id to list of iterator to order list
unordered_map<string, list<order>::iterator> sell_order_map;
unordered_map<string, list<order>::iterator> buy_order_map;

// map from price to pair<total number of items with the price, order list>
map<int, pair<int, list<order>>> sell_price_map;
map<int, pair<int, list<order>>> buy_price_map;

string resultString;
stringstream resout(resultString);

void print()
{
    resout << "SELL:" << endl;
    for (auto it = sell_price_map.rbegin(); it != sell_price_map.rend(); ++it)
    {
        resout << it->first << " " << it->second.first << endl;
    }

    resout << "BUY:" << endl;
    for (auto it = buy_price_map.rbegin(); it != buy_price_map.rend(); ++it)
    {
        resout << it->first << " " << it->second.first << endl;
    }
}

void sell(vector<string>& cmd)
{
    if (cmd.size() != 5)
        return;

    int price = stoi(cmd[2]);
    int size = stoi(cmd[3]);
    if (price <= 0 || size <= 0)
        return;

    string& id = cmd[4];
    if (sell_order_map.find(id) != sell_order_map.end() ||
       buy_order_map.find(id) != buy_order_map.end())
        return;

    auto start = buy_price_map.rbegin();
    while (start != buy_price_map.rend())
    {
        auto& priceKey = start->first;
        if (priceKey < price || size <= 0)
            break;

        auto& sizeLeft = start->second.first;
        auto& itemList = start->second.second;
        while (!(itemList.empty()) && (size > 0))
        {
            auto& item = itemList.front();
            if (item.m_size > size)
            {
                resout << "TRADE" << " " << item.m_id << " " << item.m_price << " " << size << " " <<
                        id << " " << price << " " << size << endl;

                item.m_size -= size;
                sizeLeft -= size;
                size = 0;
            }
            else
            {
                resout << "TRADE" << " " << item.m_id << " " << item.m_price << " " << item.m_size <<
                    " " << id << " " << price << " " << item.m_size << endl;

                size -= item.m_size;
                sizeLeft -= item.m_size;
                buy_order_map.erase(item.m_id);
                itemList.pop_front();
            }
        }

        if (sizeLeft == 0)
        {
            buy_price_map.erase(priceKey);
            start = buy_price_map.rbegin();
        }

    }

    if (size == 0)
        return;

    string& type = cmd[1];
    if (type == "GFD")
    {
        order newOrder(id, type, price, size);
        auto& sellItem = sell_price_map[price];
        sellItem.first += size;
        sellItem.second.emplace_back(newOrder);
        auto it = --(sellItem.second.end());
        sell_order_map[id] = it;
    }
}


void buy(vector<string>& cmd)
{
    if (cmd.size() != 5)
        return;

    int price = stoi(cmd[2]);
    int size = stoi(cmd[3]);
    if (price <= 0 || size <= 0)
        return;

    string& id = cmd[4];
    if (sell_order_map.find(id) != sell_order_map.end() ||
       buy_order_map.find(id) != buy_order_map.end())
        return;

    auto start = sell_price_map.begin();
    while (start != sell_price_map.end())
    {
        auto& priceKey = start->first;
        if (priceKey > price || size <= 0)
            break;

        auto& sizeLeft = start->second.first;
        auto& itemList = start->second.second;
        while (!(itemList.empty()) && (size > 0))
        {
            auto& item = itemList.front();
            if (item.m_size > size)
            {
                resout << "TRADE" << " " << item.m_id << " " << item.m_price << " " << size << " " <<
                        id << " " << price << " " << size << endl;

                item.m_size -= size;
                sizeLeft -= size;
                size = 0;
            }
            else
            {
                resout << "TRADE" << " " << item.m_id << " " << item.m_price << " " << item.m_size <<
                    " " << id << " " << price << " " << item.m_size << endl;

                size -= item.m_size;
                sizeLeft -= item.m_size;
                sell_order_map.erase(item.m_id);
                itemList.pop_front();
            }
        }

        if (sizeLeft == 0)
        {
            sell_price_map.erase(priceKey);
            start = sell_price_map.begin();
        }
    }

    if (size == 0)
        return;

    string& type = cmd[1];
    if (type == "GFD")
    {
        order newOrder(id, type, price, size);
        auto& buyItem = buy_price_map[price];
        buyItem.first += size;
        buyItem.second.emplace_back(newOrder);
        auto it = --(buyItem.second.end());
        buy_order_map[id] = it;
    }
}


void cancel(vector<string>& cmd)
{
    if (cmd.size() != 2)
        return;

    string& id = cmd[1];

    if (sell_order_map.find(id) != sell_order_map.end())
    {
        auto it = sell_order_map[id];
        int price = it->m_price;
        auto& sellItem = sell_price_map[price];
        auto& itemList = sellItem.second;
        auto& sizeLeft = sellItem.first;

        itemList.erase(it);
        sizeLeft -= it->m_size;
        if (sizeLeft == 0)
            sell_price_map.erase(price);
        sell_order_map.erase(id);
    }
    else if (buy_order_map.find(id) != buy_order_map.end())
    {
        auto it = buy_order_map[id];
        int price = it->m_price;
        auto& buyItem = buy_price_map[price];
        auto& itemList = buyItem.second;
        auto& sizeLeft = buyItem.first;

        itemList.erase(it);
        sizeLeft -= it->m_size;
        if (sizeLeft == 0)
           buy_price_map.erase(price);
        buy_order_map.erase(id);
    }
}

void modify(vector<string>& cmd)
{
    if (cmd.size() != 5)
        return;

    int price = stoi(cmd[3]);
    int size = stoi(cmd[4]);

    if (price <= 0 || size <= 0)
        return;

    string type;
    string& id = cmd[1];

    if (sell_order_map.find(id) != sell_order_map.end())
    {
        type = sell_order_map[id]->m_type;
        vector<string> newCmd{"CANCEL", id};
        cancel(newCmd);
    }
    else if (buy_order_map.find(id) != buy_order_map.end())
    {
        type = buy_order_map[id]->m_type;
        vector<string> newCmd{"CANCEL", id};
        cancel(newCmd);
    }
    else
    {
        return;
    }

    if (cmd[2] == "BUY")
    {
        vector<string> newCmd {"BUY", type, cmd[3], cmd[4], id};
        buy(newCmd);
    }
    else if (cmd[2] == "SELL")
    {
        vector<string> newCmd {"SELL", type, cmd[3], cmd[4], id};
        sell(newCmd);
    }
}

void process_cmd(vector<string>& cmd)
{
    switch (cmd[0][0])
    {
        case 'B':
            if (cmd[0] == "BUY")
                buy(cmd);
            break;
        case 'S':
            if (cmd[0] == "SELL")
                sell(cmd);
            break;
        case 'M':
            if (cmd[0] == "MODIFY")
                modify(cmd);
            break;
        case 'P':
            if (cmd[0] == "PRINT")
                print();
            break;
        case 'C':
            if (cmd[0] == "CANCEL")
                cancel(cmd);
            break;

        default:
            break;
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */

    string s;
    vector<string> cmd;

    while (getline(cin, s))
    {
        stringstream ss(s);
        string t;
        while(getline(ss, t, ' '))
        {
            cmd.emplace_back(t);
        }
        process_cmd(cmd);
        cmd.clear();
    }
    cout << resout.str();

    return 0;
}

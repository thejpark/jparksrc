#include <assert.h>
#include <vector>
#include <list>
#include <set>
#include <unordered_set>
#include <queue>
#include <deque>
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

class lrumap3 {
private:

  deque<pair<string, int>> l; // if we want to limit the number of cache element, then we need to access map element.
    // so list need to have either <key, value> pair (in this example, it is <string, int>) or <iterator_to_map_elem, value)
  unordered_map<string, deque<pair<string,int>>::iterator> mm;
  int size;
  int cnt;

public:
  explicit lrumap3(int sz) : size(sz), cnt(0) {}

  bool get(const string& s, int* x)
    {
        if (mm.find(s) != mm.end())
        {
          auto& t = mm[s];
          int i = *x = t->second;
          l.erase(t);
          l.push_front(make_pair(s, i));
          mm[s] = l.begin();
          return true;
        }
        else
        {
          return false;
        }
    }

    void put(const string& s, int i)
    {
      int t;
      auto n = get(s, &t);

      if (!n) {
        if (cnt == size) {
            auto& b = l.back();
            mm.erase(b.first);
            l.pop_back();
            cnt--;
        }
        l.push_front(make_pair(s, i));
        mm[s] = l.begin();
        cnt++;
      }
      else {
        auto a = l.begin();
        a->second = i;
      }
    }

    void print() {
        for (auto& e : l) {
            cout << e.first << " : " << e.second << endl;
        }
    }
};

void test_lrumap3() {
    lrumap3 lru(2);
    int res{0};
    cout << lru.get("a", &res) << " " << res <<  endl;
    lru.put("a", 1);
    cout << lru.get("a", &res) << " " << res <<  endl;

    cout << lru.get("b", &res) << " " << res <<  endl;
    lru.put("b", 2);
    cout << lru.get("b", &res) << " " << res <<  endl;

    cout << lru.get("c", &res) << " " << res <<  endl;
    lru.put("c", 3);
    cout << lru.get("c", &res) << " " << res <<  endl;

    lru.print();
}

int main() {
    test_lrumap3();
}

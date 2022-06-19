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


int main() {


    std::unordered_map<std::string, std::pair<std::string, int>> mm;
    mm["a"] = std::make_pair("b", 1);
    auto& e = mm["a"];
    std::cout << e.first << " " << e.second << std::endl;

    auto& p = mm["a"];
    p.second = 2;
    std::cout << p.first << " " << p.second << std::endl;

    auto& [x, y] = mm["a"];
    y = 100;
    auto& [_, r] = mm["a"];
    std::cout << r << std::endl;

    r = 30;

    std::cout << mm["a"].first << " " << mm["a"].second << std::endl;
}

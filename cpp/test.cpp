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

int main() {

    string a = "000111";
    int x = 111;
    x += atoi(a.c_str());
    cout << x << endl;

    ofstream tf("");
    tf << "test " << endl;

    auto r = A::Start();
}

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

class A {
public:
    A(int a, int b): x(a), y(b) {}
    int x;
    int y;
};

int main() {
    unordered_map<int, A> m;
    A a(2, 2);
    m.insert({2, a});
    auto& r = m.at(2);
    r.x = 1;
    r.y = 1;
    std::cout << "the result is " << m.at(2).x << " " << m.at(2).y << std::endl;
}


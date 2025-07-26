#include <assert.h>
#include <exception>
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
#include <utility> // For std::forward

using namespace std;

class A {
public:
    A(int a, int b): x(a), y(b) 
{
	std::cout << "A is created" << std::endl;
}
    A(const A& a) {
      std::cout << "A is copied" << std::endl;
      x = a.x;
      y = a.y;  
    }


    int x;
    int y;
};

void foo() {
    try {
        throw std::exception();
    } catch(std::exception& e) {
        std::cout << "catch exception" << std::endl;
    }

    std::cout << "after catch" << std::endl;
}

struct st {
    int a;
    char *b;
};  

void bar(const A& a) {
  [a] {
    std::cout << "a.x = " << a.x << std::endl;
  }();
}

int main() {
    std::cout << "test for lambda" << std::endl;
    A a1(1, 2);
    bar(a1);
}


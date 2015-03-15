#include <iostream>
#include <string>
#include <vector>
#include <future>

using namespace std;

// clang++ -std=c++11 -stdlib=libc++ cpp11.cpp

int t1()
{
    vector<int> x{1, 2, 3};

    for(auto it = x.begin(); it != x.end(); ++it)
        cout << *it;
    cout << endl;
    return 0;
}


int myfib(int x)
{
    if (x == 0 || x == 1)
        return x;

    auto r1 = async(myfib, x - 1);
    auto r2 = async(myfib, x - 2);
    return r1.get() + r2.get();
}

void t2()
{
    cout << myfib(6) << endl;
}

int main(int argc, char * argv[])
{
	t2(); 
}




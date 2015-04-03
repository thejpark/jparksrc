#include <iostream>
#include <string>
#include <vector>
#include <future>
#include <thread>
#include <mutex>
#include <stdexcept>

using namespace std;

// clang++ -std=c++11 -stdlib=libc++ cpp11.cpp

int t1()
{
    vector<int> x{1, 2, 3};

    for(auto it = x.begin(); it != x.end(); ++it)
        cout << *it;
    cout << endl;

    for (auto i: x)
        cout << i;
    cout << endl;
    
    // copy elements to i
    for (auto i : {1, 2, 3})
        cout << i;

    // do not copy elements of x to i, but use reference
    for (auto& i: x)
        cout << i;
    cout << endl;
 
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


class mysem {
public:
    mysem(int size) : avail{size} {}
    mysem() : avail{0} {}
    ~mysem() {}
    void acquire()
    {
        unique_lock<mutex> lck{mmutex}; // acquire mmutex
        while (true) {
            if (avail > 0)
            {
                --avail;
                return;
            }
            else
            {
                mcond.wait(lck); // release lck and wait
                // reacquire lck upon wake up
            }
        }
    }
    void release()
    {
        unique_lock<mutex> lck{mmutex}; // acquire mmutex
        ++avail;
        mcond.notify_one();
    }

private:
    int avail;
    condition_variable mcond;
    mutex mmutex;
};


static int mycount = 0;
static mutex m;
static mysem sem(100);

void task3a()
{
    while (true)
    {
        sem.acquire();
        unique_lock<mutex> lck{m};
        ++mycount;
        cout << this_thread::get_id() << " : " << mycount << endl;
    }
}

void task3b()
{
    while (true)
    {
        sem.release();
    }
}

void t3()
{
    thread a(task3a);
    thread b(task3a);
    // thread c(task3b);
    a.join();
    b.join();
    // c.join();
}

// RAII (vector, string, etc which hides nakid new/delete with handle class.

class Vector
{
public:
    Vector() : elem{new double[10]}, sz{10} {}
    Vector(int s)
    {
        if (s < 0)
            throw length_error{"length error"};
        elem = new double[s];
        sz = s;
    }

    Vector(std::initializer_list<double> lst) :
        elem{new double[lst.size()]},
        sz{static_cast<int>(lst.size())}
    {
        copy(lst.begin(), lst.end(), elem);
    }

    Vector(const Vector& a):
        elem{new double[a.sz]}, sz{a.sz}
    {
        for (int i = 0; i != sz; ++i)
            elem[i] = a.elem[i];
    }

    Vector& operator=(const Vector& a)
    {
        double*p = new double[a.sz];
        for (int i = 0; i != a.sz; ++i)
            p[i] = a.elem[i];
        delete[] elem;
        elem = p;
        sz = a.sz;
        return *this;
    }
    
    ~Vector()
    {
        delete[] elem;
    }

    double& operator[](int i) {
        if (i < 0 || size() <= i)
            // out_of_range is in <stdexcept>
            throw out_of_range{"Vector::operator[]"};
        return elem[i];
    }
    int size() { return sz;}
private:
    double* elem;
    int sz;
};

// So, enum can be used to create singleton pattern?
enum class Color {red, blue, green};
enum class TrafficLight {green, yellow, red};
// enum has initialization, assignment, and comparison, and also
// allow adding new method
TrafficLight& operator++(TrafficLight & t)
{
    switch(t) {
    case TrafficLight::green: return t=TrafficLight::yellow;
    case TrafficLight::yellow: return t=TrafficLight::red;
    case TrafficLight::red: return t=TrafficLight::green;
    }
}

void t4()
{
    Color c = Color::red;
    TrafficLight t = TrafficLight::red;
    // the following line is error, is Color is not int type
    // int i = Color::red;
    // Color c = 2;
    TrafficLight next = ++t;
    if (next == TrafficLight::green)
        cout << "next is green" << endl;
}

int main(int argc, char * argv[])
{
	t4(); 
}




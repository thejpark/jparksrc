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

template<typename T>
class Vector
{
public:
    using value_type = T;
    using size_type = unsigned int;

    Vector() : elem{new T[10]}, sz{10} {}
    Vector(int s)
    {
        if (s < 0)
            throw length_error{"length error"};
        elem = new T[s];
        sz = s;
    }

    Vector(std::initializer_list<T> lst) :
        elem{new T[lst.size()]},
        sz{static_cast<int>(lst.size())}
    {
        copy(lst.begin(), lst.end(), elem);
    }

    Vector(const Vector& a):
        elem{new T[a.sz]}, sz{a.sz}
    {
        for (int i = 0; i != sz; ++i)
            elem[i] = a.elem[i];
    }

    // move constructor
    // && is rvalue reference. As it changes the value of a, a should not be
    // const
    Vector(Vector&& a): elem{a.elem}, sz{a.sz}
    {
        a.elem = nullptr;
        a.sz = 0;
    }
    // move assignment
    Vector& operator=(Vector&& a)
    {
        elem = a.elem;
        sz = a.sz;
        a.elem = nullptr;
        a.sz = 0;
        return *this;
    }
    
    T* begin()
    {
        return sz? &elem[0] : nullptr;
    }

    T* end()
    {
        return begin() + sz;
    }

    Vector& operator=(const Vector& a)
    {
        T* p = new T[a.sz];
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

    T& operator[](int i) {
        if (i < 0 || size() <= i)
            // out_of_range is in <stdexcept>
            throw out_of_range{"Vector::operator[]"};
        return elem[i];
    }
    int size() { return sz;}
private:
    T* elem;
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

Vector<double> t5()
{
    Vector<double> x(1000);
    Vector<double> y(1000);
    Vector<double> z(1000);
    // copy
    z = x;
    // move
    y = std::move(x);
    // move
    return z;
}


// how to supress operations?
class Shape {
public:
    Shape(){}
    Shape(const Shape&)=delete; // no copy operation
    Shape& operator=(const Shape&)=delete;
    Shape(Shape&&)=delete; // no move operation
    virtual ~Shape(){};
    virtual void draw() = 0;
};

class Circle : public Shape
{
public:
    Circle() {}
    void draw()
    {
        cout << "Circle" << endl;
    }
};

class Smiley : public Circle
{
public:
    void draw()
    {
        cout << "Smiley" << endl;
    }
};

// unique_ptr hides naked new/delete.
unique_ptr<Shape> ReadShape(istream& is)
{
// read shape header from is and find its kind k
    // switch (k) {
    // case Kind::circle:
    //     // read circle data
    return unique_ptr<Shape>(new Circle());
}

template<typename T>
class LessThan {
    const T val;
public:
    LessThan(const T& v) : val(v) {}
    bool operator()(const T& x) const {return x < val;}
};

void t6()
{
    const int num = 44;
    LessThan<int> lti {num};
    LessThan<string> lts {"the"};
    cout << "1: " << lti(43) << " and 2: " << lts("then") << endl;
    // lambda expression is just like a function object but has no name
    cout << "3: " << [&](int a){return a < num;}(43) << endl;
}

template <typename T, typename O>
void for_all(T& t, O o)
{
    for (auto& v: t)
        o(*v);
}

void t7()
{
    vector<unique_ptr<Shape>> v;
    while(cin)
        v.push_back(ReadShape(cin));
    for_all(v, [](Shape& s){s.draw();});
}


void f() {}

template<typename T, typename... Tail>
void f(T head, Tail... tail)
{
    [](T& h){ cout << h << " "; }(head);
    f(tail...);
}

void t8()
{
    cout << "first: ";
    f(1, 2.2, "hello");
    cout << "\nsecond: ";
    f(0.2, 'c', "yuck!", 0, 1, 2);
    cout << "\n";
}

int main(int argc, char * argv[])
{
	t8(); 
}




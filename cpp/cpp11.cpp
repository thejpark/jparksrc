#include <iostream>
#include <fstream>
#include <iterator>
#include <map>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <future>
#include <thread>
#include <mutex>
#include <stdexcept>
#include <numeric>

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

void t5()
{
    try {
        Vector<double> x(1000);
        Vector<double> y(1000);
        Vector<double> z(1000);
        // copy
        z = x;
        // move
        y = std::move(x);
        // move at return statement
        // return z;
    } catch (length_error e) {
        cout << "length error" << endl;
    } catch (...) {
        cout << " unknown error" << endl;
    }
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

template<typename V>
using StringMap = map<string, V>;
void t9()
{
    StringMap<int> m;
    m["this"] = 1;
    for (auto c : m)
        cout << c.first << " " << c.second << endl;
}

// Unless you have a reason not to, use a vector (than other containers such as list). A vector performs better
// for traversal (i.e., find() and count()), and fo sorting and searching
// (sort() and binary_search()).


void t10()
{
    unordered_map<string, int> PhoneBook = {
        {"david k", 123},
        {"william d", 456},
        {"james j", 789}
    };

    cout << PhoneBook["david k"] << endl;

    // please make sure that as it is actually hash, it is not ordered
    for (auto& v : PhoneBook)
        cout << v.first << " : " << v.second << endl;
}


struct Entry {
    string name;
    int number;
};

bool operator<(const Entry&x, const Entry& y)
{
    return x.name < y.name;
}

// for some reason, unique_copy gives compile error.
template <class InputIterator, class OutputIterator>
  OutputIterator unique_copy1 (InputIterator first, InputIterator last,
                              OutputIterator result)
{
  if (first==last) return result;

  *result = *first;
  while (++first != last) {
      // Traits class defining properties of iterators
      typename iterator_traits<InputIterator>::value_type val = *first;
      if (!(*result == val))   // or: if (!pred(*result,val)) for version (2)
          *(++result)=val;
  }
  return ++result;
}

// unique element using sort
// list<Entry> get_unique_copy(vector<Entry>& v)
// {
//     list<Entry> ll;
//     sort(v.begin(), v.end());
//     unique_copy(v.begin(), v.end(), back_inserter(ll));
//     return ll;
// }

void t11()
{
    vector<Entry> PhoneBook = {
        {"david k", 123},
        {"david k", 123},
        {"william d", 456},
        {"james j", 789}
    };

    // list<Entry> l;
    // unique_copy(PhoneBook.begin(), PhoneBook.end(),
    //             back_inserter(l));

    set<Entry> s{PhoneBook.begin(), PhoneBook.end()};
    for (auto& e : s)
        cout << e.name << " : " << e.number << endl;
}

void t12()
{
    string s{"this"};
    // string iterator
    auto p = find(s.begin(), s.end(), 't');
    if (p == s.end())
        cout << "error" << endl;
    else
        cout << "pass" << endl;
}

// using typename to define a type inside template definition
template<typename T>
using Iterator = typename T::iterator;

template<typename C, typename V>
vector<Iterator<C>> find_all(C& c, V v)
{
    vector<Iterator<C>> res;
    for (auto p = c.begin; p != c.end(); ++c)
        if (*p == v)
            res.push_back(p);
    return res;
}   


void t13()
{
    string from, to;
    cin >> from >> to;

    ifstream is{from};
    istream_iterator<string> ii {is};
    istream_iterator<string> eos {};
    
    ofstream os{to};
    ostream_iterator<string> oo {os, "\n"};

    vector<string> b {ii, eos};
    // sort all the string in the file
    sort(b.begin(), b.end());
    unique_copy(b.begin(), b.end(), oo);
    // print error status
    cout << endl << !is.eof() || !os;
}


template <class InputIterator1, class InputIterator2, class OutputIterator>
  OutputIterator merge1 (InputIterator1 first1, InputIterator1 last1,
                        InputIterator2 first2, InputIterator2 last2,
                        OutputIterator result)
{
  while (true) {
    if (first1==last1) return std::copy(first2,last2,result);
    if (first2==last2) return std::copy(first1,last1,result);
    *result++ = (*first2<*first1)? *first2++ : *first1++;
  }
}


void t14()
{
    string res;
    string s{"acfg"};
    string t{"bdeh"};
    merge1(s.begin(), s.end(), t.begin(), t.end(), back_inserter(res));

    cout << s << " : " << t << " : " << res << endl;
}

void f15()
{
    cout << "hello";
}

struct F15 {
    void operator()() { cout << "parallel world" ;}
};

void t15()
{
    thread t1 {f15};
    thread t2 {F15()};
    t1.join();
    t2.join();

}

// if we need to return result, we should use out-param
void f16(vector<double>& v)
{
    cout << "hello";
}

struct F16 {
    vector<double>& v; 
    F16(vector<double>& vv) : v{vv} {}
    void operator()() { cout << "parallel world" ;}
};

void t16()
{
    vector<double> sv {1, 2, 3};
    vector<double> tv {3, 2, 1};
// we need ref() to tell variadic template 'sv' is reference not object
    thread t1 {f16, ref(sv)};
    thread t2 {F16(tv)};
    t1.join();
    t2.join();
}


void t17()
{
    mutex m1, m2;

    unique_lock<mutex> lck1{m1, defer_lock};
    unique_lock<mutex> lck2{m2, defer_lock};

    lock(lck1, lck2);
}

double accum(double* beg, double* end, double init)
{
    return accumulate(beg, end, init);
}

double comp2(vector<double>& v)
{
    using Task_type = double(double*, double*, double);

    packaged_task<Task_type> pt0 {accum};
    packaged_task<Task_type> pt1 {accum};

    future<double> f0 {pt0.get_future()};
    future<double> f1 {pt1.get_future()};

    double* first = &v[0];
    thread t1 {move(pt0), first, first + v.size() / 2, 0.0};
    thread t2 {move(pt1), first + v.size() / 2, first + v.size(), 0.0};
    return f0.get() + f1.get();
}

int main(int argc, char * argv[])
{
	t16();
}

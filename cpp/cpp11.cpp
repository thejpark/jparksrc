#include <assert.h>
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
#include <memory>
#include <queue>
#include <span>

using namespace std;

// clang++ -std=c++20 -stdlib=libc++ cpp11.cpp
// g++-4.9

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

    auto r1 = async(myfib, x - 1); //jj
    auto r2 = async(myfib, x - 2);
    return r1.get() + r2.get();
}

void t2()
{
    cout << myfib(6) << endl;
}

int plus2(int *i)
{
    return *i + 2;
}


void t2_1()
{
    int i = 3;
    auto r = async(plus2, &i);
    cout << r.get() << endl;
}


class mysem { //jj
public:
    mysem(int size) : avail{size} {}
    mysem() : avail{0} {}
    ~mysem() {}
    void acquire()
    {
        unique_lock<mutex> lck{mmutex}; // acquire mmutex
        while (!avail) {
                mcond.wait(lck); // release lck and wait
                // reacquire lck upon wake up
        }
        --avail;
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


class test3 {
public:
    test3() : mycount{0}, sem{100} {}
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
private:
    int mycount;
    mutex m;
    mysem sem;
};


void t3()
{
    test3 t;
    // first argument of the method is a reference(or pointer) to an object
    thread a(&test3::task3a, ref(t)); //jj
    thread b(&test3::task3a, ref(t));
    // thread c(task3b);
    a.join();
    b.join();
    // c.join();
}

// RAII (vector, string, etc which hides nakid new/delete with handle class.
template<typename T>
class Vector //jj
{
public:
    // alias
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
enum class Color {red, blue, green}; //jj
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
    } catch (...) { //jj
        cout << " unknown error" << endl;
    }
}


// how to supress operations?
class Shape {
public:
    Shape(){}
    Shape(const Shape&)=delete; // no copy operation //jj
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
unique_ptr<Shape> ReadShape(istream& is) //jj
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

template <class InputIterator, class OutputIterator>
  OutputIterator unique_copy1 (InputIterator first, InputIterator last,
                              OutputIterator result)
{
  if (first==last) return result;

  *result = *first;
  while (++first != last) {
      // Traits class defining properties of iterators
    typename iterator_traits<InputIterator>::value_type val = *first; //jj
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
  thread t1 {f15}; //jj
    thread t2 {F15()};
    t1.join();
    t2.join();

}

// if we need to return result, we should use out-param //jj
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
// we need ref() to tell variadic template 'sv' is reference not object //jj
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
    // difference between async and packaged_task is that, package_task should
    // explicitly start task. if you do not start thread the it will start in
    // the current thread.
    thread t1 {move(pt0), first, first + v.size() / 2, 0.0}; // start task //jj
    thread t2 {move(pt1), first + v.size() / 2, first + v.size(), 0.0};
    return f0.get() + f1.get();
}


class my_countdown_latch { //jj
public:
    my_countdown_latch(int n)
    {
        if (n <= 0)
            throw length_error("length error");
        count = n;
    }

    void countDown()
    {
        unique_lock<mutex> l{mmutex};
        if (--count == 0)
            mcond.notify_all();
    }

    void wait()
    {
        unique_lock<mutex> l{mmutex};
        mcond.wait(l);
    }

private:
    condition_variable mcond;
    int count;
    mutex mmutex;
};


void task18(my_countdown_latch& mcl,
            my_countdown_latch& mcl2)
{
    mcl.wait();
    cout << " a " << endl;
    mcl2.countDown();
}


void t18()
{
    my_countdown_latch mcl(1);
    my_countdown_latch mcl2(5);
    vector<thread> threads;
    for (int i = 0; i < 5; ++i)
        threads.push_back(thread(task18, ref(mcl), ref(mcl2)));
    cout << "test started" << endl;
    mcl.countDown();
    mcl2.wait();
    cout << "test ended" << endl;
    for (auto& v : threads)
        v.join();
}


class my_barrier { //jj
public:
    my_barrier(int n)
    {
        if (n <= 0)
            throw length_error("length error");
        size = count = n;
    }

    void await()
    {
        unique_lock<mutex> l{mmutex};
        if (--count == 0)
        {
            mcond.notify_all();
            count = size;
        }
        else
        {
            mcond.wait(l);
        }
    }

private:
    condition_variable mcond;
    int count;
    int size;
    mutex mmutex;
};

template <typename T>
class my_bounded_blocking_queue { //jj
public:
    my_bounded_blocking_queue(string s="", int size=10) :
        name{s},
        head{0},
        tail{0},
        capacity{size},
        data{new T[size]},
        availSpace{size},
        availItems{0} {}
    void put(T t);
    T take();

private:
    void putItem(T t);
    T getItem();
    int head;
    int tail;
    int capacity;
    mutex mmutex;
    string name;
    mysem availItems;
    mysem availSpace;
    T* data;
};

template <typename T>
void my_bounded_blocking_queue<T>::put(T t)
{
    availSpace.acquire();
    putItem(t);
    availItems.release();
}

template <typename T>
void my_bounded_blocking_queue<T>::putItem(T t)
{
    unique_lock<mutex> lck{mmutex};
    data[tail] = t;
    tail = (tail + 1) % capacity;
}

template<typename T>
T my_bounded_blocking_queue<T>::take()
{
    availItems.acquire();
    T data = getItem();
    availSpace.release();
    return data;
}

template <typename T>
T my_bounded_blocking_queue<T>::getItem()
{
    unique_lock<mutex> lck{mmutex};
    T r = data[head];
    head = (head + 1) % capacity;
    return r;
}

#if 0

struct item{
    int data;
};

constexpr int buf_max = 20;
int head = 0;
int tail = 0;

condition_variable availItem;
condition_variable availSpace;
mutex mtx;

item shared_buff[buff_max;]

void produce(item nextProduced)
{
    while ((head + 1) mod buff_max == tail) {};

    // 1) using cond and mutex
    // unique_lock<mutex> lck(mtx);
    // while ((head + 1) % buff_max == tail)
    //     availSpace.wait(lck);

    shared_buff[head] = nextProduced;
    head = (head + 1) mod buff_max;
    // availItem.notify_one();
}


item consume()
{
    while (head == tail) {};
    // 1) using cond and mutex
    // unique_lock<mutex> lck(mtx);
    // while (head == tail)
    //     availItem.wait(lck);

    nextConsumed = shared_buff[tail];
    tail = (tail + 1) mod buff_max;
    // availSpace.notify_one();
}

// using lockless

void push(T *ptr)
{
    thr_pos().head = head_;
    thr_pos().head = __sync_fetch_and_add(&head_, 1);

    while (__builtin_expect(thr_pos().head >=
                            last_tail_ + Q_SIZE, 0))
    {
        ::sched_yield();

        auto min = tail_;
        for (size_t i = 0; i < n_consumers_; ++i) {
            auto tmp_t = thr_p_[i].tail;

            asm volatile("" ::: "memory"); // compiler barrier

            if (tmp_t < min)
                min = tmp_t;
        }
        last_tail_ = min;
    }

    ptr_array_[thr_pos().head & Q_MASK] = ptr;
    thr_pos().head = ULONG_MAX;
}

T *pop()
{
    thr_pos().tail = tail_;
    thr_pos().tail = __sync_fetch_and_add(&tail_, 1);

    while (__builtin_expect(thr_pos().tail >=
                            last_head_, 0))
    {
        ::sched_yield();

        auto min = head_;
        for (size_t i = 0; i < n_producers_; ++i) {
            auto tmp_h = thr_p_[i].head;

            asm volatile("" ::: "memory"); // compiler barrier

            if (tmp_h < min)
                min = tmp_h;
        }
        last_head_ = min;
    }

    T *ret = ptr_array_[thr_pos().tail & Q_MASK];
    thr_pos().tail = ULONG_MAX;
    return ret;
}
#endif

template <typename T>
class my_blocking_queue { //jj
    class elem {
    public:
        elem(T t) : data{t}, prev{nullptr}, next{nullptr} {}
        ~elem() { cout << "deleted" << endl; }
        shared_ptr<elem> prev;
        shared_ptr<elem> next;
        T data;
    };
public:
    my_blocking_queue(string s="") : name{s}, count{0}, availItems{0} {}
    void put(T t);
    T take();
    int size()
    {
        unique_lock<mutex> lck{mmutex};
        return count;
    }

private:
    shared_ptr<elem> head;
    shared_ptr<elem> tail;
    int count;
    mutex mmutex;
    string name;
    mysem availItems;
};

template <typename T>
void my_blocking_queue<T>::put(T t)
{
    shared_ptr<elem> p{new elem(t)};

    unique_lock<mutex> lck{mmutex};
    if (tail == nullptr)
    {
        tail = head = p;
    }
    else
    {
        tail->next = p;
        p->prev = tail;
        tail = p;
    }
    ++count;
    availItems.release();
}

template<typename T>
T my_blocking_queue<T>::take()
{
    // assuming that take is a blocking method
    availItems.acquire();
    unique_lock<mutex> lck{mmutex};
    assert(head != nullptr);

    shared_ptr<elem> p = head;
    head = head->next;
    if (head == nullptr)
        tail = nullptr;

    --count;
    T data = p->data;
    return data;
}


void t19()
{
    my_blocking_queue<int> mbi;

    mbi.put(1);
    int x = mbi.take();
    cout << "done" << endl;
    assert(x == 1);
}

void client(my_blocking_queue<int>& qi, my_blocking_queue<int>& qo) //jj
{
    int i;
    int count = 0;
    while (i = qi.take())
    {
        // cout << "in:" << i << endl;
        if (i == -1)
        {
            --count;
            if (count == 0 && (qi.size() == 0))
            {
                cout << "client is done!" << endl;
                qo.put(-1);
                return;
            }
        }
        else
        {
            qo.put(i);
            ++count;
        }
    }
}

void t20()
{
    my_blocking_queue<int> mbi{"a"};
    my_blocking_queue<int> mbo{"b"};

    map<int, vector<int>> mc;

    mc[1] = vector<int>{2, 3, 4};
    mc[2] = vector<int>{21, 22, 23};
    mc[3] = vector<int>{31, 32, 33};
    mc[4] = vector<int>{41, 42, 43};

    mbi.put(1);
    thread t1(client, ref(mbi), ref(mbo));

    int i;
    while (i = mbo.take())
    {
        // cout << "out:" << i << endl;
        if (i == -1)
            break;
        for (auto e : mc[i])
            mbi.put(e);
        mbi.put(-1);
    }
    t1.join();
}


bool  comp21(pair<string, int>& p1, pair<string, int>& p2)
{
    return p1.second < p2.second;
}


void t21()
{
// find top 10 most occured word in the list
    string s;
    map<string, int> mc;
    while(cin >> s)
    {
        mc[s]++;
    }

    int min = 0;
    pair<string, int> vs[10];

    for (auto e: mc)
    {
        if (e.second > min)
        {
            vs[0] = e;
            // same as sort, but vector is already sorted.
            // so better not use stl sort() method.
            //
            // sort(vs, vs + 10, comp21);
            //
            // But if the size of top x is bigger, than
            // probably the best way would be to use
            // heap structure.
            for (int i = 0; i < 9; ++i)
            {
                if (vs[i].second > vs[i + 1].second)
                    swap(vs[i], vs[i + 1]);
                else
                    break;
            }
            min = vs[0].second;
        }
    }

    for (int i = 9; i != -1; --i)
        cout << vs[i].first << " : " << vs[i].second << endl;
}

bool  comp22(pair<string, int>& p1, pair<string, int>& p2)
{
    return p1.second > p2.second;
}

void t22()
{
  // find top 10 most occured word in the list //jj
  string s;
  map<string, int> mc;
  while(cin >> s)
    {
      mc[s]++;
    }

  int min = 0;
  vector<pair<string, int>> vs;
  vs.resize(10);

  make_heap(vs.begin(), vs.end(), comp22);

  for (auto e: mc)
    {
      if (e.second > min)
        {
          pop_heap(vs.begin(), vs.end(), comp22);
          vs.pop_back();
          vs.push_back(e);
          push_heap(vs.begin(), vs.end(), comp22);
          min = vs[0].second;
        }
    }

  sort_heap(vs.begin(), vs.end(), comp22);

  for (auto it = vs.begin(); it != vs.end(); ++it)
    cout << it->first << " : " << it->second << endl;
}

void t22_1()
{
// find top 10 most occured word in the list using priority queue //jj
    string s;
    map<string, int> mc;
    while(cin >> s)
    {
        mc[s]++;
    }

    using elem = pair<string, int>;
    auto comp = [](elem e1, elem e2) { return e1.second > e2.second; };
    priority_queue<elem, vector<elem>, std::function<bool(elem, elem)>> pq(comp);
    /*
      or I have to define a class for comp
      class comp
      {
      public:
      bool operator() (pair<string, int>& a, pair<string, int>& b)
      {
          return a.second > b.second;
      }
      };

      priority_queue<elem, vector<elem>, comp> pq;

     */

    for (auto e: mc) {
        pq.emplace(e);
        if (pq.size() > 10) {
            pq.pop();
        }
    }

    while (pq.size() > 0) {
        elem e = pq.top();
        cout << e.first << endl;
        pq.pop();
    }

}


#if 0

// concurrent stack without using lock
template <typename T>
class concurrent_stack
{
public:
    concurrent_stack() {}
    void push(T t) {
        node* newHead = new node(t);
        node* oldHead;
        do {
            oldHead = top;
            newHead->next = oldHead;
        } while (!top->CompareAndSet(oldHead, newHead));
    }

    T* pop() {
        node* oldHead;
        node* newHead;
        do {
            oldHead = top;
            if (oldHead == nullptr)
                return nullptr;
            newHead = oldHead->next;
        } while (!top.compareandset(oldHead, newHead));

        return oldHead->item;

    }

private:
    class node {
    public:
        node (T t) : item(t) {};
        T* next {nullptr};
        T item;
    };

    atomic<node*> top{nullptr};
};

#endif


void fs(span<int> p)
{
  for (int&x : p)
    {
      x = 0;
    }
}

void test_span()
{
  int a[100];
  fs(a);
  fs({a + 10, 100});
}



// Write a program that returns top 1000 frequent search terms out of 256 x 1 GB log files using 8 x quad-core processor machines with 8 GB RAM.
int main(int argc, char * argv[])
{
	test_span();
}

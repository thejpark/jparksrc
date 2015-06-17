/*
 *
 * Take a look at how they solved the problem in ctci. It is related how they work and
 * solve problems. See 1.5.2. Be familiar with how iterator is implemented (remove, find, parition, ...)
 * Interview questions are one of their everyday problems.
 *
 * Sometimes it is necessary to run the list or data in multiple (usually 2 passes), first pass
 * for finding size or other property, second pass for processing. see 1.7.
 *
 */ 


#include <assert.h>
#include <vector>
#include <list>
#include <set>
#include <iterator> //
#include <iostream>
#include <algorithm>
#include <functional> // function  object
#include <math.h>
#include <map>
#include <stack>
#include <memory> // auto_ptr
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <typeinfo>

using namespace std;

// in place algorithms

//1.1

// find if a string has only unique chars.
// you can use sort, but it usually needs extra space
// you can use map. Especially if the string is usally small, than we don't need to allocate
// 256 bytes. Also, if it is unicode, than we should use map or bit vector.

bool unique_str(string &s)
{
    bool chars[256]; // assumed 8 bit char.

    // you should initialize array,
    for (int i = 0; i < 256; i++)
        chars[i] = false;
    
    for (int i = 0; i < s.size(); i++) {
        char c = s[i];
        if (chars[c]) return false;
        chars[c] = true;
    }
    
    return true;
    
}

//using bit vector, useful only with small letters
bool unique_str2(string &s)
{
    int w = 0;

    char c;

    for (int i = 0; i != s.size(); i++) {

        c = s[i];
        if (w & (1 << (c - 'a')))
            return false;

        w |= 1 << (c - 'a');
    }
    
    return true;
}



int t11()
{

    string a("abcdefg hi");
    string b("abcdefg hi ");
    cout << a << " : " << unique_str(a) << endl;
    cout << b << " : " << unique_str(b) << endl;
}



//1.2

void reverse(string &s)
{
    // front - back, going to each other until hit
    int i = 0;
    int j = s.size() - 1;

    while (i < j) {
        swap(s[i], s[j]);
        ++i;
        --j;
    }
    
}

// test for c style string
void reverse1(char *s)
{
    // front - back, going to each other until hit
    int i = 0;

    int j;
    
    for (j = 0; s[j] != 0; ++j);

    --j;

    cout << s << " : the size of str is " << j + 1 << endl;
    
    while (i < j) {
        swap(s[i], s[j]);
        ++i;
        --j;
    }
    
}

int t12()
{
    string s("this");
    cout << s << endl;
    
    reverse(s);
    
    cout << s << endl;
    
}

int t12_1()
{

    char s[] = {'T', 'h', 'i', 's', 0};

    cout << s << " " << strlen(s) << endl;
    
    reverse1(s);
    
    cout << s << endl;
    
}




//1.3
// test cases: null str, a, abcd, aaaa, aaabbb, ababab
// using remove method
void remove_dup(string &s)
{
    int ret;

    int len = s.size();
    
    // for each char in s
    for (int i = 0; i != len; i++){
        // len = remove(s.begin + 1, s.end, c);
        ret = i + 1;
        for (int j = i + 1; j != len; j++) {
            if (s[i] != s[j]) {
                s[ret++] = s[j];
            }
        }
        // update len
        len = ret;
    }
    s.resize(len);
}

// using find method in the same place
void remove_dup2(string &s)
{
    int ret = 1;
    int len = s.size();

    for (int i = 1; i < len; i++) {
        // k = find(ret.begin, ret.end, i)
        int j;
        for (j = 0; j < ret; j++) {
            if (s[j] == s[i])
                break;
        }
        if (j == ret) {
            s[ret++] = s[i];
        }
    }

    s.resize(ret);
    
}

// using additional info, which char has not unique.
// much faster than list search.
void remove_dup3(string &s)
{
    bool chars[256] = {false, };

    if (s.empty())
        return;
    
        
    // do I need to initialize it to false? or automatically initialized to false? YES, otherwise you got problem
    for (int i = 0; i < 256; i++)
        chars[i] = false;
    
    int ret = 1;
    char c = s[0]; // this may cause if the string is null
    
    chars[c] = true;
    
    for (int i = 1; i != s.size(); ++i) {

        c = s[i];
        if (!chars[c]) {
            
            s[ret++] = c;
            chars[c] = true;
        }
    }
    s.resize(ret);
}


void remove_dup4(string& s)
{
    if (s.size() == 0)
        return;

    string::iterator ret = s.begin() + 1;

    for (string::iterator it = s.begin() + 1; it != s.end(); ++it)
    {
        if (find(s.begin(), ret, *it) == ret)
            *ret++ = *it;
    }
    s.erase(ret, s.end());
}


int resize_test()
{
    int myints[] = {10,20,20,20,30,30,20,20,10};           // 10 20 20 20 30 30 20 20 10
    std::vector<int> myvector (myints,myints+9);

    // using default comparison:
    std::vector<int>::iterator it;
    it = std::unique (myvector.begin(), myvector.end());   // 10 20 30 20 10 ?  ?  ?  ?
    //                ^

    myvector.resize( std::distance(myvector.begin(),it) ); // 10 20 30 20 10
}

int t13()
{

    string s("abcdab");
    cout << "string is " << s << endl;
    remove_dup(s);
    cout << "string is " << s << endl;    
}


int t13_1()
{

    string s("abcdaaaabbbb");
    cout << "string is " << s << endl;
    remove_dup2(s);
    cout << "string is " << s << endl;

    string ss("");
    cout << "string is " << ss << endl;
    remove_dup2(ss);
    cout << "string is " << ss << endl;
    
}

int t13_2()
{

    string s("abcdaaaabbbb");
    cout << "string is " << s << endl;
    remove_dup3(s);
    cout << "string is " << s << endl;

    string ss("");
    cout << "string is " << ss << endl;
    remove_dup3(ss);
    cout << "string is " << ss << endl;
    
}

int t13_3()
{

    string s("abcdaaaabbbb");
    cout << "string is " << s << endl;
    remove_dup4(s);
    cout << "string is " << s << endl;

    string ss("");
    cout << "string is " << ss << endl;
    remove_dup4(ss);
    cout << "string is " << ss << endl;
    
    string s3("abcdab");
    cout << "string is " << s3 << endl;
    remove_dup3(s3);
    cout << "string is " << s3 << endl;    
}


//1.5

// this version needs copying elements for every insert.
void replace(string &s, string r)
{
    // which data structure we are using?
    // check if we need to reserve first. string needs reserve. so 
    // first step (first scan) would be to find out the size to reserve.

    int i, j;
    i = j= 0;

    while (i != s.size()) {
        if (s[i] == ' ')
            ++j;
        ++i;
    }

    s.reserve(s.size() + (r.size() - 1) * j); // resize should be performed before get iterator
    
    string::iterator it = s.begin();

    while (it != s.end()) {
        cout << * it << endl;
        
        if (*it == ' ') {
            it = s.erase(it); // erase or insert may change iterator. should use iterator returned. 
            s.insert(it, r.begin(), r.end()); // insert may change iterator. So, you have enough space reserved so that insert does not
            // allocate new memory.
            it += r.size();
        }
        ++it;
    }
}



// this version does not need copying element after replacing. 
void replace2(string &s, string r)
{

    int i, j;
    i = j = 0;

    for (i = 0; i != s.size(); ++i){
        if (s[i] == ' ')
            ++j;

    }
    int old_size = s.size();
    int new_size = s.size() + j * (r.size() - 1);

    cout << old_size << " , " << new_size << endl;
    
    s.resize(new_size); // we have to use resize, not reserve. reserve is just for reserving.
    // insert automatically increases size. But if we are using direct access using index, than
    // we have to resize.

    j = new_size - 1;

    for (i = old_size - 1 ; i != -1 ; i--) {
        if (s[i] == ' ') {
            for (int k = r.size(); k > 0; k--)
                s[j--] = r[k - 1];
        }
        else {
            
            s[j--] = s[i];
        }
    }   
}



void replace(vector<int> &va, vector<int> vb)
{
    int i, j;
    i = j = 0;

    for (i = 0; i != va.size(); i++){
        
        if (va[i] == 3)
            ++j;

    }

    va.reserve(va.size() + (vb.size() - 1) * j);
    
    vector<int>::iterator it = va.begin();
    
    while (it != va.end()) {
        if (*it == 3) {
            cout << "before " << va.size() << endl;
            it = va.erase(it);
            va.insert(it, vb.begin(), vb.end());
            cout << "after " << va.size() << endl;
            it += vb.size();
        }
        else ++it;
    }
}


int t15()
{
    string a("this is new world");
    string b("%20");

    replace(a, b);

    cout << a << endl;
}

int t15_2()
{
    string a("this is new world");
    string b("%20");

    replace2(a, b);

    cout << a << endl;
}

int t15_1()
{
    vector<int> va, vb;


    for(int i = 0; i < 10; i++)
        va.push_back(3);



    
    vb.push_back(1);
    vb.push_back(1);
    vb.push_back(2);
    vb.push_back(2);

    for (int i = 0; i < va.size(); i++)
        cout << va[i];
    cout << endl;
    
    for (int i = 0; i < vb.size(); i++)
        cout << vb[i];
    cout << endl;
    
    replace(va, vb);

    cout << " result : " << va.size() << endl;
    for (int i = 0; i < va.size(); i++)
        cout << va[i];
    cout << endl;
    
}




void set_row(vector<vector<int> > &m, int row)
{

    for(int i = 0; i < m[row].size(); i++)
        m[row][i] = 0;
}


void set_col(vector<vector<int> > &m, int col)
{
    for(int i = 0; i < m.size(); i++)
        m[i][col] = 0;

}

int find(vector<int> m, int val)
{
    int i = 0;
    
    while (i != m.size()) {
        if (m[i] == val)
            return i;
        ++i;
    }
    return i;
}


vector<vector<int> >
col_row(vector<vector<int> > m)
{
    vector<vector<int> > ret (m);
    
    for (int i = 0; i < m.size(); i++) {
        int j = find(m[i], 0);
        if (j != m[i].size()) {
            set_row(ret, i);
            set_col(ret, j);
        }
    }
    return ret;
}



// this is two phase algorithm using only col and row vector.
void
col_row2(vector<vector<int> > &m)
{
    vector<int> row;
    vector<int> col;
    
    
    for (int i = 0; i < m.size(); i++) {
        int j = find(m[i], 0);
        if (j != m[i].size()) {
            row.push_back(i);
            col.push_back(j);
        }
    }

    for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < m[i].size(); j++) {
            if (find(row, i) != row.size() ||
                    find(col, j) != col.size())
                m[i][j] = 0;
        }
    }
    
}


// when it comes to a matrix, it would be better to use array instead of vector.
// as we have to resize.
// we can use array, but it needs copy function. we can do that easily.
// but if we assume input is given, then vector is also ok.

int t17()
{
    vector<vector<int> > m, n;
    m.resize(3);
    m[0].resize(3);
    m[1].resize(3);
    m[2].resize(3);
    n.resize(3);
    n[0].resize(3);
    n[1].resize(3);
    n[2].resize(3);
    
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 1;
    m[1][0] = 1;
    m[1][1] = 0;
    m[1][2] = 7;
    m[2][0] = 3;
    m[2][1] = 1;
    m[2][2] = 0;

    for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < m[i].size(); j++) {
            cout << " " << m[i][j];
        }
        cout << endl;
    }
    
    n = col_row(m);

    cout << endl << " and the result is " << endl;
    
    for (int i = 0; i < n.size(); i++) {
        for (int j = 0; j < n[i].size(); j++) {
            cout << " " << n[i][j];
        }
        cout << endl;
    }
}

int t17_1()
{
    vector<vector<int> > m, n;
    m.resize(3);
    m[0].resize(3);
    m[1].resize(3);
    m[2].resize(3);
    n.resize(3);
    n[0].resize(3);
    n[1].resize(3);
    n[2].resize(3);
    
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 1;
    m[1][0] = 1;
    m[1][1] = 0;
    m[1][2] = 7;
    m[2][0] = 3;
    m[2][1] = 1;
    m[2][2] = 9;

    for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < m[i].size(); j++) {
            cout << " " << m[i][j];
        }
        cout << endl;
    }
    
    col_row2(m);

    cout << endl << " and the result is " << endl;

    for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < m[i].size(); j++) {
            cout << " " << m[i][j];
        }
        cout << endl;
    }


}

// remove duplicate for a linked list and map
struct node {
    node(int d) : data(d), next(NULL) {};
    int data;
    node* next;
};


void remove_dup5(node* n)
{
    if (n == NULL)
        return;
    
    map<int, int> mc;
    node* end = n;
    mc[n->data]++;

    n = n->next;
    while (n != NULL)
    {
        mc[n->data]++;

        if (mc[n->data] == 1)
        {
            end->next = n;
            end = n;
        }

        n = n->next;
    }
    end->next = NULL;
}

// remove duplicate in linked list
void t21()
{

    node* head = new node(2);
    node* end = head;
    end->next = new node(1);
    end = end->next;
    end->next = new node(2);
    end = end->next;
    end->next = new node(2);
    end = end->next;
    end->next = new node(3);
    end = end->next;
    end->next = new node(1);
    end = end->next;
    end->next = new node(3);
    end = end->next;

    node* n = head;
    while (n)
    {
        cout << n->data << endl;
        n = n ->next;
    }

    cout << "after" << endl;

    n = head;
    remove_dup5(n);
    while (n)
    {
        cout << n->data << endl;
        n = n ->next;
    }

    
}

class myq {
public:
    void enq(int x) 
    {
        a.push(x);
    }

    int deq()
    {
        while (!a.empty()) {
            b.push(a.top());
            a.pop();
        }
        int front = b.top();
        b.pop();

        while (!b.empty()) { // do we need this? follow the next queue implementation
            a.push(b.top());
            b.pop();
        }
        
        return front;
    }
    
private:
    stack<int> a, b;
};

class myq2 {
public:
    void enq(int x) 
    {
        a.push(x);
    }

    int size() 
    {
        cout << endl << " " << a.size() << " : " << b.size() << endl;
        return a.size() + b.size();
    }

    int deq()
    {
        int front;
        
        if (!b.empty()) {
            front = b.top();
            b.pop();
            return front;
        } 
            
        while (!a.empty()) {
            b.push(a.top());
            a.pop();
        }

        cout << "now a is empty" << endl;
        

        front = b.top();
        b.pop();

        return front;
    }
    
private:
    stack<int> a, b;
};

    

// implement stack. pop, push, and min. all in O(1).
class minstack
{
public:
    void push(int a)
    {
        int m;
        if (v.empty())
            m = 100000; // some max value. INT_MAX?
        else
            m = imin();
        m = min(a, m);
        v.push_back(pair<int, int>(a, m));
    }

    int pop()
    {
        int r = v[v.size() - 1].first;
        v.pop_back();
        return r;
    }

    int imin()
    {
        return v[v.size() - 1].second;
    }
private:
    // value, min
    vector<pair<int, int>> v;
    };
    
void t31()
{
    minstack ms;
    ms.push(3);
    ms.push(7);
    ms.push(1);
    ms.push(4);

    assert(1 == ms.imin());
    ms.pop();
    assert(1 == ms.imin());
    ms.pop();
    assert(3 == ms.imin());
    ms.pop();
    assert(3 == ms.imin());
}

int t35()
{
    myq mq;

    for (int i = 0; i < 10; i++) {
        mq.enq(i);
    }

    for (int i = 0; i < 10; i++)
        cout << mq.deq() << endl;
    
    
}

int t35_1()
{
    myq2 mq;

    for (int i = 0; i < 10; i++) {
        mq.enq(i);
    }

    for (int i = 0; i < 10; i++)
        cout << mq.deq() << endl;
    
    
}

stack<int>
sort_stack(stack<int> a)
{
    stack<int> b;
    
    while (!a.empty()) {

        int x = a.top();
        a.pop();

        while (!b.empty() && x < b.top()) {
            a.push(b.top());
            b.pop();
        }

        b.push(x);
        
    }
    return b;
    
    
}

//3.6
int t36()
{
    stack<int> a, b;

    a.push(3);
    a.push(1);
    a.push(4);

    b = sort_stack(a);

    cout << endl;
    
    while (!b.empty()) {
        
        cout << b.top() << endl;
        b.pop();
    }

}


int t_str_size()
{
    string s("this");
    cout << s << " " << s.size() << " " << s.capacity() << endl;

    s.reserve(100);
    cout << s << " " << s.size() << " " << s.capacity() << endl;

    s.resize(100);
    cout << s << " " << s.size() << " " << s.capacity() << endl;

    cout << "  :"<< s[6] << ": " << endl;

    s.append("no no");
    cout << s << " " << s.size() << " " << s.capacity() << endl;
    cout << "  :"<< s[100] << ": " << endl;
}

int t_ptr_test()
{

    int x[] = {1, 2, 3, 4, 5, 6, 7}; // for some reason, int *x does not work here.

    int *x2 = x + 1;
    
    int *y = x + 6;
#if 0
    // this line causes compile error
    int *z = (x2 + y) / 2;
#endif
    cout << endl << *x << endl;
    cout << *y << endl;
#if 0
    cout << *z << endl;
#endif
    
}

#include <pthread.h>
int t_thread_1()
{

    cout << "before join: " << pthread_self() <<  endl;
    int err = pthread_join(pthread_self(), NULL);
    cout << "after join: " << err << endl;
    
}




static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

static void *
threadFunc2(void * args)
{
    int err;
    
    err = pthread_mutex_lock(&mtx);
    if (err)
        cout << "error in mutex_lock" << endl;
    int x = *(int*)args;
    x++;
    *(int *)args = x;

    err = pthread_mutex_unlock(&mtx);
    if (err)
        cout << "error in mutex_unlock" << endl;
    
    cout << "thread with : " << x << " is created" << endl;
}

int t_thread_2()
{
    pthread_t t1, t2;

    int err, local;

    local = 2;

    err = pthread_create(&t1, NULL, threadFunc2, &local);
    if (err)
        cout << " error in creating thread 1 " << endl;

    err = pthread_create(&t2, NULL, threadFunc2, &local);
    if (err)
        cout << " error in creating thread 1 " << endl;
    
    err = pthread_join(t1, NULL);
    err |= pthread_join(t2, NULL);

    if (err)
        cout << " error joining threads " << endl;

}

struct mythread 
{
    pthread_t thread;
    bool term;
    int idx;
} *mythread;

static int numTerm = 0;


static void *
threadFunc3(void * args)
{
    int err;
    int i = *(int *)args;

    cout << "thread [" << i << "] is created" << endl;    

    err = pthread_mutex_lock(&mtx);
    if (err)
        cout << "error in mutex_lock" << endl;
    


    numTerm++;
    mythread[i].term = true;
    
    err = pthread_mutex_unlock(&mtx);
    if (err)
        cout << "error in mutex_unlock" << endl;
    
    err = pthread_cond_signal(&cond);
    if (err)
        cout << "error in cond_signal" << endl;
    

    return NULL;
}


int t_thread_3()
{

    int err;
    int numThread = 5;

    mythread = (struct mythread *)calloc(numThread, sizeof(*mythread));
    if (mythread == NULL)
        cout << "thread alloc error" << endl;
        
    int numLive = numThread;
    
    for (int i = 0; i < numLive; ++i) {
        mythread[i].idx = i;
        // if i is given to the last argument of pthread_create, then
        // the main thread may increase i, which can be seen by other threads.
        // so we should use local idx for each thread.
        err = pthread_create(&(mythread[i].thread), NULL, threadFunc3, &(mythread[i].idx));
        if (err)
            cout << " error in creating thread 1 " << endl;
    }

    while (numLive > 0) {
        err = pthread_mutex_lock(&mtx);
        if (err)
            cout << "mutex lock error" << endl;

        while (numTerm == 0) {
            err = pthread_cond_wait(&cond, &mtx);
            
            if (err)
                cout << "cond wait  error" << endl;
        }

        for (int i = 0; i < numThread; i++) {
            if (mythread[i].term) {
                mythread[i].term = false;
                err = pthread_join(mythread[i].thread, NULL);
                if (err)
                    cout << "error in join thread [" << i << "]" << endl;
                numTerm--;
                numLive--;
                cout << "joined thread [" << i << "]" << endl;
            }
        }
        
        err = pthread_mutex_unlock(&mtx);
        if (err)
            cout << "mutex unlock error" << endl;
            
    }

}

void test_swap_even_odd_bits()
{
	int a = 54;
	printf("the value of a is %d\n", a);
	int a1 = a << 1;
	int a2 = a >> 1;
	a = (a1 & 0xAAAAAAAA) |
        	(a2 & 0x55555555);
	printf("the value of new a is %d\n", a);
}

void get_number_of_bits()
{
   int a = 54;
	printf("the value of a is %d\n", a);
	int i = 0;
	if (a != 0) i++;
	while( (a = (a & (a - 1))) != 0) {
    	i++;

    	printf("[%d]the number of bits are %d\n", a, i);
	}
	printf("the number of bits are %d\n", i);

}



// swap inplace:
int t191()
{

    cout << "swap in place" << endl;

    int a, b;

    a = 5;
    b = 4;

    cout << "swap in place with " << a << " + " << b << endl;
    a = b - a;
    b = b - a;
    a = b + a;
    cout << "results:  " << a << " + " << b << endl;

    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
    cout << "results:  " << a << " + " << b << endl;

}

int rand5()
{
    return rand() % 5; //this might not correct..
}


int rand7()
{
    int n;

    do n = 5 * rand5() + rand5();
    while (n > 21);

    return (n % 7) + 1;
}



// nrand2 in acpp also can be used. But if rand5() is specialized function that does not
// takes arguement then...
int t1910()
{

    

}


// find int sumed up to a X: with map
int t1911()
{

    vector<int>vi;

    for (int i  = 11; i <= 20; i++) {
        vi.push_back(i);
    }

    map<int, int> mc;

    for (int i = 0; i != vi.size(); ++i) {
        mc[vi[i]]++;
    }

    cout << endl;
    
    // find vars sum up to 25;
    for (int i = 0; i != vi.size(); ++i) {
        int r = 25 - vi[i];
        if (mc[r] == 1) {
            cout << vi[i] << " + " << r << " == 25 " << endl;
            mc[r]++; // to remove duplications
            mc[vi[i]]++; // to remove duplications
        }
        
    }
    
}


// if the data is sorted, then we can do it in place with less then O-square
int t1911_1()
{
    vector<int>vi;

    for (int i  = 11; i <= 20; i++) {
        vi.push_back(i);
    }

    vector<int>::size_type i, j;

    sort(vi.begin(), vi.end());
    
    i = 0; j = vi.size() - 1;
    while (i < j)
    {
        while ((vi[i] + vi[j]) > 25)
            --j;
        if ((vi[i] + vi[j]) == 25)
            cout << vi[i] << " + " << vi[j] << " == 25" << endl;
        ++i;
    }

}


// test map_reduce
/*
 * worker thread
 * workq
 *
 * Q: how to choose chunk size? data band width and cache size?
 */ 
int t_thread_4()
{


}

int t_shared_ptr()
{
    shared_ptr<myq2> Ptr(new myq2);
    Ptr->enq(1);
    Ptr->enq(2);
    cout << endl << "  " << Ptr->deq() <<  " " << Ptr->deq() << " " << Ptr->size() <<  endl;
}


struct is_null
{
    bool operator()(std::auto_ptr<int> & a) const
    {
        return a.get() == 0;
    }
};

int t_auto_ptr()
{
    typedef std::auto_ptr<int> A;
    
    A a[] = { A(new int(1)), A(new int(0)), A(new int(2)), A(0) }; // a[i].get returns pointer. so, a[3] returns 0
    const int count = sizeof(a) / sizeof(a[0]);

    std::cout << std::count_if(a, a + count, is_null()) << " "  << a[1].get() << " " << a[3].get() << endl;
    
    A b = a[0]; // no two pointer points to the same object in auto_ptr. so a[0] is not null;
    A &c = a[1];
    a[3] = a[2];
    
    std::cout << std::count_if(a, a + count, is_null()) << " "  << a[0].get() << " " << a[1].get() << " "  << a[2].get() << " " << a[3].get() << endl;
    
    return 0;
}

class test_array 
{
public:
    test_array() 
    {

        cout << ++count << endl;
        
    }
    
    static int count;
};


int test_array::count = 0;

int t_array()
{
    // how to make 2 dimensional array in c++?


    // first method
    int sizeX  = 100;
    int sizeY = 100;
    
    
    int **ary = new int*[sizeY];

    for(int i = 0; i < sizeY; ++i) {

        ary[i] = new int[sizeX];

    }

    for(int i = 0; i < sizeY; ++i) {

        delete [] ary[i];

    }

    delete [] ary;

    
    //second method
    #if 0
    int *ary = new int[sizeX*sizeY];


    // ary[i][j] is then rewritten as
    ary[i*sizeY+j]


    #endif

    test_array a[5];
    test_array *b = new test_array[3];
}

class testConst 
{

private:
    const static int x;
    const static int y = 100;

};




// reinterpret_cast

#include <iostream>

class A
{

public:
    A() : m_i(0) 
    {
        cout << "default" << endl;
    }
    A(int n) { cout << "arg version" << endl; }
    A(const A& a) { cout << " copy " << endl; }
    ~A() { cout << " dest " << endl; }

protected:
    int m_i;

};


class B
{

public:
    B() : m_d(0.0) 
    {
    }


protected:
    double m_d;

};


class C
    : public A
    , public B
{

public:
    C() :  m_c('a') // if you want arg version of A, then add 'A(3)' here (assume arg is 3)
    {
    }


private:
    char m_c;

};



// refer to http://www.cplusplus.com/doc/tutorial/typecasting/ for more information.
int t_reinterpret_cast()
{

    C d;

    A *b1 = &d;

    B *b2 = &d;


    const int a = (reinterpret_cast<char*>(b1) == reinterpret_cast<char*>(&d)) ? 1 : 2;

    const int b = (b2 == &d) ? 3 : 4;
    //const int c = (b2 == b1) ? 5 : 6; // we cannot compare two different pointer types here

    const int c = (reinterpret_cast<char*>(b1) == reinterpret_cast<char*>(b2)) ? 5 : 6;
    const int e = (reinterpret_cast<char*>(b2) == reinterpret_cast<char*>(&d)) ? 7 : 8;


    cout << a << b << c << e << endl;

    // result is 1368
    return 0;

}

#if 0
class CBase 
{
    // in this case, there is no polymorphysim
};

class CDerived: public CBase 
{
};

#else
class CBase { virtual void dummy() {} }; // this case has polymorphism

class CDerived: public CBase { int a; };

#endif

int t_dynamic_cast()
{
#if 0
    CBase b;
    CDerived d;
    CDerived* pd;

    pb = dynamic_cast<CBase*>(&d);
// ok: derived-to-base

    pd = dynamic_cast<CDerived*>(&b); // compiler error. pointer to derived class can be dynamic_cast to its base regardless of its real object. no in the other direction.
// wrong: base-to-derived

#else
    CDerived k;
    CBase * pba = &k;//new CDerived;

    CBase * pbb = new CBase;

    CDerived* pd;
    
    pd = dynamic_cast<CDerived*>(pba); // if there is no polymorphism, then compile error here

    if (pd==0) cout << "Null pointer on first type-cast" << endl;


    pd = dynamic_cast<CDerived*>(pbb); // if there is no polymorphism, then compile error here

    if (pd==0) cout << "Null pointer on second type-cast" << endl;

#endif
}

#if 0
int t_static_cast()
{

    class CBase {};
    class CDerived: public CBase {};
    CBase * a = new CBase;
    CDerived * b = static_cast<CDerived*>(a); // it compiles but maybe runtime error.

    double d=3.14159265;
    int i = static_cast<int>(d); 
}
#endif

int t_typeid()
{
    int * a,b;
    a=0; b=0;
    if (typeid(a) != typeid(b))
    {
        cout << "a and b are of different types:\n";
        cout << "a is: " << typeid(a).name() << '\n';
        cout << "b is: " << typeid(b).name() << '\n';
    }
    return 0;
    
}

    
int t_stl_test1()
{

    typedef std::list<int> L;

    L l(5);


    typedef L::const_iterator CI;

    CI cb = l.begin(), ce = l.end();

    typedef L::iterator I;

    I b = l.begin();


    std::transform(cb, --ce, ++b, std::bind2nd(std::plus<CI::value_type>(), 1));

    std::copy(l.begin(), l.end(), std::ostream_iterator<CI::value_type>(std::cout)); //print

    std::cout << std::endl;


    return 0;

}

int t_stl_test2()
{
    

        binder2nd < less<int> > IsNegative (less<int>(),0);
        binder1st < less<int> > IsPositive (less<int>(),0);

        int numbers[] = {10,-20,-30,40,-50
        };

        int cx;

        cx = count_if (numbers,numbers+5,IsNegative);

        cout << "There are " << cx << " negative elements.\n";

        cx = count_if (numbers,numbers+5,IsPositive);

        cout << "There are " << cx << " positive elements.\n";

        return 0;

}



int t_ctor_dtor()
{
    A *p = 0;
    {
        const A a = 2;
        cout << "*****1" << endl; 
        p = new A[3];
        cout << "*****2" << endl; 
        p[0] = a;
        cout << "*****3" << endl; 
    }
    cout << "*****4" << endl; 
    p[1] = A(1);
    cout << "*****5" << endl; 
    p[2] = 2;
    cout << "*****6" << endl; 
    delete [] p;

    
    return 0;
}

// this is function object used as a comparer
struct P
{
    bool operator()(const int &n) const
    {
        return n % 3 == 0;
    }
};

int t_operator()
{
    const int a[] = { 5, 2, 6, 1, 13, 9, 19 };
    const int count = sizeof(a) / sizeof(a[0]);
    std::list<int> l(a, a+ count);
    std::cout << l.size();
    std::remove_if(l.begin(), l.end(), P());
    std::cout << l.size() << std::endl;
    
    return 0;
}


class D {
    D() : x(0) {
        ;
        }

private:
    const int x; // if a member is const, it can only be initialized in the member initialization. if we call 'x == 0' in the body of ctor, it is assignment
    // so it is compile error. Also, 'const int x = 0;' gives compile error asking to change it 'static const'
};


int t_vector()
{
    int a[] = {1, 1, 2, 2};
    int count = sizeof(a) / sizeof(a[0]);
    vector<int> va(a, a + count);

    cout << va[0] << va[1] << va[2] << va[3] << endl;

}


string
myreverse(const string& s)
{
    if (s.size() <= 1)
        return s;
    else {
        string r = myreverse(string(s.begin() + 1, s.end()));
        r.push_back(s[0]);
        return r;
    }
    
}

int t_reverse_str()
{

    string s("abc");

    string r = myreverse(s);

    cout << endl << s << " is reverse of " << r << endl;
    

}


struct CC
{

    bool operator()(const int &a, const int &b) const
    {

        return a % 10 < b % 10;

    }

};


int t_test_set()
{

    const int a[] = { 4, 2, 7, 11, 12, 14, 17, 2 
    };

    const int count = sizeof(a) / sizeof(a[0]);

    std::set<int> x(a, a + count);

    std::cout << x.size() << std::endl;

    std::set<int, CC> y(x.begin(), x.end());

    std::cout << y.size() << std::endl;

    for (set<int>::iterator it = y.begin(); it != y.end(); ++it) {
        cout << *it << endl;
    }
    


    return 0;

}

/*
 * other STL
 *
 * count, count_if 
 * unique
 * adjacent_find
 *
 * */


// how to partition if the size of data is too big?
// hash(str) mod r. Get hash value, mod r where r is the number of partitions

//todo: 1.6, 3.1

int equil_solution ( const vector<int> &A ) 
{
    unsigned int size = A.size();

    if (size == 0)
        return -1;

    unsigned int b = 0; // index should be non zero.. but might use int as well 
    unsigned int e = size;

    long long  sum = 0; // it should be signed, and it should be long long if the test cases is too big

    while (b != e) {
        sum += A[b];
        ++b;
    }
    
    sum -= A[0];
    long long  sum2 = 0; // check whether it is signed or unsigned

    b = 0;
    
    do {
        if (sum == sum2)
            return b;
        else {
            sum2 += A[b];
            ++b;
            sum -= A[b];
        }
        
    } while (b != e);
    
    return -1;
}

bool
overlap(const vector<int> &A, long long  x, long long y)
{
    long long x1 = x - A[x];
    long long x2 = x + A[x];

    long long y1 = y - A[y];
    long long y2 = y + A[y];

    if ((x1 <= y1 && y1 <= x2) ||
            (x1 <= y2 && y2 <= x2) ||
            (x1 <= y1 && y2 <= x2) ||
            (x2 >= y1 && y2 >= x2))
        return true;

    return false;
}


int overlap_solution (const vector<int> &A)
{
    int size = A.size();

    int r = 0;
    
    for (int i = 0; i !=size; ++i) {
        for (int j = i + 1; j != size; ++j) {

            if (overlap(A, i, j))
                    ++r;
        }
    }


    if (r > 10000000)
        return -1;
    
    return r;
    

}

bool comp_pair(pair<int, int> s1,
        pair<int, int> s2)
{
    return s1.first < s2.first;
}


int merge_pair(vector<int> a)
{

    vector<pair<int, int> > pa;

    for (int i = 0; i != a.size(); ++i) {
        pa.push_back(pair<int, int>(a[i], i));
    }

    cout << endl;
    
    for (int i = 0; i != pa.size(); ++i)
        cout << pa[i].first << " ";

    cout << endl;
    
    sort(pa.begin(), pa.end(), comp_pair);

    for (int i = 0; i != pa.size(); ++i)
        cout << pa[i].first << " ";

    cout << endl;
    
}

int test_merge_pair()
{

    int a[] = {1, 3, 2, 6, 4
    };

    vector<int> va(a, a + 5);

    merge_pair(va);
}


double mod_fib(double n)
{
    unsigned long long a;
    unsigned long long b;

    a = 0;
    b = 1;

    for (long i = 0; i < n; ++i) {

        unsigned long long temp = a;
        a = b;
        b = temp + a;
    }
    //cout << a << endl;
    
    return fmod(a, 10000103);
    
}

int test_mod_fib()
{

    double x = pow(2, 3);
    cout << endl << mod_fib(x) << endl;
    //mod_fib(x);
    

    x = pow (4, 7);
    cout << endl << x << " "  << mod_fib(x) << endl;
    //mod_fib(x);
    
}


int test1(int N)
{

    int i = 0;
    int maxr = 0;
    int j = 0;
    while (N > 0) {

        if ((N & 1) == 1) {
            if (i == 1) {
                maxr = max(maxr, j);
                j = 0;
            } else {
                if (i == 0)
                    i = 1;
            }
        } else {
            j++;
            
        }
        
        N = N >> 1;   

    }
    
    return maxr;
}

int test2(int A, int B, int K)
{

    int x = A % K;

    int y = B % K;


    A = A + (K - x)%K;

    B = B - (K - y)%K;

    if (B > A) {
        
        return 1 + ((B - A) / K);
        
        
    } else if (B == A) {
        return 1;
    }

    return 0;
    
}

int test3(int A, int B, int C)
{

    int x = max(A, B);
    int y = max(A, C);

    if (x == y) return max(B,C);
    else return A;
}

double cube_root( double d ) 
{
    return pow( d, 1.0 / 3);
}


int test4(int A, int B)
{

    int x, y;
    
    double a = cube_root(A);
    x = a;

    if ((double)x < a)
        x++;
    
    double b = cube_root(B);
    y = b;

    cout << endl << "a = " << a << " and b = " << b << endl;
    
    if (y > x) {
        return 1 + (y - x);
    }
    else if (x == y) {
        return 1;
    }
    return 0;
}




class AA
{
public:
    friend ostream& operator<<(ostream&, const AA&);
    
    AA(int i = 0) :_x(i) 
    {

    }

    AA(const AA& a) : _x(a._x) 
    {

    }

    AA& operator=(const AA& a)
    {
        if (this == &a) return *this; // should put this here..
        
        _x = a._x;
        return *this;
    }

    int getx()
    {
        return _x;
    }
    
    
    virtual int gettype()
    {
        return 1;
    }

    virtual ~AA()
    {

    }

private:
    int _x;
};

class BB : public AA 
{
public:

    friend ostream& operator<<(ostream&, const BB&);
    BB(int i = 1) : AA(i) 
    {

    }
    BB(const BB& b) : AA(b) 
    {
        
    }

    BB& operator=(const BB& b)
    {
        AA *a = this;
        *a = b;

        return *this;
    }
    
    int gettype()
    {
        return 2;
    }

    virtual ~BB()
    {


    }

private:
    int _y;
};



ostream&
operator<<(ostream& os, const AA& a)
{
    os << a._x;
    return os;
}


ostream&
operator<<(ostream& os, const BB& b)
{
    
    os << b._y; // how can I print a._x? no?
    return os;
}


class AAA
{
public:
    virtual void foo() = 0;

    virtual ~AAA() 
    {
    }
    
};


class BBB : public AAA 
{
public:
    BBB(int i = 0) :  x(i)
    {
    }
    
    void foo() 
    {

        cout << "foo is called in BBB with " << x << endl;
    }
    virtual ~BBB() 
    {


    }

private:
    int x;
    
};


int test_inherit()
{

    AA a;
    BB b;
    AA a1(1);
    BB b2(b);
    BB b3(3);
    AA * pa;
    pa = &b2;
    
    

    cout << a.getx() << " " << b.getx() << " " << a1.getx() << " " << b2.getx() << endl;
    cout << a.gettype() << " " << b.gettype() << " " << a1.gettype() << " " << b2.gettype() << endl;
    cout << "after assignment" << endl;
    b2 = b3;
    cout << a.getx() << " " << b.getx() << " " << a1.getx() << " " << b2.getx() << endl;
    cout << a.gettype() << " " << b.gettype() << " " << a1.gettype() << " " << b2.gettype() << endl;
    cout << "test print" << endl;
    cout << a << " " << b << " " << a1 << " " << b2 << endl;

    BBB b4(4);
    AAA *a4 = &b4;
    
    
    cout << "finally " << pa->gettype() << " and ";
    a4->foo();
}




 // hash example
void hashTest ()
{
  char nts1[] = "Test";
  char nts2[] = "Test";
  std::string str1 (nts1);
  std::string str2 (nts2);

  std::hash<char*> ptr_hash;
  std::hash<std::string> str_hash;

  std::cout << "same hashes:\n" << std::boolalpha;
  std::cout << "nts1 and nts2: " << (ptr_hash(nts1)==ptr_hash(nts2)) << '\n';
  std::cout << "str1 and str2: " << (str_hash(str1)==str_hash(str2)) << '\n';
}   
    

// given a sorted array, create binary tree with minimal height
void t43()
{



}


// find next node in binary search tree (in order successor) where
// each node has pointer to its parent
#if 0

int search_min(tree* n)
{
if (n->left)
    return search_min(n->left);

return n->data;
}

int search_next(tree* n)
{
    int k = n->data;
    if (n->right)
        return search_min(n->right);
    else
    {
        while (n->data <= k)
        {
            n = n->parent;
            if (n == null)
            {
                cout << "the last element";
                return -1;
            }
        }
        return n->data;
    }
}
#endif
void t45()
{

}

// Design an algorithm and write code to find the first common 
// ancestor of two nodes in a binary tree Avoid storing 
//additional nodes in a data structure NOTE: This is not 
// necessarily a binary search tree
tree* cover(tree*n, tree*a, tree*b)
{
b1 = search(n->left, a);
b2 = search(n->left, b);
b3 = search(n->right, a);
b4 = search(n->right, b);

if (b1 && b2)
    return cover(n->left, a, b);

if (b3 && b4)
    return cover(n->right, a, b);

if ((b1 && b4) || (b2 && b3))
    return n;

return NULL;
}

void t46()
{
}


// You have two very large binary trees: T1, with millions of nodes, and T2, 
// with hun- dreds of nodes Create an algorithm to decide if T2 is a subtree of T1
void t47()
{

}


// given a binary tree in which each node contains a value Design an 
// algorithm to print all paths which sum up to that value Note that 
// it can be any path in the tree - it does not have to start at the root
void t48()
{

}

int main()
{
    t31();
}


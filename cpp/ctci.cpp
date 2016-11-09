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
#include <random>

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

void rotate(string &s, int middle)
{
    int first = 0;
    int last = s.size();
    int next = middle;
    while (first != next)
    {
        swap(s[first++], s[next++]);

        if (next == last) // this comparison go first otherwise endless loop
        {
            next = middle;
        }
        else if (first == middle)
        {
            middle = next;
        }
    }
}


void test_string_rotate()
{
    string s;
    int idx;

    cin >> s >> idx;

    rotate(s, idx);

    cout << "the result is " << s << endl;
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

// void remove_dup5(string& s) { use map<char, int> and iterate. it is sorted though.. 

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


void col_row(vector<vector<int>>& m)
{

    set<int> col, row;
    
    for (int i = 0; i < m.size(); ++i)
    {
        for (int j = 0; j < m[1].size(); ++j)
        {
            if (m[i][j] == 0)
            {
                col.insert(j);
                row.insert(i);
            }
        }
    }

    for (auto& e: col)
    {
        set_col(m, e);
    }

    for (auto& e: row)
    {
        set_row(m, e);
    }
}



// this is two phase algorithm using only col and row vector.
void
col_row2(vector<vector<int> > &m)
{
    // instead of row and col as vector,
    // consider using set. As it removes redundancy
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

// how to create 2 dimensional vector?
//
// vector< vector<int> > vec(4, vector<int>(4));
//
//



// when it comes to a matrix, it would be better to use array instead of vector.
// as we have to resize.
// we can use array, but it needs copy function. we can do that easily.
// but if we assume input is given, then vector is also ok.

int t17()
{
    vector<vector<int> > m;
    m.resize(3);
    m[0].resize(3);
    m[1].resize(3);
    m[2].resize(3);
    
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
    
    vector<vector<int>> n(m);
    col_row(n);

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

node* reverse_list(node* a)
{
    if (!a)
        return a;

    node* prev = a;
    a = a-> next;
    prev->next = NULL;

    while (a) 
    {
        node* next = a->next;
        a->next = prev;
        prev = a;
        a = next;
    }

    return prev;
}

// 1->2->3->4 to 2->1->4->3
node* reverse_list_every_other(node* a)
{
    if (!a)
        return a;

    node* r = a->next? a->next: a;

    node* prev = nullptr;

    while (a && a->next) 
    {
        if (prev)
            prev->next = a->next;

        prev = a;
        a = a-> next;
        node* next = a->next;

        a->next = prev;
        prev->next = next;
        a = next;
    }

    return r;
}


node* merge_list(node*a, node*b)
{
// merge two list into one
    if (!a)
        return b;
    if (!b)
        return a;

    node* ret = a;
    node* prev = nullptr;

    while (true)
    {
        if (!a)
        {
            prev->next = b;
            return ret;
        }
        else if (!b)
        {
            return ret;
        }
        else
        {
            if (a->data < b->data)
            {
                prev = a;
                a = a->next;
            }
            else
            {
                node* next = b->next;
                if (prev)
                {
                    prev->next = b;
                }
                else
                {
                    ret = b;
                }
                prev = b;
                b->next = a;
                b = next;
            }
        }
    }
}

void test_reverse_linked_list()
{
    node* head = new node(1);
    node* end = head;
    end->next = new node(2);
    end = end->next;
    end->next = new node(3);
    end = end->next;
    end->next = new node(4);
 

    // node* r = reverse_list(head);
    node* r = reverse_list_every_other(head);

    while (r)
    {
        cout << r->data << " ";
        r = r-> next;
    }

    cout << endl;
}

void test_merge_linked_list()
{
    node* head = new node(1);
    node* end = head;
    end->next = new node(3);
    end = end->next;
    end->next = new node(4);
    end = end->next;
    end->next = new node(7);
 
    node* head2 = new node(2);
    node* end2 = head2;
    end2->next = new node(4);
    end2 = end2->next;
    end2->next = new node(5);
    end2 = end2->next;
    end2->next = new node(6);

    node* r = merge_list(head, head2);

    while (r)
    {
        cout << r->data << " ";
        r = r-> next;
    }

    cout << endl;
}


pair<node*, node*> skip_zero(node* n)
{
    node* first = n;
    node* prev = nullptr;

    while (n && n->data == 0)
    {
        prev = n;
        n = n->next;
    }

    return pair<node*, node*>(prev, n);
}

pair<node*, node*> reverse_one_word(node* a)
{
    if (!a)
        return pair<node*, node*>(a, a);

    node* prev = a;
    node* head = a;
    a = a-> next;

    while (a && a->data != 0) 
    {
        node* next = a->next;
        a->next = prev;
        prev = a;
        a = next;
    }

    head->next = a;
    return pair<node*, node*>(prev, a);
}


node* reverse_word(node* n)
{
    node* head = n;

    while (n)
    {
        pair<node*, node*> a = skip_zero(n);
        pair<node*, node*> b = reverse_one_word(a.second);

        if (a.first)
            a.first->next = b.first;
        else
            head = b.first;

        n = b.second;
    }

    return head;
}

void test_reverse_word()
{
    node* head = new node(0);
    node* end = head;
    end->next = new node(1);
    end = end->next;
    end->next = new node(2);
    end = end->next;
    end->next = new node(0);
    end = end->next;
    end->next = new node(3);
    end = end->next;
    end->next = new node(4);

    node* r = reverse_word(head);
    while (r)
    {
        cout << r->data << " ";
        r = r-> next;
    }

    cout << endl;
}


void test_merge_k_sorted_list()
{

    // merge k list of length n
    // with nklogk

    // 1) using heap of length k
    // 2) logk means tree, so merge two list of size n, then 2n,..., and at the logk step
    //    merge all
}

void test_swap_nodes()
{
    
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
            (x1 >= y1 && y2 >= x2))
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
    if (n->right)
        return search_min(n->right);

    node* p = n->parent;

    while (p)
    {
        if (n == p->left)
        {
            return n->data;
        }
        n = p;
        p = p->parent;
    }

    cout << "last element" << endl;
    return 0;
}
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

#endif

// You have two very large binary trees: T1, with millions of nodes, and T2, 
// with hun- dreds of nodes Create an algorithm to decide if T2 is a subtree of T1

#if 0
Note that the problem here specifies that T1 has millions of nodes
this means that we should be careful of how much space we use Lets say,
 for example, T1 has 10 million nodes thismeansthatthedataaloneisabout40mb 
Wecouldcreateastringrepresenting the inorder and preorder traversals If T2s 
preorder traversal is a substring of T1s preorder traversal, and T2s inorder 
traversal is a substring of T1s inorder traversal, then T2 is a sub- string
 of T1 We can check this using a suffix tree However, we may hit memory 
limitations because suffix trees are extremely memory intensive If this 
become an issue, we can use an alternative approach
                                   
Alternative Approach: The treeMatch procedure visits each node in the small 
tree at most once and is called no more than once per node of the large tree 
Worst case runtime is at most O(n * m), where n and m are the sizes of trees 
T1 and T2, respectively If k is the number of occurrences of T2s root in T1, 
the worst case runtime can be characterized as O(n + k * m)

Another alternative is using parallelism. async is a way.
    
Or let each node have a hash (or similar) value which can represent
nodes under the root node
#endif
    

// https://en.wikipedia.org/wiki/Suffix_array
void t47()
{

}


// given a binary tree in which each node contains a value Design an 
// algorithm to print all paths which sum up to that value Note that 
// it can be any path in the tree - it does not have to start at the root
void t48()
{

}

// circular buffer

class cb {
public:
    cb() : availspace(10), 
           capacity(10), 
           availitem(0), 
           head(0), 
           tail(0), 
           data{new char[10]}
    {
    }
    
    int put(char* vi, int len)
    {
        int bytes_written = (len > availspace)? availspace : len;
        availspace -= bytes_written;
        availitem += bytes_written;
        for (int i = 0; i < bytes_written; ++i)
            putitem(vi[i]);
            
        return bytes_written;
    }

    void putitem(char x)
    {
        int i = tail;
        data[i] = x;
        tail = (++i == capacity)? 0 : i;
    }
    
    int get(char* vo, int len)
    {
        int bytes_read = (len > availitem)? availitem : len;
        availitem -= bytes_read;
        availspace += bytes_read;

        for (int i = 0; i < bytes_read; ++i)
            vo[i] = getitem();
            
        return bytes_read;
    }
    
    char getitem()
    {
        int i = head;
        char x = data[i];
        head = (++i == capacity)? 0 : i;
        return x;
    }

private:
    int availspace;
    int availitem;
    int capacity;
    int head;
    int tail;
    char* data;
};



void t131()
{
    cb c;
    char ca[] = "1234567890abcdefgh";
    char ra[20];

    memset(ra, 0, 20);

    ra[1] = 0;
    int r = c.put(ca, 8);
    cout << r << endl;

    r = c.get(ra, 2);
    cout << r << endl;
    
    r = c.put(ca, 8);
    cout << r << endl;

    r = c.get(ra + 2, 2);
    cout << r << endl;

    r = c.get(ra + 4, 9);
    cout << r << endl;


    cout << ra << endl;
}

// find the last N lines in a file

void t132()
{
    // use array in a circular way
}


// merge to arrays into one, one with N + M size (N filled) and the other is M.
// Merge into N + M size array.
void test_merge_array()
{

    vector<int> a(10);
    vector<int> b = {1, 2, 7, 9, 11};

    int x[] = {3, 4, 5, 6, 8};
    
    for (int i = 0; i < 5; ++i)
        a[i] = x[i];
        
    auto first1 = a.begin();
    auto last1 = a.begin() + 5;
    auto first2 = b.begin();
    auto last2 = b.end();
    auto ret = a.end();
    
    while (true)
    {
        if (first1 == last1)
        {
            copy(first2, last2, first1);
            break;
        }
        else if (first2 == last2)
        {
            break;
        }
        else
        {
            *(--ret) = *(last1 - 1) > *(last2 -1) ? *(--last1) : *(--last2);
        }
    }

    for (auto e : a)
        cout << e << " ";

    cout << endl;
}

// given a sorted array and a character, print the number of characters

// this method returns the begining index of the character.
// if there is no such character then it returns the position which it should be exist
int find_beg(vector<char>& vc, int i, int j, char t)
{
    if (i > j)
        return i;
    int mid = i + (j - i) / 2;

    if (vc[mid] == t)
        return find_beg(vc, i, mid - 1, t);
    else if (vc[mid] > t)
        return find_beg(vc, i, mid - 1, t);
    else
        return find_beg(vc, mid + 1, j, t);
}


int find_beg2(vector<char>& vc, int i, int j, char t)
{
    while(i <= j)
    {
        int mid = i + (j - i) / 2;

        if (vc[mid] == t)
            j = mid - 1;
        else if (vc[mid] > t)
            j = mid - 1;
        else
            i = mid + 1;
    }

    return i;
}


// this method returns the begining index of the next character.
// if there is no such character then it returns the position which it should be exist
int find_end(vector<char>& vc, int i, int j, char t)
{
    if (i > j)
        return i;
    
    int mid = i + (j - i) / 2;

    if (vc[mid] == t)
        return find_end(vc, mid + 1, j, t);
    else if (vc[mid] > t)
        return find_end(vc, i, mid - 1, t);
    else
        return find_end(vc, mid + 1, j, t);
}


int find_end2(vector<char>& vc, int i, int j, char t)
{
    while(i <= j)
    {
        int mid = i + (j - i) / 2;

        if (vc[mid] == t)
            i = mid + 1;
        else if (vc[mid] > t)
            j = mid - 1;
        else
            i = mid + 1;
    }

    return i;
}


int find_pos(vector<char>& vc, int i, int j, char t)
{
    if (i > j)
        return -1;// that means it did not find any
    
    int mid = i + (j - i) / 2;

    if (vc[mid] == t)
        return  mid;
    else if (vc[mid] > t)
        return find_pos(vc, i, mid - 1, t);
    else
        return find_pos(vc, mid + 1, j, t);
}

void test_count_char_in_sorted_array()
{
    string s;
    cin >> s;

    vector<char> vc(s.begin(), s.end());

    char t;
    cin >> t;
    
    int i = find_beg(vc, 0, vc.size() - 1, t);
    int j = find_end(vc, 0, vc.size() - 1, t);
    int k = find_pos(vc, 0, vc.size() - 1, t);

    cout << " the result is " << i << " " << j << " " << k << endl;
    i = find_beg2(vc, 0, vc.size() - 1, t);
    j = find_end2(vc, 0, vc.size() - 1, t);
    cout << " the result is " << i << " " << j << " " << k << endl;
 }


// Given a set of intervals such as (10,20), (15,25), (28,40), (50,70), (0,9) 
// (60,90) and build a data structure. Query the data structure for point x, 
// and it find out all the intervals that contain this point x.
// this method returns the begining index of the character.
// if there is no such character then it returns the position which it should exists
int find_beg(vector<pair<int, int>>& vc, int i, int j, int t) {
    if (i > j)
        return i;
    int mid = i + (j - i) / 2;

    if (vc[mid].second == t)
        return find_beg(vc, i, mid - 1, t);
    else if (vc[mid].second > t)
        return find_beg(vc, i, mid - 1, t);
    else
        return find_beg(vc, mid + 1, j, t);
}

// this method returns the begining index of the next character.
// if there is no such character then it returns the position which it should exists
int find_end(vector<pair<int, int>>& vc, int i, int j, int t) {
    if (i > j)
        return i;
    
    int mid = i + (j - i) / 2;

    if (vc[mid].first == t)
        return find_end(vc, mid + 1, j, t);
    else if (vc[mid].first > t)
        return find_end(vc, i, mid - 1, t);
    else
        return find_end(vc, mid + 1, j, t);
}


void test_find_interval()
{
    // sort intervals with first number, and store it to array a
    // sort intervals with last number, and store it to array b
    // given number x, binary search in the a->k and b->l 
    // then set_intersection(a[:k], b[l:]) would be the answer.
    // To improve speed, this set intersection can be precomputed for each(k,l)
    // where k and l are in [0, sizeof(intervals)], so the computation is just
    // binary search for finding k and l, which is O(log(n))

    int n;

    cin >> n;

    using pos = pair<int, int>;
    vector<pos> v;
    for (int i = 0; i < n; ++i)
    {
        int x, y;
        cin >> x >> y;

        v.push_back(pos(x, y));
    }

    int k;
    cin >> k;
    
    vector<pos> a(v);
    vector<pos> b(v);

    sort(a.begin(), a.end(), [](pos x, pos y) {return x.first < y.first; });
    int i = find_end(a, 0, a.size() - 1, k);

    sort(b.begin(), b.end(), [](pos x, pos y) {return x.second < y.second; });
    int j = find_beg(b, 0, b.size() - 1, k);

    vector<pos> r;
    set_intersection(a.begin(), a.begin() + i, b.begin() + j, b.end(),
                     back_inserter(r));

    cout << " And the result is " << endl;
    for (auto&e : r)
        cout << e.first << "," << e.second << endl;

    cout << endl;
}


// implement how to find lru map element if the number of element in the map
// hits to the max. We only have 1000 element in the map, and later should
// replace old one with new one.

class lrumap {
private:

    class node {
    public:
        node(string s, int x) : str(s), data(x), prev(NULL), next(NULL) {}
        int data;
        string str;
        node* prev;
        node* next;
    };
    node* head;
    node* tail;
    map<string, node*> mm;
    int size;
 
public:
    lrumap(int sz) : size(sz) {}
    
    int get(string& s)
    {
        if (mm.find(s) != mm.end())
        {
            node* n = mm[s];

            // set the node as the head of the list
            if (n == head && n == tail)
            {
                // do nothing
            }
            else if (n == head)
            {
                // do nothing
            }
            else if (n == tail)
            {
                tail = tail->prev;
                tail->next = nullptr;

                n->next = head;
                n->prev = nullptr;
                head = n;
            }
            else
            {
                n->prev->next = n->next;
                n->next->prev = n->prev;

                n->next = head;
                n->prev = nullptr;
                head = n;
            }

            return n->data;
        }
        else
        {
            return 0;
        }
    }

    void put(string& s, int i)
    {
        node* n;

        if (mm.size() == size)
        {
            n = tail;
            n->prev = nullptr;
            mm.erase(mm.find(n->str));
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
        {
            n = new node(s, i);
        }

        n->next = head;
        head = n;
        mm[s] = n;
    }
};
    

void test_lru()
{
}


// partition int array with k, so that k puts together, smaller than k goes left,
// and bigger than k goes to right.
void test_partition_using_k()
{
    int n, k;
    cin >> n;
    vector<int> v;
    
    for (int i = 0; i < n; ++i)
    {
        int t;
        cin >> t;
        v.push_back(t);
    }

    cin >> k;

    auto a = partition(v.begin(), v.end(), [&](int x) { return x < k; }); 
    partition(a, v.end(), [&](int x) { return x == k; }); 

    cout << "the result is" << endl;

    for (auto &e: v)
        cout << e << " ";

    cout << endl;
}


// given an array of (start price, daily high, daily low), find the best
// period for buy and sell (gap between buy and sell is highest)
void test_find_best_investment_period_once()
{
    // for x = [2, 3, 5, 1, 9],
    //     y = [7, 6, 4, 8, 0]. y[i] = max(x[i+1] - x[i], x[i+1] - x[i] + y[i+1]);  
    // then for the biggest element (biggest gap)  in y, find interval

    vector<int> v;
    int n;

    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        int t;
        cin >> t;
        v.push_back(t);
    }

    int m_max = 0;
    int k = 0;
    int beg;
    int end = v.size() - 1;
    for (int i = v.size() - 2; i >= 0; --i)
    {
        int t = v[i + 1] - v[i];
        k = max(t, t + k);
        if (k > m_max)
        {
            m_max = k;
            beg = i;

            if (v[end] < v[i])
                end = i;
        }

    }

    cout << "the result is " << m_max << " begin at " << beg << " and ends at " << end << endl;
}


// find the best investment period of buying and selling twice
void test_find_best_investment_period_twice()
{
    vector<int> v;
    int n;

    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        int t;
        cin >> t;
        v.push_back(t);
    }

    int end = v.size() - 1;

    vector<int> v1(v.size());
    vector<int> v2(v.size());

    v1[end] = 0;
    for (int i = v.size() - 2; i >= 0; --i)
    {
        int t = v[i + 1] - v[i];
        v1[i] = max(t, t + v1[i + 1]);
    }

    v2[0] = 0;
    int m_min = v[0]; 
    for (int i = 1; i < v.size(); ++i)
    {
        v2[i] = v[i] - m_min;
        m_min = min(m_min, v[i]);
    }

    int m_max = 0;
    for  (int i = 1; i < v.size() - 1; ++i)
    {
        int t = v2[i] + v1[i + 1];
        m_max = max(m_max, t);
    }

    cout << "the result is " << m_max << endl;
}

//
// Given a file with a lot of words (10 million) find out the top 10%
// most frequently occurring words.
//

void test_find_10_percent_from_10_milion_words()
{
// run map for each word, count how big is it, then calculate 10%, make heap with that size,
// run each word in the map and find 10%. Is it OK?

// can we split and gather/merge the result? No, as 10M * sizeof(word) can be
// enough for memory usage for heap structure and hash map. O(n) is data usage.
// or just want to see how to implement heap? Yes, with some explanation of memory usage

}


/*
There are N houses in a row. Each house can be painted in either Red, Green or Blue color. The cost of coloring each house in each of the colors is different.
Find the color of each house such that no two adjacent house have the same color and the total cost of coloring all the houses is minimum.

Update: The question intends to state that cost of painting any house in any color is different, so if cost of painting House 1 in Red is say, X then the cost of painting House 2 in red will some other value Y. It can be considered each house has different dimensions and hence cost of painting in each color is different, and the cost of paint for each house also varies
*/

void test_paint_house_with_3_colors()
{
    // If the cost for painting is same across all houses, then just start
    // with a cheapest color, then next with second cheap, then third with
    // cheapest color, until all houses are painted.


    // If the costs for painting is different across all houses, then
    // assume cost[n][3] is the cost of painting each n houses,
    // compute total_cost[n][3] be the total cost for painting. 


    int n;
    cin >> n;

    vector<vector<int>> v(n,vector<int>(3));
    for (int i = 0; i < n; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;
        v[i][0] = a;
        v[i][1] = b;
        v[i][2] = c;
    }

    vector<vector<int>> vr(n,vector<int>(3));
    
    vr[n - 1][0] = v[n - 1][0];
    vr[n - 1][1] = v[n - 1][1];
    vr[n - 1][2] = v[n - 1][2];

    for (int i = n - 2; i >= 0; --i)
    {
        vr[i][0] = v[i][0] + min(vr[i + 1][1], vr[i + 1][2]);
        vr[i][1] = v[i][1] + min(vr[i + 1][0], vr[i + 1][2]);
        vr[i][2] = v[i][2] + min(vr[i + 1][1], vr[i + 1][0]);
    }

    int r = min(min(vr[0][0], vr[0][1]), vr[0][2]);
    cout << "The result is " << r << endl;
}


// with two rectangle, if they are intersect then return
// the intersection area
struct rect {
    int x, y, width, height;
};

bool is_intersect(const rect& r1, const rect& r2)
{
    return !((r1.x > r2.x + r2.width) ||
             (r2.x > r1.x + r1.width) ||
             (r1.y > r2.y + r2.height) ||
             (r2.y > r1.y + r1.height));
}

rect intersect(const rect& r1, const rect& r2)
{
    if (is_intersect(r1, r2))
    {
        return rect{
            max(r1.x, r2.x), max(r1.y, r2.y),
            min(r1.x + r1.width, r2.x + r2.width) - max(r1.x, r2.x),
            min(r1.y + r1.height, r2.y + r2.height) - max(r1.y, r2.y)};
    }
    else
    {
        return rect{0,0,-1,-1};
    }
}

void test_rect_intersect()
{
    int x, y, w, h;
    cin >> x >> y >> w >> h;
    rect r1{x, y, w, h};
    
    cin >> x >> y >> w >> h;
    rect r2{x, y, w, h};

    rect r = intersect(r1, r2);

    cout << "the result is " << r.x << " " << r.y << " " << r.width << " " << r.height << endl;

}

// this implementation assume that we just copy as small as possible
// do not copy overlapping area
void acopy(vector<int>* v, int s, int l, int t)
{
    vector<int>& vi = *v;

    if (s == t)
        return;
    else if (s > t)
    {
        int l1 = s - t;
        l1 = min(l, l1);
        l1 = min(l1, int(vi.size() - s));
        while (l1 > 0)
        {
            vi[t++] = vi[s++];
            --l1;
        }
    }
    else
    {
        int l1 = t - s;
        l1 = min(l, l1);
        l1 = min(l1, int(vi.size() - t));
        while (l1 > 0)
        {
            vi[t++] = vi[s++];
            --l1;
        }
    }
}

// this test is simple but you need to ask questions for the
// overlapping and edge cases before implement.
void test_copy_in_array()
{
    int n;

    vector<int> v;

    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        int t;
        cin >> t;
        v.push_back(t);
    }

    int s, t, l;
    cin >> s >> l >> t;

    acopy(&v, s, l, t);

    cout << "the result is" << endl;

    for (int i = 0; i < v.size(); ++i)
    {
        cout << v[i] << " ";
    }
    cout << endl;
}


void test_apply_perm()
{
    string a;
    vector<int> v;

    cin >> a;
    for (int i = 0; i < a.size(); ++i)
    {
        int t;
        cin >> t;
        v.push_back(t);
    }

    for (int i = 0; i < v.size(); ++i)
    {
        int idx = i;

        while (v[idx] >= 0)
        {
            int next = v[idx];
            swap(a[i], a[next]);
            v[idx] -= v.size(); // just in case we need to restore v
            idx = next;
        }
    }

    cout << "the result is " << a << endl;
}

void next_perm(vector<int>* pv)
{
    vector<int>& v = *pv;

    for (int i = v.size() - 2; i >= 0; --i)
    {
        if (v[i] < v[i + 1])
        {
            int min_j = i + 1;
            for (int j = i + 2; j < v.size(); ++j)
            {
                if ((v[j] > v[i]) && (v[j] < v[min_j]))
                    min_j = j;
            }
            swap(v[i], v[min_j]);

            // then reverse all from i + 1 to the end
            reverse(v.begin() + i + 1, v.end());
            return;
        }
    }

    v.clear();
    return;
}


// find next permutation without recursive call
void test_next_perm()
{
    int n;
    vector<int> v;

    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        int t;
        cin >> t;
        v.push_back(t);
    }

    while(!v.empty())
    {
        next_perm(&v);
        for (int e: v)
            cout << e << " ";
        cout << endl;
    }
    cout << "no more permutation" << endl;
}
    
            
int find_min_from_sorted_rotated(const vector<int>& v, int a, int e)
{
    if (v[a] <= v[e])
        return v[a];

    int mid = a + (e - a) / 2;
    int min1 = min(v[a], v[mid]);
    int min2 = min(v[mid + 1], v[e]);

    if (min1 > min2)
        return find_min_from_sorted_rotated(v, mid + 1, e);
    else
        return find_min_from_sorted_rotated(v, a, mid);
}


void test_find_min_from_sorted_rotated_array()
{
    int n;
    vector<int> v;

    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        int t;
        cin >> t;
        v.push_back(t);
    }

    cout << "the result is " ;
    cout <<  find_min_from_sorted_rotated(v, 0, v.size() - 1) << endl;
}

void test_find_rand_comb()
{
    int n;
    vector<int> v;

    cin >> n;
    for(int i = 0; i < n; ++i)
    {
        int t;
        cin >> t;
        v.push_back(t);
    }

    int k;

    cin >> k;
    
    default_random_engine seed((random_device())()); // random num generator
    for (int i = 0; i < k; ++i)
    {
        swap(v[i], v[uniform_int_distribution<int>{
                    i, static_cast<int>(v.size()) - 1}(seed)]);
    }

    cout << "the result is ";
    for (int i = 0; i < k; ++i)
        cout << v[i] << " ";

    cout << endl;
}
    
void test_non_unform_random_numbers()
{
    int n;

    vector<int> v;
    cin >> n;
    
    for(int i = 0; i < n; ++i)
    {
        int t;
        cin >> t;
        v.push_back(t);
    }

    vector<double> p;
    for(int i = 0; i < n; ++i)
    {
        double t;
        cin >> t;
        p.push_back(t);
    }    

    vector<double> prefix_p;
    prefix_p.emplace_back(0.0);
    
    // prefix sum or cumulative sum
    partial_sum(p.cbegin(), p.cend(), back_inserter(prefix_p));

    default_random_engine seed((random_device())()); // random num generator

    double uniform_0_1 =
        generate_canonical<double, numeric_limits<double>::digits>(seed);

    int interval_idx =
        distance(prefix_p.cbegin(),
                 upper_bound(prefix_p.cbegin(),
                             prefix_p.cend(),
                             uniform_0_1)) - 1;

    cout << " the result is " <<  v[interval_idx] << endl;
}


// how to make searching substring more efficient?
// you can use many string algorithms (MK, etc)

// or you can optimize it like this:
// return index in string t if s is a substring of t, -1 otherwise
int search_substr(const string& s, const string& t)
{
    if (s.size() > t.size())
        return -1;

    vector<int> v;

    int sum = accumulate(s.begin(), s.end(), 0);
    v.push_back(0);
    partial_sum(t.begin(), t.end(), back_inserter(v));

    for (int i = 0; i < t.size() - s.size() + 1; ++i)
    {
        // filter so that only if sum is same.
        // this filter is linear.
        // we can use hash of each character and use it instead of just ascii
        // value of it.
        int tt = v[i + s.size()] - v[i];

        if ((sum == tt) &&
            (s == t.substr(i, s.size())))
            {
                return i;
            }
    }

    return -1;
}

void test_search_substring()
{
    string a, b;

    cin >> a >> b;

    cout << search_substr(a, b) << endl;

}

// reference
// https://github.com/andreis/interview 
//

int main()
{
    test_search_substring();
}


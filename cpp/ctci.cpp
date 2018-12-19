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
#include <unordered_set>
#include <queue>
#include <iterator> //
#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional> // function  object
#include <math.h>
#include <map>
#include <unordered_map>
#include <stack>
#include <memory> // auto_ptr
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <typeinfo>
#include <random>
#include <sstream>

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

void rotate(string &s, int middle)//jj
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

// using find method in the same place
void remove_dup2(string &s)//jj
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


void remove_dup4(string& s)//jj
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

// this version does not need copying element after replacing.
void replace2(string &s, string r)//jj
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
            // same as the following code
            // copy(r.cbegin(), r.cend(), s.rbegin() + new_size - j - 1);
            // j -= r.size();
        }
        else {

            s[j--] = s[i];
        }
    }
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

void col_row(vector<vector<int>>& m)//jj
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

struct node {
    node(int d) : data(d), next(nullptr) {};
    int data;
    node* next;
};

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
node* reverse_list_every_other(node* a)//jj
{
    if (!a)
        return a;

    node r(0);

    node* prev = &r;
    prev->next = a;

    while (a && a->next)
    {
        prev->next = a->next;
        prev = a;
        a = a->next;
        node* next = a->next;

        a->next = prev;
        prev->next = next;
        a = next;
    }

    return r.next;
}

pair<node*, node*> swap_two(node* a)//jj
{
    node* first = a->next;
    node* next = first->next;
    a->next = next;
    first->next = a;
    return pair<node*, node*>(first, a);
}

node* reverse_list_every_other2(node* a)
{
    node rtn(0);
    node* prev = &rtn;
    prev->next = a;

    while (a && a->next)
    {
        auto n = swap_two(a);

        prev->next = n.first;

        prev = n.second;

        a = prev->next;
    }

    return rtn.next;
}

// or, you can just swap the value of first and second node.


node* merge_list(node*a, node*b)//jj
{
// merge two list into one

    node ret(0);
    node* prev = &ret;

    while (true)
    {
        if (!a)
        {
            prev->next = b;
            break;
        }
        else if (!b)
        {
            prev->next = a;
            break;
        }
        else
        {
            if (a->data < b->data)
            {
                prev->next = a;
                prev = a;
                a = a->next;
            }
            else
            {
                prev->next = b;
                prev = b;
                b = b->next;
            }
        }
    }

    return ret.next;
}


pair<node*, node*> skip_zero(node* n)
{
    node* prev = nullptr;

    while (n && n->data == 0)
    {
        prev = n;
        n = n->next;
    }

    return pair<node*, node*>(prev, n);
}

pair<node*, node*> reverse_one_word(node* a)//jj
{
    if (!a)
        return pair<node*, node*>(a, a);

    node* prev = a;
    node* head = a;
    a = a->next;

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
    node head(0);
    head.next = n;

    n = &head;
    while (n)
    {
        pair<node*, node*> a = skip_zero(n);
        pair<node*, node*> b = reverse_one_word(a.second);

        a.first->next = b.first;
        n = b.second;
    }

    return head.next;
}


void merge_k_sorted_list()//jj
{

    // merge k list of length n
    // with nklogk

    // 1) using heap of length k
    // 2) logk means tree, so merge two list of size n, then 2n,..., and at the logk step
    //    merge all
}

class myq2 { //jj
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
class minstack //jj
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

stack<int>
sort_stack(stack<int> a) //jj
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

void path_normalization() //jj
{
    string s;
    cin >> s;

    stringstream ss(s);
    stack<string> stk;


    if (s[0] == '/')
        stk.emplace("/");

    string str;
    while (getline(ss, str, '/'))
    {
        if (str == "." || str == "")
        {
            continue;
        }
        else if (str == "..")
        {
            if (stk.top() == "/")
            {
                cout << "error" << endl;
                return;
            }
            else if (stk.top() == ".." || stk.empty())
            {
                stk.emplace(str);
            }
            else
            {
                stk.pop();
            }
        }
        else
        {
            stk.emplace(str);
        }
    }

    string r;
    while (!stk.empty())
    {
        r = stk.top() + r;
        stk.pop();
        if (!stk.empty() && stk.top() != "/")
            r = "/" + r;
    }

    cout << " the result is " << r << endl;
}

void sunset_view() //jj
{
    // input: list of house with hight, east to west
    // out : list of house with sunset view
    // constraints: if there is higher building in the west,
    // view is blocked and not sunset view.
}


class myqueue {

public:
    myqueue() { }
    bool empty()
    {
        return l.empty();
    }

    int front()
    {
        return l.front();
    }

    void deque()
    {
        l.pop_front();
        l2.pop_front();
    }

    void enque(int x)
    {
        l.emplace_back(x);
        for (auto iter = l2.rbegin(); iter != l2.rend(); ++iter)
        {
            if (*iter < x)
                *iter = x;
            else
                break;
        }
        l2.emplace_back(x);
    }

    int max()
    {
        return l2.front();
    }

private:
    list<int> l;
    list<int> l2;
};


void swap_even_odd_bits()//jj
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
void swap_in_place()
{
    int a, b;

    a = 5;
    b = 4;

    cout << "swap in place with " << a << " + " << b << endl; //jj
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


// find int sumed up to a X: with map //jj
void find_sum_up_to_x()
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


// if the data is sorted, then we can do it in place with less then O-square. This is another application of partition //jj
void find_sum_up_to_x_1()
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

// how to partition if the size of data is too big?
// hash(str) mod r. Get hash value, mod r where r is the number of partitions

bool comp_pair(pair<int, int> s1,
        pair<int, int> s2)
{
    return s1.first < s2.first;
}


void merge_pair(vector<int> a)
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

template <typename T>
struct nodeParent {
    nodeParent(T v) : val(v), left(nullptr), right(nullptr) {}
    nodeParent* left;
    nodeParent* right;
    nodeParent* parent;
    T val;
};

// find next node in binary search tree (in order successor) where each node has pointer to its parent //jj
nodeParent<int>* search_min(nodeParent<int>* n)
{
    if (n->left)
        return search_min(n->left);

    return n;
}

nodeParent<int>* search_next(nodeParent<int>* n)
{
    if (n->right)
        return search_min(n->right);

    nodeParent<int>* p = n->parent;

    while ((p != nullptr) && (p->right == n))
    {
        n = p;
        p = p->parent;
    }

    return p;
}


// check whether a binary tree is balanced or not.
// what is balanced? distance from the root to all the leaf, min and
// max should be less than 1? or all the internal nodes (including)
// root, its left and right tree should be less than 1? proably
// the second is more difficult.

template <typename T>
struct bt_node {
    bt_node(T v) : val(v), left(nullptr), right(nullptr) {}
    bt_node* left;
    bt_node* right;
    T val;
};

pair<bool, int> check_balanced(const bt_node<int>* node)//jj
{
    if (!node)
        return pair<bool, int>(true, 0);

    auto left = check_balanced(node->left);
    auto right = check_balanced(node->right);

    int depth = max(left.second, right.second) + 1;
    bool balanced = (left.first == true &&
                     right.first == true &&
                     abs(left.second - right.second) <= 1);

    return pair<bool, int>(balanced, depth);
}

void t45()
{
    bt_node<int> a(6);
    bt_node<int> b(3);
    a.left = &b;

    bt_node<int> d(1);
    bt_node<int> e(4);
    b.left = &d;
    b.right = &e;

    auto r = check_balanced(&a);
    cout << " the result is " << r.first << " : " << r.second << endl;

    bt_node<int> c(8);
    a.right = &c;
    r = check_balanced(&a);
    cout << " the result is " << r.first << " : " << r.second << endl;
}


bool check_symmetric(bt_node<int>* left, bt_node<int>* right)//jj
{
    // or, traverse tree in order and store it in a list, and
    // store pair pair<list<bool>, int> where list shows path (i.e.,
    // false means left and true means right) and int is val,
    // perform partition-like comparison  one from left-to-right and
    // the other from right-to-left
    if (left == nullptr && right == nullptr)
        return true;
    if (left != nullptr && right != nullptr)
    {
        if ((left->val == right->val) &&
            check_symmetric(left->left, right->right) &&
            check_symmetric(left->right, right->left))
            return true;
    }

    return false;
}

bool is_symmetric(bt_node<int> * n)
{
    return (n == nullptr || check_symmetric(n->left, n->right));
}

void test_check_binary_tree_symmetric()
{
    bt_node<int> a(6);
    bt_node<int> b(3);
    a.left = &b;
    bt_node<int> c(3);
    a.right = &c;

    bt_node<int> d(1);
    bt_node<int> e(1);
    b.left = &d;
    c.left = &e;
    cout << is_symmetric(&a) << endl;
}


// Design an algorithm and write code to find the first common
// ancestor of two nodes in a binary tree Avoid storing
// additional nodes in a data structure NOTE: This is not
// necessarily a binary search tree

using elem1 = pair<int, bt_node<int>*>;
elem1 find_fca1(bt_node<int>*n, bt_node<int>* a, bt_node<int>* b)//jj
{

    if (n == nullptr)
        return elem1(0, nullptr);

    elem1 r1 = find_fca1(n->left, a, b);
    if (r1.first == 2)
        return r1;

    elem1 r2 = find_fca1(n->right, a, b);
    if (r2.first == 2)
        return r2;

    int r3 = r1.first + r2.first + (n == a) + (n == b);

    return elem1(r3, (r3 == 2) ? n : nullptr);
}

// jj: todo: firs common ancestor in DAG
// first common ancestor in DAG, by the way, can be done by first finding parent of each node, and search (bfs) and store parents of
// a and b so that each parents can be mapped depth from a or b to the parent. And use ist intersection. This was done in
// find common ancestor in Java.

/*
foo (n, a, b)
{
    vector v;
    // if (m.find(n) != m.end()) return m[n];
    for (e : n.adj)
    {
        auto x = foo(e, a, b);
        if (x.first == 2)
        {
            return x;
        }

        if (x.first == 1)
        {
            if (v.empty())
                v.push_back(x);
            else
            {
                if (x != v[0])
                {
                    // m[n] =  {2, n};
                    return {2, n};
                }
            }
        }

    }

    r = 0;
    ptr = nullptr;
    if (n == a || n == b)
    {
        if (v.size() == 1)
            return {2, n};
        else
        {
            r = 1;
            ptr = n;
        }
    }

    return {r, prt};
}
*/


void t46()
{
}

// You have two very large binary trees: T1, with millions of nodes, and T2,
// with hundreds of nodes Create an algorithm to decide if T2 is a subtree of T1//jj

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


void faps(int k, int t, vector<int> vt, vector<vector<int>>& rt, bt_node<int>* n)
{
  if (n == nullptr) {
      return;
  }

  if (t == k) {
      rt.emplace_back(vt);
  }

  vector<int> vtt;
  vtt.emplace_back(n->val);
  faps(k, n->val, vtt, rt, n->left);
  faps(k, n->val, vtt, rt, n->right);


  t += n->val;
  vt.emplace_back(n->val);
  faps(k, t, vt, rt, n->left);
  faps(k, t, vt, rt, n->right);
}

vector<vector<int>> find_all_paths_sum_up(int k, bt_node<int>* n)
{
  vector<vector<int>> rt;
  vector<int> vt;

  // assume that n is not nullprt
  vt.emplace_back(n->val);
  faps(k, n->val, vt, rt, n->left);
  faps(k, n->val, vt, rt, n->right);

  return rt;
}

// given a binary tree in which each node contains a value Design an
// algorithm to print all paths which sum up to that value Note that //jj: todo test this code
// it can be any path in the tree - it does not have to start at the root
void t48()
{

}

// circular buffer//jj

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

    // what should we do if we want to increase/resize buffer
    // when the buffer is full? then rotate and set head/tail
    // and resize the buffer!
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

// find the last N lines in a file (use array in a circular way)//jj
void t132()
{
    // use array in a circular way
}


// merge to arrays into one, one with N + M size (N filled) and the other is M.//jj
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

    // this can be done with two separate while loop (section 14.2 of element of coding interview)

    for (auto e : a)
        cout << e << " ";

    cout << endl;
}

// given a sorted array and a character, print the number of characters

// this method returns the begining index of the character.
// if there is no such character then it returns the position which it should be exist
// lower bound
int find_beg(vector<char>& vc, int i, int j, char t)//jj
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
int find_end(vector<char>& vc, int i, int j, char t)//jj
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

void test_count_char_in_sorted_array() //jj
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
void test_find_interval()//jj
{
    // sol1: a point can be represented by pair<int, bool> where int is location
    // and bool means begin or end. All points (including target) are stored in an
    // array(sorted by beg position), keep searching array from left to right. While
    // searching, if a point is begining of range that range is added, if the point
    // is end of range that the ranage is removed, if target is found then return
    // the ranges we keep so far. You can preprocess so that for each in the array,
    // corresponding range set can precomputed, and then perform binary search for the
    // target number in the array (find_beg would be enough?)
    // If we want to count the number of range then it
    // would be easier.
    //
    // sol2:
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
}

// [-2, 0, 2, 3, 6, 7, 9] -> [2, 3]
void find_same_index_and_val_in_sorted_array(vector<int>& va, int i, int j, vector<int>& vr)//jj
{
    if (i > j)
        return;

    int mid = i + (j - i) / 2;

    // we are happy just one of the indexes
    #if 1
    // if there is a duplicate in the array
    if (mid == va[mid])
    {
        vr.emplace_back(mid);
        return;
    }
    if (va[i] <= (mid - 1) && i <= va[mid - 1])
    {
        find_same_index_and_val_in_sorted_array(va, i, mid - 1, vr);
        if (vr.size() > 0)
            return;
    }
    if ((mid + 1) <= va[j] && va[mid + 1] <= j)
    {
        find_same_index_and_val_in_sorted_array(va, mid + 1, j, vr);
        if (vr.size() > 0)
            return;
    }
    #else
    // if there is no duplicate in the array
    if (mid == va[mid])
    {
        vr.emplace_back(mid);
    }
    else if (mid < va[mid])
    {
        find_same_index_and_val_in_sorted_array(va, i, mid - 1, vr);
    }
    else
    {
        find_same_index_and_val_in_sorted_array(va, mid + 1, j, vr);
    }
    #endif
}


void test_find_same_index_and_val_in_sorted_array()
{
    vector<int> va;
    int t;

    cin >> t;

    for (int i = 0; i < t; ++i)
    {
        int k;
        cin >> k;
        va.emplace_back(k);
    }

    vector<int> vr;

    find_same_index_and_val_in_sorted_array(va, 0, va.size() - 1, vr);

    cout << "the result is" << endl;

    for (auto e : vr)
    {
        cout << " " << e;
    }

    cout << endl;
}


// find a number x in a sorted (left to right, top to down) 2D array//jj
bool matrix_search(const vector<vector<int>>& va, int x)
{
    int row = 0;
    int col = va[0].size() - 1;

    while (row < va.size() && col >= 0)
    {
        if (va[row][col] == x)
        {
            return true;
        }
        else if (va[row][col] > x)
        {
            --col;
        }
        else
        {
            ++row;
        }
    }

    // this implementation is O(n + m), but I think we can improve this by using
    // lower bound to find the next array element if the array size is too big.
    // for example, instead of --col, col = get_lower_bound_col(row, col1, col2)
    return false;
}

// implement how to find lru map element if the number of element in the map
// hits to the max. We only have 1000 element in the map, and later should
// replace old one with new one.

class lrumap {//jj
private:

    class node {
    public:
      node(string s, int x) : str(s), data(x), prev(NULL), next(NULL) {}
        int data;
        string str;
        shared_ptr<node> prev;
        shared_ptr<node> next;
    };
    shared_ptr<node> head;
    shared_ptr<node> tail;
    map<string, shared_ptr<node>> mm;
    int size;

public:
    lrumap(int sz) : size(sz) {}

    shared_ptr<node> get(string& s)
    {
        if (mm.find(s) != mm.end()) // if (mm.count(s)) // can be used as well
        {
            shared_ptr<node> n = mm[s];

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

            return n;
        }
        else
        {
            return nullptr;
        }
    }

    void put(string& s, int i)
    {
        shared_ptr<node> n = get(s);

        if (n)
        {
            n->data = i;
            return;
        }

        if (mm.size() == size)
        {
            shared_ptr<node> prev = tail->prev;
            tail->prev = nullptr;
            mm.erase(mm.find(tail->str));
            tail = prev;
            tail->next = nullptr;
        }

        n = shared_ptr<node>(new node(s, i));
        n->next = head;
        head = n;
        mm[s] = n;
    }
};


class lrumap2 {
private:

  list<int> l; // if we want to limit the number of cache element, then we need to access map element.
    // so list need to have either <key, value> pair (in this example, it is <string, int>) or <iterator_to_map_elem, value)
  map<string, list<int>::iterator> mm;
  int size;

public:
  lrumap2(int sz) : size(sz) {}

  bool get(string& s, int* x)
    {
        if (mm.find(s) != mm.end())
        {
          auto t = mm[s];
          int i = *x = *t;
          l.erase(t);
          l.push_front(i);
          mm[s] = l.begin();
          return true;
        }
        else
        {
          return false;
        }
    }

    void put(string& s, int i)
    {
      int t;
      auto n = get(s, &t);

      if (!n) {
        l.push_front(i);
        mm[s] = l.begin();
      }
      else {
        auto a = l.begin();
        *a = i;
      }
    }
};


void test_lru()
{
}


// partition int array with k, so that k puts together, smaller than k goes left,//jj
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
void test_find_best_investment_period_once() //jj
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


// stock share
// find the best investment period of buying and selling twice //jj
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

void test_paint_house_with_3_colors() //jj
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


// with two rectangle, if they are intersect then return the intersection area //jj
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

// this implementation assume that we just copy as small as possible do not copy overlapping area
void acopy(vector<int>* v, int s, int l, int t) //jj
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


void test_apply_perm() //jj
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

void next_perm(vector<int>* pv) //jj
{
    vector<int>& v = *pv;

    // caution: time complexity is O(n) not O(n^2). This code can be doen with
    // two separate for loop instead of nested for loops.
    for (int i = v.size() - 2; i >= 0; --i)
    {
        if (v[i] < v[i + 1])
        {
            // need to go back->front or front->back?
#if 1
            // if we search back->front, then we can just break if (v[i] < v[j])
            for (int j = v.size() -1; j > i; --j)
            {
                if (v[j] > v[i])
                {
                    swap(v[j], v[i]);
                    break;
                }
            }
#else
            int min_j = i + 1;
            for (int j = i + 2; j < v.size(); ++j)
            {
                if ((v[j] > v[i]) && (v[j] < v[min_j]))
                    min_j = j;
            }
            swap(v[i], v[min_j]);
#endif
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

    next_perm(&v);
    for (int e: v)
        cout << e << " ";
    cout << endl;
}


int find_min_from_sorted_rotated(const vector<int>& v, int a, int e) //jj
{
    if (v[a] <= v[e])
        return v[a];

    int mid = a + (e - a) / 2;

    if (v[mid] > v[e])
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

void test_find_rand_comb() //jj
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

void test_find_uniformly_randimised_image_with_exactly_p_percent_of_black_pixel() //jj
{
// given width and height and percentage, generates an image of pixel (black
// and white) that has exactly p percent of black pixel, with uniformly
// randomised.


// it is just the same problem of selecting a uniformly randomised subset

    int n, m;
    double p;

    cin >> n >> m >> p;


    vector<int> v(n * m);
    for (int i = 0; i < n * m; ++i)
        v[i] = i;

    int cnt = (n * m * p) / 100;

    default_random_engine seed((random_device())()); // random num generator

    for (int i = 0; i < cnt; ++i)
    {
        int j = uniform_int_distribution<int>{
            i, n * m - 1}(seed);
        swap(v[i], v[j]);
    }

    cout << " the result is" << endl;

    for (int i = 0; i < cnt; ++i)
    {
        int x = v[i] / m;
        int y = v[i] % m;
        cout << x << ":" <<y << endl;
    }

}


void test_sample_online_data()//jj
{
// design an algorithm that takes as input a size k, and read packets,
// continuously maintinging a uniform random subset of size k of the read
// packets

    int t;
    int k;
    cin >> k;

    cout << " now enter numbers " << endl;

    vector<int> v(k);
    int cnt = 0;
    default_random_engine seed((random_device())()); // random num generator

    while (cin >> t)
    {
        if (cnt < k)
        {
            v[cnt] = t;
        }
        else
        {
            int j = uniform_int_distribution<int>{0, cnt - 1}(seed);
            if (j < k)
            {
                v[j] = t;
            }
        }
        ++cnt;


        cout << endl << " the result is : " << endl;
        for (int i = 0; i < k; ++i)
        {
            cout << " " << v[i];
        }
        cout << endl;
    }
}


void test_find_rand_subset_of_k_from_n() //jj
{

    int n, k;
    cin >> n >> k;

    map<int, int> mi;
    default_random_engine seed((random_device())()); // random num generator

    for (int i = 0; i < k; ++i)
    {
        int ri = uniform_int_distribution<int>{i, n - 1}(seed);
        auto p1 = mi.find(i);
        auto p2 = mi.find(ri);

        if (p1 == mi.end() && p2 == mi.end())
        {
            mi[i] = ri;
            mi[ri] = i;
        }
        else if (p1 == mi.end())
        {
            mi[i] = p2->second;
            p2->second = i;
        }
        else if (p2 == mi.end())
        {
            mi[ri] = p1->second;
            p1->second = ri;
        }
        else
        {
            swap(p1->second, p2->second);
        }
    }

    for (int i = 0; i < k; ++i)
    {
        cout << mi[i] << " ";
    }

    cout << endl;

}

void test_non_unform_random_numbers() //jj
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
int search_substr(const string& s, const string& t) //jj
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


string ConstructString(int r, int b)
{
    if (r == 0)
        return "";

    int t = r % b;

    if (t >= 10)
        return ConstructString(r/b, b) + char('A' + t - 10 );

    else
        return ConstructString(r/b, b) + char('0' + t);
}


string ConvertBase(const string& s, int a, int b) //jj
{

    if (s.empty())
        return s;

    bool is_negative = s[0] == '-';

    int r = 0;
    for (int i = is_negative? 1:0; i < s.size(); ++i)
    {
        int t = isdigit(s[i])? s[i] - '0' : s[i] - 'A' + 10;
        r = r * a + t;
    }

    if (r == 0)
        return "0";

    string rs = ConstructString(r, b);

    if (is_negative)
        return "-" + rs;
    else
        return rs;
}

void test_convert_base()
{
    int a, b;
    string n;
    cin >> n >> a >> b;

    cout << "the result is " << ConvertBase(n, a, b) << endl;

}

void test_swap_bit() //jj
{
    int i, j;
    long n;

    cin >> n >> i >> j;

    int x = (n >> i) & 1;
    int y = (n >> j) & 1;

    if (x != y)
    {
        n ^= (1L << i | 1L << j);
    }

    cout << "the result is " << n;
}


// sum to
// in an array of integer (+, -, 0), find 3 numbers that sums up 0, and
// return index of them.
// [0, 2, -2, -2] -> [(0, 1, 2), (0, 1, 3)]
// can we find in less then n^2?
// [-8, -4, -3, 2, 6, 7]
// at the moment, assume that all numbers are distinct.
bool hastwosum(vector<int>& v, int i)
{
    int beg = 0, end = v.size() - 1;

    int t = -v[i];

    while (beg < end)
    {
        if (beg == i)
        {
            ++beg;
            continue;
        }
        else if (end == i)
        {
            --end;
            continue;
        }

        int tmp = v[beg] + v[end];
        if (tmp == t)
        {
            return true;
        }
        else if (tmp < t)
        {
            ++beg;
        }
        else
        {
            --end;
        }
    }

    return false;
}

void test_find_3_num_sum_to_zero() //jj
{
    // sol1: sort the array, for each e in array find wheter there is a pair (x, y) which
    // sum up to -a. O(nlogn) Time, O(1) space.

    int n;
    cin >> n;
    vector<int> v;

    for (int i = 0; i < n; ++i)
    {
        int t;
        cin >> t;
        v.emplace_back(t);
    }

    sort(v.begin(), v.end());

    for (int i = 0; i < v.size(); ++i)
    {
        if (hastwosum(v, i))
        {
            cout << "found" << endl;
            return;
        }
    }

    cout << "not found" << endl;
}

/*
there is a bunch of tasks, each have different time to complete, task is independent, and then there are some workers,
      How to allocate tasks to these workers to minimize the total time to complete all the task. The tasks can be randomly picked from the task list.
      Example
      Task: 2,2,3,7, 1
      Worker: 2.
      Return 8, because the first worker can work on the first three tasks : 2 + 2 + 3 = 7, and the second worker can work on the last two tasks : 7 + 1 = 8, so the total time to finish all the task is 8.
      public int getMini(int[] tasks, int k)


sol 1: using recursive method.

 int foo(x, y, a, i):
     if (i == a.size())
        return max(x, y)
     return min(foo(x + a[i], y, a, i + 1),
                foo(x, y + a[i], a, i + 1))

     for performance, we can cache using two parameter [x, i]. for each i, the sum
     so far is same for the same i, and sum[0, i - 1] == x + y, so we do not need to
     take y as a third argument (x and i is enough.)

sol 2: this is not precise, but approximate.
       sort array, and then from max number to min number, distribute to
       one of the worker. If the distribution did not make status change
       then keep adding the next big task to the same worker. Otherwise
       change the worker and send the new task to the worker. so,
       first send 7 to worker1, then send 3, 2, 2 to worker2, then send 1 to
       worker 1. however, consider [7, 3, 2, 2, 2, 2, 2]. Optimal is (10, 10)
       but it ends with (11, 9). We can enhance this algorithm by scaning the
       resulting list, swap items to decrease the difference.

sol 3: sort it, sum it, target = sum / 2, then find sequence of numbers
       (from the first one, which is biggest) that sums closest to the target.
       Maintain min sum, and if the current sum is bigger than min then go to
       the next candidate.
todo: can it be done in O(n)? Is it 2^n?
*/

int two_workers_n_job(int x, int y, vector<int>& a, int i)
{
    if (i == a.size())
    {
        return max(x, y);
    }

    // use cache for performance
    return min (two_workers_n_job(x + a[i], y, a, i + 1),
                two_workers_n_job(x, y + a[i], a, i + 1));

}

// find max number which is smaller than the half of the sum of all numbers;
int two_workers_n_job_2(vector<int>& a, int k, int i)
{
    if (i == a.size())
    {
        return 0;
    }

    // use cache for performance
    int x = two_workers_n_job_2(a, k, i + 1);
    int y = (k < a[i])? 0 : a[i] + two_workers_n_job_2(a, k - a[i], i + 1);

    return max(x, y);
}


int two_workers_n_job_dp(vector<int>& a, int k)
{
    vector<vector<int>> v(a.size() + 1, vector<int>(k + 1, 0));

    for (int i = 1; i <= a.size(); ++i)
    {
        for (int j = 1; j <= k; ++j)
        {
            int x = v[i - 1][j];
            int y = (j < a[i - 1])? 0 : a[i - 1] + v[i - 1][j - a[i - 1]];

            v[i][j] = max(x, y);
        }
    }
    return v[a.size()][k];
}

void test_2_workers_n_jobs() //jj todo: DP? using table? 2 machine n job
{
    int n;
    vector<int> a;

    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        int t;
        cin >> t;
        a.emplace_back(t);
    }

    int result = two_workers_n_job(0, 0, a, 0);

    cout << "the result is " << result << endl;

    int ac = accumulate(a.begin(), a.end(), 0);
    result = two_workers_n_job_2(a, ac / 2, 0);
    cout << "the result is " << (ac - result) << endl;

    result = two_workers_n_job_dp(a, ac / 2);
    cout << "the result is " << (ac - result) << endl;
}


// implement a method to return an index of one of max numbers in an array
// with the possibility of 1 / num_max_number. [3 0 2 1 3] -> [0, 4] with 1/2
// possibility. do it with O(n) time and O(1) space

void test_return_index_to_max_num() //jj
{
    // sol: first pass find max number and number of it
    //      second pass, get the random number r in range [0, num_max -1],
    //        go throuth the numbers and return the index of rth max number.


}


/*
Given an unsorted array, sort it in such a way that the first
element is the largest value, the second element is the smallest,
the third element is the second largest element and so on.
[2, 4, 3, 5, 1] -> [5, 1, 4, 2, 3]

sol 2: can you do it without using extra space? yes.
       sort the array from big number to small number.
       [5, 4, 3, 2, 1]. From the position of the first small number, rotate right.
       [5, 1, 4, 3, 2]. Then from the position of the next small number, rotate right.
       [5, 1, 4, 2, 3].
*/

void test_sort_big_small_number() //jj //without extra space? can we do it? find max then swap, find min then swap, ...
{
  int n;
  cin >> n;

  vector<int> v;
  for (int i = 0; i < n; ++i) {
    int t;
    cin >> t;
    v.emplace_back(t);
  }

  sort(v.begin(), v.end(), [](int a, int b){ return a > b;});

  vector<int> v2(v.size(), 0);
  int j = 0;
  for (int i = 0; i < v.size(); i += 2) {
    v2[j++] = i;
  }

  j = v.size() - 1;
  for (int i = 1; i < v.size(); i += 2) {
    v2[j--] = i;
  }

  for (int i = 0; i < v2.size(); ++i) {
    int idx = i;
    while (v2[idx] >= 0) {
      int next = v2[idx];
      swap(v[i], v[next]);
      v2[idx] -= v.size(); // just in case we need to restore v
      idx = next;
    }
  }

  cout << " the result is " << endl;
  for (int i = 0; i < v.size(); ++i)
    cout << v[i] << " ";

  cout << endl;
}


// given a list of range (x1, x2), find the size of entire area covered by all of the
// range. For example, [(1,2), (1, 3)] -> 2, [(2,3), (4, 5)] -> 2
// sol: first, sort the list with the first number in the pair.
//      second, from the first pair, if it is intersecting with the next pair then merge
//              it. otherwise skip to the next pair.
//      third, calculate the range.
// sol2: same with intersect problem before.
//       struct point {int loc; bool begin;}, sort all the points left to right. Visit them from left to right,
//       starts a region if the point is begin and this is the only point, ends the region when end point encountered
//       no other points remained in the region.
bool is_intersect(pair<int, int> a, pair<int, int> b)
{
    return !(a.second < b.first || b.second < a.first);
}

void test_get_all_covered_range() //jj
{
    int n;
    cin >> n;

    using elem = pair<int, int>;

    vector<elem> vp;
    for (int i = 0; i < n; ++i)
    {
        int a, b;
        cin >> a >> b;

        vp.emplace_back(elem(a, b));
    }

    sort(vp.begin(), vp.end(), [](elem x, elem y) { return x.first < y.first; });

    int ret = 0;
    vector<int> vr;
    vr.emplace_back(0);

    for (int i = 1; i < vp.size(); ++i)
    {
        if (is_intersect(vp[ret], vp[i]))
        {
            vp[ret].second = max(vp[ret].second, vp[i].second);
        }
        else
        {
            vr.emplace_back(i);
            ret = i;
        }
    }

    int rsize = 0;
    for (int i = 0; i < vr.size(); ++i)
        rsize += vp[vr[i]].second - vp[vr[i]].first;

    cout << "the result is " << rsize << endl;
}

void test_find_maximum_intersected_events_in_a_calendar()
{
// sol: each end point of a calendar are added in a vector, sort the vector,
//      process each one by one. If a start of event then increase num_intersect,
//      if an end of event then decrease it. If num_intersect is bigger than max_intersect
//      then set new max_intersect. After processing all the event, return max_intersect.
}


int my_part(int i, int j, int k, vector<int>& v)
{
    while (i != j)
    {
        while (v[i] <= k)
        {
            ++i;
            if (i == j)
                return i;
        }

        do
        {
            --j;
            if (i == j)
                return i;
        } while (v[j] > k);

        swap(v[i], v[j]);
        ++i;
    }

    return i;
}

void test_find_kth_biggest_element_from_unsorted_array() //jj
{
// sol1: use min heap with size of k (or max heap of n - k if k is too big)
// sol2: use partition // this is O(n)

    int n;
    int k;
    cin >> k >> n;

    vector<int> v;
    for (int i = 0; i < n; ++i)
    {
        int t;
        cin >> t;
        v.emplace_back(t);
    }
    int left = 0;
    int right = v.size();

    int r = -100;
    while (left != right)
    {
        int lval = v[left];
        int d = my_part(left, right, lval, v);
        swap(v[left], v[d - 1]);
        if (d == k)
        {
            r = v[d - 1];
            break;
        }
        else if (d < k)
        {
            left = d;
        }
        else
        {
            right = d - 1;
        }
    }

    cout << "the result is " << r << endl;
}

/* 100 -> "One Hundred" */

string n2e(int d)
{
    string s;
    if (d >= 1000)
    {
        s = n2e(d / 1000) + " Thousand" + n2e(d % 1000);
    }
    else if (d >= 100)
    {
        s = n2e(d / 100) + " Hundred" + n2e(d % 100);
    }
    else if (d >= 20)
    {
        vector<string> vs = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy",
                             "Eighty", "Ninty"};
        s = vs[d / 10] + n2e(d % 10);
    }
    else
    {
        vector<string> vs = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight",
                             "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Ninteen"};

        s = vs[d];
    }

    return " " + s;
}

string num_to_eng(int d)
{
    if (d == 0)
        return "Zero";

    return n2e(d);
}

void test_number_to_english() //jj
{
    int n;
    cin >> n;

    string s = num_to_eng(n);

    cout<< " the result is " << s << endl;
}


// given a vector of strings, group them with same substrings.
// the substring should be in a given vector as well
void test_group_with_substrings() //jj
{
    // union and find, use string::find method

    int n;
    vector<string> vs;

    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        string t;
        cin >> t;
        vs.emplace_back(t);
    }

    vector<int> vi(vs.size(), 0);
    for (int i = 0; i < vs.size(); ++i)
    {
        vi[i] = i;
    }

    // if we sort string using their size (smallest string first), then the second loop could be
    // j = i + 1 not j = 0;
    for (int i = 0; i < vs.size(); ++i)
    {
        for (int j = 0; j < vs.size(); ++j)
        {
            if (i == j)
            {
                continue;
            }

            if (vi[i] != i)
            {
                continue;
            }

            if (vs[j].find(vs[i]) != std::string::npos)
            {
                vi[j] = i;
                // we need to do union operation here, otherwise we need to do search
                // to find top in the hierarcy. (i.e., bab ab abab)
            }
        }
    }

    // result
    map<string, vector<string>> m;

    for (int i = 0; i < vi.size(); ++i)
    {
        m[vs[vi[i]]].emplace_back(vs[i]);

        cout << vs[i] << " belogns to " << vs[vi[i]] << endl;
    }
}

/*
Given m 0 and n 1, count the total number of permutations where two 1 cannot be adjacent
public int count(int m, int n){
}
*/

// todo: can we do it with DP? using table?

int no_adj_1(int m, int n, bool prevOne)
{
    if (m == 0)
    {
        if (n > 1)
            return 0;
        // if (n == 1 && prevOne)
        //     return 0;
        return 1;
    }
    if (n == 0)
        return 1;

    int r1 = no_adj_1(m - 1, n, false);

    int r2 = 0;
    if (!prevOne)
        r2 = no_adj_1(m, n - 1, true);

    return r1 + r2;
}


void test_perm_1_0_with_no_adjacent_1() //jj
{
    int m, n;

    cin >> m >> n;

    int r = no_adj_1(m, n, false);

    cout << "the result is " << r << endl;
}

/*
Given a positive integer n, find the no of integers less than equal to n, whose binary representation doesn't contain consecutive or
adjacent 1s.
eg:
I/P : 4
O/P: 4 (0,1,2,4 Valid)
 */

// sol 1: from 0 to n, check if it has consecuive n.
// sol 2: use recursive method as following
int no_adj_1(int m, int t, int k)
{
    if (t > k)
        return 0;

    if (m == 0)
        return 1;

    int r1 = no_adj_1(m - 1, t << 1, k);

    int r2 = 0;
    if ((t & 0x1) == 0)
        r2 = no_adj_1(m - 1, (t << 1) + 1, k);

    return r1 + r2;
}

void test_nums_with_no_adjacent_1() //jj
{
    int k;
    cin >> k;

    int t = k;
    int m = 0, n = 0;

    while (t > 0)
    {
        if ((t & 0x1) == 0)
            ++m;
        else
            ++n;
        t = t >> 1;
    }

    int r = no_adj_1(m + n, 0, k);

    cout << "1: the result is " << r << endl;

    // TODO
    // sol3: divide and conquer.
    /*
    t = k;
    int a = 0; b = 0;
    while (t > 0)
    {
        tmp = a;
        a = num % 4 + a + b;// 4 -> 1, 8 -> 3, 16-> 8,
        if ((t & 0x3) == 0x3)
            ++a;
        b = tmp;
    }
    */

}


pair<int, int> find_small_subarray(vector<string>& s, vector<string>& k) //jj
{
  unordered_map<string, int> m;
  unordered_set<string> sk;
  int begin = -1, end = -1;

  for (int i = 0; i < k.size(); ++i) {
    sk.insert(k[i]);
  }

  int size = 0;

  for (int left = 0, right = 0; right < s.size(); ++right) {
    if (sk.count(s[right])) {
      if (m[s[right]] == 0) {
          ++size;
      }
      ++m[s[right]];
    }

    while (size == sk.size()) {
      if ((begin == -1 && end == -1) ||
          right - left < end - begin) {
        begin = left;
        end = right;
      }

      if (sk.count(s[left])) {
        if(m[s[left]] == 1) {
          --size;
        }
        --m[s[left]];
      }

      ++left;
    }
  }

  return pair<int, int>(begin, end);
}

pair<int, int> find_small_subarray(istringstream* sin, vector<string>& k) //jj
{
  list<int> loc;
  unordered_map<string, list<int>::iterator> dict;

  for (string& s : k) {
    dict[s] = loc.end();
  }

  int begin = -1, end = -1;

  int idx = 0;
  string s;
  while(*sin >> s) {
    auto it = dict.find(s);
    if (it != dict.end()) {
      if (it->second != loc.end()) {
        loc.erase(it->second);
      }

      loc.emplace_back(idx);
      it->second = --loc.end();
    }

    if (loc.size() == k.size()) {
      if ((begin == -1 && end == -1) ||
          idx - loc.front() < end - begin) {
        begin = loc.front();
        end = idx;
      }
    }

    ++idx;
  }

  return pair<int, int>(begin, end);
}


void test_find_smallest_subarray_of_string_containing_key_strings()
{
  // sol 1: for each index from 0, find subarray that have all the containing key, find the min of all the finding.
  // sol 2: first pass, for each index from 0 update map<string, int> for word count. also find first index(k) which has all keys
  //        second pass, start with [0, k], increase lower bound, if it causes a key missing then stop increase lower bound. increase upper bound
  //        until the missing key found. Keep update smallest range [a, b] until we run up all the element in the array

  int n, m;
  cin >> n >> m;


  vector<string> vs, vk;
  for (int i = 0; i < n; ++ i)
    {
      string s;
      cin >> s;
      vs.emplace_back(s);
    }

  for (int i = 0; i < m; ++ i)
    {
      string s;
      cin >> s;
      vk.emplace_back(s);
    }

  auto r = find_small_subarray(vs, vk);

  cout << " the result is " << r.first << ", " << r.second << endl;
}

/*
  Given an input string "aabbccba", find the shortest substring from the alphabet "abc".
  In the above example, there are these substrings "aabbc", "aabbcc", "ccba" and "cba". However the shortest substring that contains all the characters in the alphabet is "cba", so "cba" must be the output.
  Output doesnt need to maintain the ordering as in the alphabet.
  Other examples:
  input = "abbcac", alphabet="abc" Output : shortest substring = "bca".
*/

void test_find_shortest_substr_using_alplabet() //jj : same as above
{
}


// the same problem, but subarray should have order
pair<int, int> find_small_subarray_with_order(vector<string>& s, vector<string>& k) //jj
{
  vector<int> vi(k.size(), -1);
  int begin = -1, end = -1;
  map<string, int> m;              // map for string to index into vector vi
  for (int i = 0; i < k.size(); ++i) {
    m[k[i]] = i;
  }

  for (int i = 0; i < s.size(); ++i) {
    if (s[i] == k[0]) {
      vi[0] = i;
      continue;
    }

    auto it = m.find(s[i]);
    if (it != m.end()) {
      int idx = it->second;
      if (vi[idx - 1] != -1) {
        vi[idx] = vi[idx - 1];
        vi[idx - 1] = -1;
        if (idx == k.size() - 1 && ((begin == -1 && end == -1) || (i - vi[idx] < end - begin))) {
          begin = vi[idx];
          end = i;
          vi[idx] = -1;
        }
      }
    }
  }

  return pair<int, int>(begin, end);
}

// [3, -2, 7, 9, 8, 1, 2, 0, -1, 5, 8] -> [-2, -1, 0, 1, 2, 3]
pair<int, int> find_largest_contained_interval(vector<int>& vi) //jj
{
  unordered_map<int, int> m;

  for (auto e : vi) {
    m[e] = e;
  }

  unordered_set<int> s(vi.begin(), vi.end());

  for (auto e :vi) {
    if (m.find(e + 1) != m.end()) {
      m[e] = e + 1;
      s.erase(e + 1);
    }
  }

  // now s should have root nodes
  auto begin = s.begin();
  int next = *begin;
  int a = next;
  int count = 1;
  while (m[next] != next) {
    next = m[next];
    ++count;
  }
  int b = next;

  for (auto beg = ++(s.begin()); beg != s.end(); ++beg) {
    int next = *beg;
    int cnt = 1;
    while (m[next] != next) {
      next = m[next];
      ++cnt;
    }

    if (cnt > count) {
      count = cnt;
      a = *beg;
      b = next;
    }
  }

  return pair<int, int>(a, b);
}


void test_find_largest_contained_intervals()
{
  vector<int> vi = {3, -2, 7, 9, 8, 1, 2, 0, -1, 5, 8};
  pair<int, int> r = find_largest_contained_interval(vi);
  cout << "the result is : " << r.first << " " << r.second << endl;
}


// array monotonic. Space complexity does not count the origial space, just count additional space, so this is
// O(N) time complexity, and O(1) space complexity.
bool check_array_is_keep_increasing_decreasing(vector<int>& a) //jj
{
  int direction = a.back() > a.front() ? 1 : -1;

  for (int i = 0; i < a.size() - 1; ++i) {
    int tempd;

    if (direction == 1) {
      tempd = a[i + 1] >= a[i] ? 1 : -1;
    }
    else {
      tempd = a[i + 1] <= a[i]? -1 : 1;
    }

    if (tempd != direction)
      return false;
  }

  return true;
}

// Usually I can think of using prev variable.
bool array_monotonic_2(vector<int>& a)
{
    if (a.size() < 3)
        return true;

    auto cd = [](int a, int b) {
        if (b > a)
            return 1;
        else if (a > b)
            return -1;
        else return 0;
    };

    int prev = cd(a[1], a[0]);

    for (int i = 2; i < a.size(); ++i)
    {
        int tmp = cd(a[i], a[i - 1]);

        if (tmp == 0)
            continue;

        if (tmp != prev && prev != 0)
            return false;

        prev = tmp;
    }

    return true;
}


//std::sort (numbers, numbers+5, std::less<int>()); -> 10 20 30 40 50
//std::sort (numbers, numbers+5, std::greater<int>()); -> 50 40 30 20 10
int get_top_three_scores_sum(priority_queue<int, vector<int>, greater<int>> scores) //jj
{
  int sum = 0;
  while (!scores.empty()) {
    sum += scores.top();
    scores.pop();
  }

  return sum;
}

string find_student_with_highest_best_of_three_scores(ifstream* ifs)
{
  // multiset
  unordered_map<string, priority_queue<int, vector<int>, greater<int>>> student_scores;

  string name;
  int score;

  while (*ifs >> name >> score) {
    student_scores[name].emplace(score);
    if (student_scores[name].size() > 3) {
      student_scores[name].pop();

    }
  }

  string top_student = "no such student";
  int current_top_sum = 0;
  for (const auto& scores: student_scores) {
    if (scores.second.size() == 3) {
      int current_scores_sum = get_top_three_scores_sum(scores.second);
      if (current_scores_sum > current_top_sum) {
        current_top_sum = current_scores_sum;
        top_student = scores.first;

      }
    }
  }

  return top_student;
}


struct student {
  int age;
  string name;
};

// partition student so that same ages go together.
// try to swap inplace to reduce memory usage.
void partition_student_with_same_age(vector<student>& vs) //jj: todo: can we use apply_perm algorithm?
{
  unordered_map<int, int> age_count;
  unordered_map<int, int> age_offset;

  for (auto& a : vs) {
    age_count[a.age]++;
  }

  int offset = 0;
  for (auto& a : age_count) {
    age_offset[a.first] = offset;
    offset += a.second;
  }

  while (age_offset.size()) {
    auto from = age_offset.begin();
    auto to = age_offset.find(vs[from->second].age);

    swap(vs[from->second], vs[to->second]);

    --age_count[to->first];
    if (age_count[to->first]) {
      --to->second;
    }
    else {
      age_offset.erase(to);
    }
  }
}

/*
  Given an array (may have negative num) and an integer(may be negative),
  find the smallest subarray whose sum is >= the given integer.
  int[] nums2 = {5,4,-10,16};
  int x=10;
  return 1, because 16 >= x
  try to solve it in o(n) time
  public static int miniSubArrayLen(int[] nums, int s) {
 */

void find_min_subarray_bigger_than_x(vector<int>& v, int x)
{
    // consider {5, 4, -15, 11} and x = 10, the answer should be 11
    int begin = -1, end = -1;
    int left = 0, right = 0;
    int sum = 0, min_sum = 0;

    while (right < v.size())
    {
        sum += v[right];
        min_sum = min(sum, min_sum);

        if (sum - min_sum > x)
        {
            int tsum;
            while (left <= right)
            {
                if ((sum >= x) &&
                    ((begin == -1 && end == -1) ||
                     ((right - left) < (end - begin))))
                {
                    begin = left;
                    end = right;
                    tsum = sum;
                }

                sum -= v[left];
                ++left;
            }

            left = begin + 1;
            sum = tsum - v[begin];
        }

        ++right;
    }

    cout << "the result is " << end  << " "  << begin << endl;
}

void test_find_min_subarray_bigger_than_x()
{
    int x, n;
    cin >> x >> n;

    vector<int> v;

    for (int i = 0; i < n; ++i)
    {
        int t;
        cin >> t;
        v.emplace_back(t);
    }

    find_min_subarray_bigger_than_x(v, x);
}

int find_minimum_number_of_chars_to_remove_to_make_palindrome(string s)
{
    if (s.size() <= 1)
    {
        return 0;
    }

    int end = s.size() - 1;

    if (s[0] == s[end])
    {
        return find_minimum_number_of_chars_to_remove_to_make_palindrome(s.substr(1, end - 1));
    }
    else
    {
        return 1 + min(find_minimum_number_of_chars_to_remove_to_make_palindrome(s.substr(1)),
                       find_minimum_number_of_chars_to_remove_to_make_palindrome(s.substr(0, end)));
    }
}


int find_minimum_number_of_chars_to_remove_to_make_palindrome_dp(string s)
{
    vector<vector<int>> v(s.size() + 1, vector<int>(s.size() + 1));
    int n = s.size() + 1;

    for (int i = 0; i < n; ++i)
    {
        v[i][i] = 0;
    }


    for (int t = 2;t < n; ++t)
    {
       for (int i = 1, j = t; j < n; ++i, ++j)
       {
           if (s[i - 1] == s[j - 1])
           {
               v[i][j] = v[i + 1][j -1];
           }
           else
           {
               v[i][j] = 1 + min(v[i][j - 1], v[i + 1][j]);
           }
       }
    }

    return v[1][n - 1];
}

void test_find_min_num_char_to_make_palindrome()
{
    string s;

    cin >> s;

    int r = find_minimum_number_of_chars_to_remove_to_make_palindrome(s);
    int r2 = find_minimum_number_of_chars_to_remove_to_make_palindrome_dp(s);

    cout << "the result is " << r << " and " << r2 << endl;
}

int find_lcs(string s1, string s2)
{
    if (s1.size() == 0)
    {
        return 0;
    }
    else if (s2.size() == 0)
    {
        return 0;
    }
    else
    {
        if (s1[0] == s2[0])
        {
            return 1 + find_lcs(s1.substr(1), s2.substr(1));
        }
        else
        {

            return  max(find_lcs(s1.substr(1), s2),
                        find_lcs(s1, s2.substr(1)));
        }
    }
}

int find_lcs_dp(string s1, string s2)
{
    int n = s1.size() + 1;
    int m = s2.size() + 1;

    vector<vector<int>> v(n, vector<int>(m, 0));

    for (int i = 1; i < n; ++i)
    {
        for (int j = 1; j < m; ++j)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                v[i][j] = v[i - 1][j - 1] + 1;
            }
            else
            {
                v[i][j] = max(v[i - 1][j], v[i][j - 1]);
            }
        }
    }

    return v[n - 1][m - 1];
}


void test_find_lcs()
{
    string s1, s2;

    cin >> s1 >> s2;

    int r = find_lcs(s1, s2);
    int r2 = find_lcs_dp(s1, s2);

    cout << "the result is " << r << " and " << r2 << endl;
}


// DP
// post office is the same problem?
int knapsack(int k, vector<int>& v, vector<int>& w, int i, vector<vector<int>>& vv)
{
    if (i == w.size())
        return 0;

    if (vv[k][i] == -1)
    {
        int a = (k < w[i]) ? 0: v[i] + knapsack(k - w[i], v, w, i + 1, vv);
        int b = knapsack(k, v, w, i + 1, vv);
        vv[k][i] = max(a, b);
    }

    return vv[k][i];
}

int knapsack_dp(int k, vector<int>& v, vector<int>& w)
{
    vector<vector<int>> vv(w.size() + 1, vector<int>(k + 1, 0));

    for (int i = 1; i <= w.size(); ++i)
    {
        for (int j = 1; j <= k; ++j)
        {
            int a = vv[i - 1][j];
            int b = (j < w[i - 1])? 0 : v[i - 1] + vv[i - 1][j - w[i - 1]];
            vv[i][j] = max(a, b);
        }
    }

    return vv[v.size()][k];
}

int knapsack_dp2(int k, vector<int>& v, vector<int>& w)
{
    vector<vector<int>> vv(2, vector<int>(k + 1, 0));

    int prev = 0;
    int  cur = 1;
    for (int i = w[0]; i <= k; ++i)
    {
        vv[prev][i] = v[0];
    }

    for (int i = 2; i <= w.size(); ++i)
    {
        for (int j = 1; j <= k; ++j)
        {
            int a = vv[prev][j];
            int b = (j < w[i - 1])? 0 : v[i - 1] + vv[prev][j - w[i - 1]];
            vv[cur][j] = max(a, b);
        }

        prev = (prev == 0)? 1 : 0;
        cur = (cur == 0)? 1 : 0;
    }

    return vv[prev][k];
}



// test input
// 130 16
// 65 20 35 8 245 60 195 55 65 40 150 70 275 85 155 25 120 30 320 65 75 75 40 10 200 95 100 50 220 40 99 10

void test_knapsack()
{
    int k;
    vector<int> v;
    vector<int> w;

    cin >> k;

    int size;

    cin >> size;
    for (int i = 0; i < size; ++i)
    {
        int a, b;
        cin >> a >> b;

        v.emplace_back(a);
        w.emplace_back(b);
    }

    vector<vector<int>> vv(k + 1, vector<int>(w.size(), -1));
    // todo: for the memory efficiency, we can use a map.
    // map<int, int> ma;
    // inside a knapsack function, check using
    // if (ma.find(k * w.size() + i) == ma.end())
    // { ma[k * w.size() + i] = max(...); }

    int result = knapsack(k, v, w, 0, vv);

    cout << " the result is " << result << endl;

    result = knapsack_dp(k, v, w);
    cout << " the result is " << result << endl;

    result = knapsack_dp2(k, v, w);
    cout << " the result is " << result << endl;
}


// Given a dictionary, design an efficient algorithm that checks whether the name is the concatenation of a sequence of dictionary words. If such a concatenation exists, return it. Consider return any concatenation without using recursive function.
// inout: 'amanaplanacanal', 'a man plan canal'. output: 'a man a plan a canal'
void test_decompose_into_dictionary_words()
{
    // sol1: use DP: time complexity O(W * n^2) where W is longest dictionary word and n is domain string length
    int n;

    cin >> n;

    set<string> sset;
    for (int i = 0; i < n; ++i)
    {
        string s;
        cin >> s;
        sset.insert(s);
    }

    string ss; // source string
    cin >> ss;

    vector<int> v;
    vector<set<string>::iterator> vi(ss.size() + 1, sset.end());


    for (int i = 1; i <= ss.size(); ++i)
    {
        string tmp = ss.substr(0, i);
        if (sset.count(tmp))
        {
            v.emplace_back(i);
            vi[i] = sset.find(tmp);
        }
        else
        {
            for (int j = v.size() - 1; j >= 0; --j)
            {
                string t = ss.substr(v[j], i - v[j]);
                if (sset.count(t))
                {
                    v.emplace_back(i);
                    vi[i] = sset.find(t);
                    break;
                }
            }
        }
    }

    if (v.back() == ss.size())
    {
        cout << "found" << endl;
        int i = ss.size();
        while(i != 0)
        {
            string tmp = *vi[i];
            cout << tmp << " ";
            i -= tmp.size();
        }
    }
}


// There are a row of coins (even number of them).
// Two players pickup a coin from either front or back of coins. Maximum gains win.
// Design an efficient algorithm to get maximum total value for the starting player.
// Assume the second player move to minimize the revinue of the first player.
// 10 25 5 1 10 5
// the result is 31

int get_max_gain(vector<int>& v, int beg, int end)
{
    if (beg > end)
    {
        return 0;
    }

    int a = v[beg] + min(get_max_gain(v, beg + 2, end),
                         get_max_gain(v, beg + 1, end - 1));
    int c = v[end] + min(get_max_gain(v, beg + 1, end - 1),
                         get_max_gain(v, beg, end - 2));

    return max(a, c);
}

int get_max_gain_dp(vector<int>& v)
{
    vector<vector<int>> vv(v.size() + 1, vector<int>(v.size() + 1, 0));

    for (int i = 2; i <= v.size(); i += 2)
    {
        for (int j = 0; j <= v.size() - i; ++j)
        {
            int a = v[j] + min(vv[j + 2][j + i], vv[j + 1][j + i - 1]);
            int c = v[j + i - 1] + min(vv[j + 1][j + i - 1], vv[j][j + i - 2]);
            vv[j][j + i] = max(a, c);
        }
    }

    return vv[0][v.size()];
}

void test_pickup_coins_for_maximum_gain()
{
    int n;
    vector<int> v;

    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        int t;
        cin >> t;
        v.emplace_back(t);
    }

    int r = get_max_gain(v, 0, v.size() - 1);

    cout << "the result is " << r << endl;
    r = get_max_gain_dp(v);
    cout << "the result is " << r << endl;
}

// input: 0 8 4 12 2 10 6 14 1 9
// output: 4 (length of longest non decreasing seqeunce, 0, 4, 10, 14 or 0, 2, 6, 9)
int non_dec_seq(int idx, vector<int>& v)
{
    if (v.size() == idx)
    {
        return 0;
    }
    // use cache using idx
    int r = 0;
    for (int i = idx + 1; i < v.size(); ++i)
    {
        if (v[idx] <= v[i])
        {
            r = max(r, 1 + non_dec_seq(i, v));
        }
    }

    return r;
}

int non_dec_seq2(int idx, vector<int>& v)
{
    if (v.size() == idx)
    {
        return 0;
    }

    int r = 0;
    for (int i = idx + 1; i < v.size(); ++i)
    {
        if (v[idx] <= v[i])
        {
            r = max(r, 1 + non_dec_seq(i, v));
        }
    }

    int b = non_dec_seq2(idx + 1, v);

    return max(r, b);
}
void test_longest_non_decreasing_sequence()
{
    int n;
    vector<int> v;
    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        int t;
        cin >> t;
        v.emplace_back(t);
    }

    int r = 0;

    for (int i = 0; i < n; ++i)
    {
        r = max(r, non_dec_seq(i, v));
    }

    cout << "the result is " << r + 1 << endl;
    cout << "the result is " << non_dec_seq2(0, v) + 1 << endl;

    // DP

    vector<int> vd(n, 1);

    for (int i = 1; i < n; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (v[j] <= v[i])
            {
                vd[i] = max(vd[i], 1 + vd[j]);
            }
        }
    }

    r = *max_element(vd.begin(), vd.end());

    cout << "the result is " << r << endl;
}

// Input:  words[] = {"baa", "abcd", "abca", "cab", "cad"}
// Output: Order of characters is 'b', 'd', 'a', 'c'
//                                      Note that words are sorted and in the given language "baa" 
//                                      comes before "abcd", therefore 'b' is before 'a' in output.
//                                      Similarly we can find other orders.

//                                      Input:  words[] = {"caa", "aaa", "aab"}
// Output: Order of characters is 'c', 'a', 'b'
void test_alien_language()
{
    //sol: find partial order then it ends up wit  a graph, then topological sort using dfs

    int n;
    cin >> n;

    vector<string> vs;

    for (int i = 0; i < n; ++i)
    {
        string s;
        cin >> s;

        vs.emplace_back(s);
    }

}

// Implement a fast sorting algorithm for list. It should be stable sort.
// Merge sort on array is not in-place, but merge sort on array is in-place.
// 14.9 of EPI
// sol: use merge sort. you need to have merge_list which merges two sorted list and return merged sorted list.


// Given a string, find all possible palindromic partitions of given string.
// Example: input -> geeks
//          output -> g e e k s
//                    g ee k s
bool is_palindrom(int i, int j, string&s)
{
    while (i < j)
    {
        if (s[i] != s[j])
        {
            return false;
        }
        ++i;
        --j;
    }

    return true;
}

void find_all_palindrom(int i, string& s, vector<int> t, vector<vector<int>>& r)
{
    if (i == s.size())
    {
        r.emplace_back(t);
    }

    for (int j = i; j < s.size(); ++j)
    {
        if (is_palindrom(i, j, s))
        {
            t.emplace_back(j);
            find_all_palindrom(j + 1, s, t, r);
            t.pop_back();
        }
    }
}

// find if there is a palindromic decomposition, it always return true as each char is a palindromic.
// it does not find all.
bool find_palindrom_dp(string& s)
{
    vector<int> p;

    for (int i = 0; i < s.size(); ++i)
    {
        if (is_palindrom(0, i, s))
        {
            p.emplace_back(i);
        }
        else
        {
            for (int j = p.size() - 1; j >= 0; --j)
            {
                if (is_palindrom(p[j] + 1, i, s))
                {
                    p.emplace_back(i);
                    break;
                }
            }
        }
    }

    if (p.back() == (s.size() - 1))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void test_find_all_possible_palindromic_partitions()
{
    string s;

    cin >> s;

    vector<int> t;
    vector<vector<int>> r;

    if (find_palindrom_dp(s))
    {
        cout << "found at least one" << endl;
    }

    find_all_palindrom(0, s, t, r);

    for (int i = 0; i < r.size(); ++i)
    {
        cout << endl<< "begin : ";
        for (int j = 0; j < r[i].size(); ++j)
        {
            cout << r[i][j] << " ";
        }
        cout << " end" << endl;
    }
}

// moving average of last N numbers in a stream
// For example, if N=3 and the stream S=[2,3,4,1,2,-3,0,…] then moving averages at each each streamed number are = [2.0, 2.5, 3.0, 2.66, 2.33, 0, -0.33,…].
void test_moving_average_of_last_n()
{
    // sol: similar to circular buffer.

    int n;

    cin >> n;
    double sum = 0;
    double avg = 0;
    int size = 0;

    vector<int> v(n, -1);

    int head = 0, tail = 0;

    auto put = [&](int t) {
        v[tail++] = t;
        sum += t;
        if (tail == n)
        {
            tail = 0;
        }
    };


    auto get = [&]() {
        sum -= v[head++];

        if (head == n)
        {
            head = 0;
        }
    };

    auto get_avg = [&]() {
        return sum / min(size, n);
    };

    int t;
    string s;
    while (getline(cin, s, ' '))
    {
        t = stoi(s);
        if (size < n)
        {
            put(t);
            size++;
        }
        else
        {
            get();
            put(t);
        }

        cout << endl << "avg : " << get_avg() << endl;
    }
}


void test_find_number_of_subarrays_sum_to_k()
{
    int n;
    vector<int> v;

    int k;
    cin >> k;

    cin >> n;
    for (int i = 0; i < n; ++i )
    {
        int t;
        cin >> t;
        v.emplace_back(t);
    }

    unordered_map<int, int> m;

    int count = 0;
    int sum = 0;

    m[0] = 1;
    for (int i = 0; i < n; ++i)
    {
        sum += v[i];

        if (m.find(sum - k) != m.end())
        {
            count += m[sum - k];
        }

        m[sum]++;
    }

    cout << "the result is " << count << endl;
}


// find island
// input
// xxx00
// 000xx
// xx00x
// output
// ->3

// x000x
// x000x
// x000x
// xxxxx
// -> 0
// what if the dimension is too big? who can handle this?
void test_find_island_from_2_dimensional_array()
{
    // sol1: dfs or bfs
    // sol2: line by line, for each element look at left and up. If left and up belongs to different area, merge it (union/find?)
    int n;
    cin >> n;
    vector<string> v;

    for (int i = 0; i < n; ++i)
    {
        string s;
        cin >> s;
        v.emplace_back(s);
    }

    int count = 0;
    vector<int> vi;

    vector<vector<int>> vr (2, vector<int>(v[0].size(), -1));
    int cur = 0, prev = -1;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < v[0].size(); ++j)
        {
            if (v[i][j] != 'x')
            {
                continue;
            }

            auto a = (i == 0)? -1 : vr[prev][j];
            auto b = (j == 0)? -1 : vr[cur][j - 1];

            if (a == -1 && b == -1)
            {
                vi.emplace_back(count);
                vr[cur][j] = count;
                ++count;
            }
            else if (a == -1)
            {
                vr[cur][j] = b;
            }
            else if (b == -1)
            {
                vr[cur][j] = a;
            }
            else if (a == b)
            {
                vr[cur][j] = b;
            }
            else
            {
                vr[cur][j] = b;
                // merge or union/find
                vi[a] = vi[b];
            }
        }

        prev = cur;
        cur = (cur + 1) % 2;
    }

    int r = 0;
    for (int i = 0; i < vi.size(); ++i)
    {
        if (vi[i] == i)
        {
            ++r;
        }
    }

    cout << "the result is " << r << endl;
}

//
// test functions
//

void test_mod_fib()
{

    double x = pow(2, 3);
    cout << endl << mod_fib(x) << endl;
    //mod_fib(x);


    x = pow (4, 7);
    cout << endl << x << " "  << mod_fib(x) << endl;
    //mod_fib(x);

}


void test_merge_pair()
{

    int a[] = {1, 3, 2, 6, 4
    };

    vector<int> va(a, a + 5);

    merge_pair(va);
}
void test_queue_with_max_method()//jj
{
    int n;
    vector<int> v;

    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        int t;
        cin >> t;
        v.emplace_back(t);
    }

    myqueue mq;

    for (int i = 0; i < n; ++i)
    {
        mq.enque(v[i]);
    }

    for (int i = 0; i < n; ++i)
    {
        cout << mq.front() << " : " << mq.max() << endl;
        mq.deque();
    }

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
    node* r = reverse_list_every_other2(head);

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

void test_set_row_col()
{
    vector<vector<int> > m(3, vector<int>(3, 0));

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


void test_replace()
{
    string a("this is new world");
    string b("%20");

    replace2(a, b);

    cout << a << endl;
}

void test_string_rotate()
{
    string s;
    int idx;

    cin >> s >> idx;

    rotate(s, idx);

    cout << "the result is " << s << endl;
}

void test_unique_string()
{
    string a("abcdefg hi");
    string b("abcdefg hi ");
    cout << a << " : " << unique_str(a) << endl;
    cout << b << " : " << unique_str(b) << endl;
}
// reference
// https://github.com/andreis/interview
//


// for algorithm design or coding interview question,
// consider simple cases. For example, in uniformly randomised
// pixel of p percent black pixel, first consider if the number
// of black pixel is 1. and then 2. If the size is n, then how to
// handle n + 1?
int main()
{
    // lesson from fb 2017: I knew 3 of 4 problems, and I solved the other 1 well.
    // But I did not pass. because I pretend I do not know the problem before.
    // 문제를 다 풀기전에, 리커시브로alphacode 풀다가 잘 안된다고 DP로 넘어갔고,
    // three var sum to zero또한N^2로 풀다가 안된다고NlogN 으로 넘어갔음. 나는
    // 처음부터 하나로 해야 했고, 그리고 중간에 넘어가지 말고 끝까지 해결하는 모습을
    // 보여야 했음. 어쩌면 뭔가를 보면서 문제를 풀고있다는, 그러니까 남이 해 놓은것
    // 을 인터넷으로 보고있다는 느낌을 줬을수도 있음.
    // 또한, 나는 spacec omplexity를 틀리게 말했음. array monotonic은 O(1) 이지 O(n) 이 아니다.
    // array monotonic할 때는 알고리즘도 막 바꾸고, 인터뷰어와 소통도 하지 않았다.
    // time complexity에서, string 의 경우 find() 가 있다고 하면 이것도 time complexity에 포함할 수 있을 것 (위의 dictionary decomposit)
    test_find_min_subarray_bigger_than_x();
}

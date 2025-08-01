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
#include <climits>
#include <limits>
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
// time_point::time_since_epoch
#include <chrono>
#include <shared_mutex>

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

    // need to check like this? while (a || b)? or does not matter?
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

// merge list and return unique elements
node* merge_list_unique(node*a, node*b)//jj
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
                a = a->next;
            }
            else
            {
                prev->next = b;
                b = b->next;
            }

            if (prev->next->data == prev->data)
            {
                // remove duplicate
                auto next = prev->next;
                prev->next = next->next;
                delete next; // or just skip it
            }
            else
            {
                prev = prev->next;
            }
        }
    }

    while (prev->next) {
      if (prev->next->data == prev->data) {
        auto next = prev->next;
        prev->next = next->next;
        delete next; // or just skip it
      } else {
        prev = prev->next;
      }
    }

    return ret.next;
}


// this is a generic merge function from c++ ref, which can be used to merge two sorted iterators
// returns an output iterator to element past the last element copied.

template<class InputIt1, class InputIt2, class OutputIt>
OutputIt merge_impl(InputIt1 first1, InputIt1 last1,
               InputIt2 first2, InputIt2 last2,
               OutputIt d_first)
{
    for (; first1 != last1; ++d_first)
    {
        if (first2 == last2)
            return std::copy(first1, last1, d_first);
 
        if (*first2 < *first1)
        {
            *d_first = *first2;
            ++first2;
        }
        else
        {
            *d_first = *first1;
            ++first1;
        }
    }
    return std::copy(first2, last2, d_first);
}

std::pair<node*, node*> reverse_one_word(node* n) {
  // reverse one word
  auto p = n;
  auto old_next = n;
  n = n->next;
  while (n && n->data != 0) {
    auto next = n->next;
    n->next = p;
    p = n;
    n = next;
  }
  old_next->next = n; // set up next
  return std::make_pair(p, old_next);
}

node* reverse_word(node* n)
{
    node head(0);
    node* prev = &head;
    head.next = n;

    while (n)
    {
        // skip zero
        while (n && n->data == 0)
        {
          prev = n;
          n = n->next;
        }

        if (!n) {
            break;
        }

        // reverse one word
        auto p = n;
        auto old_next = n;
        n = n->next;
        while (n && n->data != 0) {
          auto next = n->next;
          n->next = p;
          p = n;
          n = next;
        }
        old_next->next = n; // set up next

        //set up prev
        prev->next = p;
        prev = old_next; 
        n = prev->next;
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

    do n = 5 * rand5() + rand5(); // rand5() returns 0 ~ 4
    while (n >= 21);

    return (n % 7) + 1; // return 1 ~ 7
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

// if there is no parent
nodeParent<int>* search_next(nodeParent<int>* root, nodeParent<int>* n)
{
    nodeParent<int>* next = nullptr;
    nodeParent<int>* c = root;

    while (c && c != n)
    {
        if (c->val > n->val)
        {
            next = c;
            c = c->left;
        }
        else
        {
            c = c->right;
        }
    }

    if (c == nullptr)
        return nullptr;
    else if (c->right == nullptr)
        return next;

    return search_min(c->right);
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

// leetcode 437 PathSum III
class PathSumSolution {
  public:
      int pathSum(bt_node<int>* root, int sum) {
          
          unordered_map<int, int> m;
          m[0] = 1;
          foo(root, 0, sum, m);
          
          return cnt;
      }
      
      int cnt {0};
      
      void foo(bt_node<int>* n, int t, int sum, unordered_map<int, int>& m)
      {
          if (n == nullptr)
              return;
          
          t += n->val;
          
          //if (m.count(t - sum))
          //{
              cnt += m[t - sum]; // returns 0 by default
          //}
          
          m[t]++;
          foo(n->left, t, sum, m);
          foo(n->right, t, sum, m);
          m[t]--;
      }
  };

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
void merge_sorted_array()
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

void count_char_in_sorted_array() //jj
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
void find_all_intervals_containing_x()//jj
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

}

// [-2, 0, 2, 3, 6, 7, 9] -> [2, 3]
void find_same_index_and_val_in_sorted_array(vector<int>& v, int i, int j, vector<int>& vr)//jj
{
    if (i > j)
        return;

    int m = i + (j - i) / 2;

    if (m == v[m])
    {
        vr.push_back(m);
        find_same_index_and_val_in_sorted_array(v, i, m - 1, vr);
        find_same_index_and_val_in_sorted_array(v, m + 1, j, vr);
    }
    else if (m < v[m])
    {
        find_same_index_and_val_in_sorted_array(v, i, m - 1, vr);
        find_same_index_and_val_in_sorted_array(v, v[m] + 1, j, vr);
    }
    else
    {
        find_same_index_and_val_in_sorted_array(v, i, v[m] - 1, vr);
        find_same_index_and_val_in_sorted_array(v, m + 1, j, vr);
    }
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


class matrix_search_using_lower_bound {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        if (m == 0)
            return 0;

        int n = matrix[0].size();
        if (n == 0)
            return 0;

        int i = 0, j = 0;

        do {
            j = findj(matrix[i], target);

            if (j == n)
                --j;
            else if (matrix[i][j] == target)
                return true;
            else if (j == 0)
                return false;
            else
                --j;

            i = findi(matrix, j, target);
            if (i == m)
                return false;
            else if (matrix[i][j] == target)
                return true;

        } while (i < m && j >= 0);

        return false;
    }

    int findj(vector<int>& mat, int t)
    {
        int i = 0, j = mat.size() - 1;

        while (i <= j)
        {
            int mid = i + (j - i) / 2;
            if (mat[mid] == t)
                j = mid - 1;
            else if (mat[mid] > t)
                j = mid - 1;
            else
                i = mid + 1;
        }

        return i;
    }

    int findi(vector<vector<int>>& mat, int idx, int t)
    {
        int i = 0, j = mat.size() - 1;

        while (i <= j)
        {
            int mid = i + (j - i) / 2;
            if (mat[mid][idx] == t)
                j = mid - 1;
            else if (mat[mid][idx] > t)
                j = mid - 1;
            else
                i = mid + 1;
        }

        return i;
    }

};



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
    int cap;

public:
    lrumap(int sz) : cap(sz) {}

    shared_ptr<node> get(string& s)
    {
        if (mm.find(s) != mm.end()) // if (mm.count(s)) // can be used as well
        {
            shared_ptr<node> n = mm[s];
            remove(n);
            prepend(n);
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

        if (cap == size)
        {
            shared_ptr<node> n = tail;
            remove(n);
            mm.erase(mm.find(tail->str));
        }
        else
        {
            size++;
        }

        n = shared_ptr<node>(new node(s, i));
        mm[s] = n;
        prepend(n);
    }

private:
    void remove(shared_ptr<node>& n)
    {
        if (head == n && tail == n)
        {
            n->next = n->prev = head = tail = nullptr;
        }
        else if (head == n)
        {
            head = n->next;
            n->next = n->prev = nullptr;
        }
        else if (tail == n)
        {
            tail = n->prev;
            n->next = n->prev = nullptr;
        }
        else
        {
            n->next->prev = n->prev;
            n->prev->next = n->next;
            n->next = n->prev = nullptr;
        }
    }
    void prepend(shared_ptr<node>& n)
    {
        if (head != nullptr)
        {
            n->next = head;
            head->prev = n;
            head = n;
        }
        else
        {
            head = tail = n;
        }
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

class lrumap3 {
private:

  // removing an element from the deque (not the begin or end) is O(n). So, do we need this?
  deque<pair<string, int>> l;
  map<string, deque<pair<string,int>>::iterator> mm;
  int size;
  int cnt;

public:
  explicit lrumap3(int sz) : size(sz), cnt(0) {}

  bool get(const string& s, int* x)
    {
        if (mm.find(s) != mm.end())
        {
          auto& t = mm[s];
          int i = *x = t->second;
          l.erase(t);
          l.push_front(make_pair(s, i));
          mm[s] = l.begin();
          return true;
        }
        else
        {
          return false;
        }
    }

    void put(const string& s, int i)
    {
      int t;
      auto n = get(s, &t);

      if (!n) {
        if (cnt == size) {
            auto& b = l.back();
            mm.erase(b.first);
            l.pop_back();
            cnt--;
        }
        l.push_front(make_pair(s, i));
        mm[s] = l.begin();
        cnt++;
      }
      else {
        auto a = l.begin();
        a->second = i;
      }
    }

    void print() {
        for (auto& e : l) {
            cout << e.first << " : " << e.second << endl;
        }
    }
};


// leetcode 380
// Design a data structure that supports all following operations in average O(1) time.

//     insert(val): Inserts an item val to the set if not already present.
//     remove(val): Removes an item val from the set if present.
//     getRandom: Returns a random element from current set of elements. Each element must have the same probability of being returned.
class RandomizedSet {
private:
    vector<int> v;
    unordered_map<int, int> m;
    int last {-1};

public:
    /** Initialize your data structure here. */
    RandomizedSet() {

    }

    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if (m.count(val))
            return false;

        ++last;
        v.push_back(val);
        m[val] = last;

        return true;
    }

    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        if(!m.count(val))
            return false;

        int idx = m[val];
        m.erase(val);
        if (idx != last)
        {
            v[idx] = v[last];
            m[v[idx]] = idx;

        }

        v.pop_back();
        --last;
        return true;
    }

    /** Get a random element from the set. */
    int getRandom() {
        int r = rand() % (v.size());
        return v[r];
    }
};


/*
 leetcode 381
insert(val): Inserts an item val to the collection.
remove(val): Removes an item val from the collection if present.
getRandom: Returns a random element from current collection of elements. The probability of each element being returned is linearly related to the number of same value the collection contains.
*/

class RandomizedCollectionWithDuplicate {

    unordered_map<int, unordered_set<int>> m;
    vector<int> v;
public:
    /** Initialize your data structure here. */
    RandomizedCollectionWithDuplicate() {

    }

    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) {
        v.push_back(val);
        m[val].insert(v.size() - 1);
        return m[val].size() == 1;
    }

    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) {
        if (m[val].size() == 0)
            return false;
        int idx = *(m[val].begin());
        m[val].erase(idx);
        int last = v.back();
        v[idx] = last;
        m[last].insert(idx);
        m[last].erase(v.size() - 1);
        v.pop_back();
        return true;
    }

    /** Get a random element from the collection. */
    int getRandom() {
        int r = rand() % v.size();
        return v[r];
    }
};

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


// leetcode 123
// stock share
// find the best investment period of buying and selling twice //jj
int maxProfit(vector<int>& prices) {
    if (prices.size() <= 1)
        return 0;

    vector<int> v1(prices.size(), 0);
    int mmin = prices[0];
    int mmax = 0;
    v1[0] = 0;
    for (int i = 1; i < prices.size(); ++i)
    {
        mmax = max(mmax, prices[i] - mmin);
        v1[i] = mmax;
        mmin = min(mmin, prices[i]);
    }
    int mmax1 = mmax;

    vector<int> v2(prices.size(), 0);

 #if 1
    mmax = 0;
    int tmax = prices.back();
    for (int i = prices.size() - 2; i >= 0; --i)
    {
        mmax = max(mmax, tmax - prices[i]);
        v2[i] = mmax;
        tmax = max(tmax, prices[i]);
    }
#else
    for (int i = prices.size() - 2; i >= 0; --i)
    {
        int t = prices[i + 1] - prices[i];
        v2[i] = max(t, t + v2[i + 1]);
    }
    mmax = v2.back();
    for (int i = prices.size() -2; i >= 0; --i)
    {
        mmax = max(v2[i], mmax);
        v2[i] = mmax;
    }

#endif


    mmax = 0;
    for (int i = 1; i < prices.size() - 1; ++i)
    {
        mmax = max(mmax, v1[i] + v2[i + 1]);
    }

    return max(mmax1, mmax);
}

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

    int r = maxProfit(v);

    cout << " the result is " << r << endl;
}


void test_find_best_investment_period_as_many_as_possible()
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

    int mmax = 0;

    for (int i = 1; i < v.size(); ++i)
    {
        if (v[i] > v[i - 1])
            mmax += v[i] - v[i - 1];
    }

    cout << "the result is " << mmax;
}

//leetcode 152
/*
  Given an integer array nums, find the contiguous subarray within an array (containing at least one number) which has the largest product.

  Example 1:

  Input: [2,3,-2,4]
  Output: 6
  Explanation: [2,3] has the largest product 6.
*/

int maxProduct(vector<int>& a) {

  int n = a.size();
  int maxi = a[0];
  int mini = a[0];
  int ans = a[0];

  for(int i=1;i<n;i++){
    int c1 = maxi * a[i];
    int c2 = mini * a[i];

    maxi = max(a[i],max(c1,c2));
    mini = min(a[i],min(c1,c2));
    ans = max(maxi,ans);
  }


  return ans;
}


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

// find next permutation without recursive call
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
class Solution_leetcode_53 {
    // leetcode 53
    // Given an integer array nums, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.
    // A subarray is a contiguous part of an array.
    // Example:
    // Input: [-2,1,-3,4,-1,2,1,-5,4], Output: 6
    // Explanation: [4,-1,2,1] has the largest sum = 6. 
public:
    int maxSubArray(vector<int>& nums) {
        
        if (nums.size() == 0)
            return 0;
        
        int cur_sum = nums[0];
        int max_sum = nums[0];

        for (int i = 1; i < nums.size(); ++i)
        {
            cur_sum = max(nums[i], cur_sum + nums[i]);
            max_sum = max(max_sum, cur_sum);
        }

        return max_sum;
    }

   int maxSubArray2(vector<int>& nums) {
        int maxsofar = nums[0];
        int res = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            if (maxsofar <= 0) {
                maxsofar = nums[i];
            } else {
                maxsofar += nums[i];
            }
            res = max(res, maxsofar);
        }

        return res;
    }
};

// leetcode 153
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

// leetcode 154
int find_min_from_sorted_rotated_with_duplicate(const vector<int>& v, int i, int j) //jj
{

    while (i < j)
    {
        int mid = i + (j - i) / 2;

        if (v[mid] > v[j])
            i = mid + 1;
        else if (v[mid] < v[j])
            j = mid;
        else //for handling duplicate. can't make any decision on whether we should go left or right so just remove this from search space
            j--;
    }

    return v[i];
}

// leetcode 81
// input: [1, 1, 1, 1, 1, 2, 1, 1, 1] output: 6
int find_start_index_of_min_values_from_sorted_rotated_with_duplicate(vector<int>& nums, int a, int e)
{
    while (a < e) {
        if (nums[a] < nums[e]) {
            break;
        }

        if (nums[a] == nums[e]) {
            a++;
            continue;
        }
        int mid = (a + e) / 2;
        
        if (nums[a] < nums[mid])
        {
            a = mid + 1;
        }
        else if (nums[a] > nums[mid])
        {
            e = mid;
        }
        else
        {
            a++;
        }
    }
    return a;
}


// leetcode 162
int searchPeak(vector<int> nums, int l, int r) {
  if (l == r)
    return l;
  int mid = (l + r) / 2;
  if (nums[mid] > nums[mid + 1])
    return searchPeak(nums, l, mid);
  return searchPeak(nums, mid + 1, r);

}

int findPeakElement(vector<int>& nums) {
  return searchPeak(nums, 0, nums.size() - 1);

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

int convertBase(int x, int y)
{
    bool negative = (x < 0);

    x = abs(x);

    int r = 0, k = 1;
    while (x > 0)
    {
        int a = x / y;
        int b = x % y;
        r = r + k * b;
        x = a;
        k = k * 10;
    }

    return negative? -r : r;
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

void test_2_workers_n_jobs() //jj
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
  Given an unsorted array nums, reorder it such that nums[0] < nums[1] > nums[2] < nums[3]....

  Example 1:

  Input: nums = [1, 5, 1, 1, 6, 4]
  Output: One possible answer is [1, 4, 1, 5, 1, 6].
*/
void wiggleSort(vector<int>& nums)
{
    vector<int> v(nums);

    sort(v.begin(), v.end());
    for (int i = 0, j = 0; i < nums.size() / 2; ++i, j += 2)
    {
        nums[j] = v[(nums.size() - 1)/ 2 - i];
        nums[j + 1] = v[nums.size() - 1 - i];
    }

    if (nums.size() % 2)
    {
        nums[nums.size() - 1] = v[0];
    }

    return;
}

void test_sort_small_big_small_number() //jj //without extra space? can we do it? find max then swap, find min then swap, ...
{
  int n;
  cin >> n;

  vector<int> v;
  for (int i = 0; i < n; ++i) {
    int t;
    cin >> t;
    v.emplace_back(t);
  }

  wiggleSort(v);

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
// regarding above test, see also leetcode 352.


// array monotonic. Space complexity does not count the origial space, just count additional space, so this is
// O(N) time complexity, and O(1) space complexity.
class MonotonicArrayChecker // jj
{
public:
  bool check_array_is_keep_increasing_decreasing(vector<int> &a) // jj
  {
    if (a.size() < 2) {
      return true;
    }
    int d = 0;

    for (int i = 1; i < a.size(); ++i) {
      if (a[i] > a[i - 1]) {
        if (d == -1) {
          return false;
        }
        d = 1;
      } else if (a[i] < a[i - 1]) {
        if (d == 1) {
          return false;
        }
        d = -1;
      } else {
        // do nothing, just continue
        // do not need to change d, just keep it as is.
        continue;
      }
    }

    return true;
  }

  bool check_array_is_keep_increasing_decreasing_2(vector<int> &a) // jj
  {
    if (a.size() < 2) {
      return true;
    }

    int i = 1;
    while (i < a.size() && a[i] == a[i - 1]) {
      ++i;
    }

    if (i == a.size()) {
      return true;
    }

    int d = a[i] - a[i - 1];
    ++i;

    for (; i < a.size(); ++i) {
      if (a[i] == a[i - 1]) {
        continue;
      }
      if ((a[i] - a[i - 1]) * d < 0) {
        return false;
      }
    }

    return true;
  } 
};

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


// leetcode 5
// find the number of longest palindrome substring
// Given a string s, find the longest palindromic substring in s
// Example 1:

// Input: "babad"
// Output: "bab"
// Note: "aba" is also a valid answer.
// sol1: DP
// sol2 : Brute force (scan from left to right, check if it is palindrom (scan left and right).
// sol3: using BFS (start with base case, expand)
string longestPalindromeDP(string s) {
  // P(i,j)=(P(i+1,j−1) and S[i]​ ==S[j]​)
  // The base cases are:
  // P(i, i) = true
  // P(i, i + 1) = ( S[i] == S[i + 1])

  if (s.empty())
    return s;

  vector<vector<bool>> v(s.size(), vector<bool>(s.size(), false));

  string ans;
  int len = 0;

  for (int j = 0; j < s.size(); ++j)
    {
      for (int i = 0; i <= j; ++i)
        {
          auto same = s[i] == s[j];

          v[i][j] = j - i >= 2 ? same && v[i + 1][j - 1] : same;

          if (v[i][j] && j - i + 1 > len)
            {
              len = j - i + 1;
              ans = s.substr(i, len);
            }
        }
    }

  return ans;
}

void test_find_longest_palindromic_substring()
{
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
// knapsack problem. Each item has a value and a weight.
//  Given a knapsack with a maximum weight capacity, find the maximum value of items that can be put in the knapsack.
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


int non_dec_seq_dp(vector<int>& v)
{
    vector<int> vd(v.size(), 1);

    for (int i = 1; i < v.size(); ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (v[j] <= v[i])
            {
                vd[i] = max(vd[i], 1 + vd[j]);
            }
        }
    }

    return *max_element(vd.begin(), vd.end());
}

int non_dec_seq_nlogn(vector<int>& A)
{
    //nlog(n)
    vector<int> arr;
    for (int i = 0; i < A.size(); i++)
        if (arr.empty() || A[i] >= arr[arr.size() - 1])
            arr.push_back(A[i]);
        else
            *(lower_bound(arr.begin(), arr.end(), A[i])) = A[i];
    return arr.size();
}

// leetcode 376
// A sequence of numbers is called a wiggle sequence if the differences between successive numbers strictly alternate between positive and negative. The first difference (if one exists) may be either positive or negative. A sequence with fewer than two elements is trivially a wiggle sequence.
//   For example, [1,7,4,9,2,5] is a wiggle sequence because the differences (6,-3,5,-7,3) are alternately positive and negative. In contrast, [1,4,7,2,5] and [1,7,4,5,5] are not wiggle sequences, the first because its first two differences are positive and the second because its last difference is zero.
//   Given a sequence of integers, return the length of the longest subsequence that is a wiggle sequence. A subsequence is obtained by deleting some number of elements (eventually, also zero) from the original sequence, leaving the remaining elements in their original order.
//   Example 1:
//                                                                                                                                      Input: [1,7,4,9,2,5]
//   Output: 6
//   Explanation: The entire sequence is a wiggle sequence.

int wiggleMaxLength(vector<int>& nums) {
  if(nums.size() <= 1)    return nums.size();
  int max_wiggle{1};
  int slope = 0;
  for(int i=1; i<nums.size(); i++) {
    if(nums[i] > nums[i-1] && slope <= 0) {
      slope = 1;
      max_wiggle++;
    }
    if(nums[i] < nums[i-1] && slope >= 0) {
      slope = -1;
      max_wiggle++;
    }
  }
  return max_wiggle;
}

// leetcode 978, longest turbelent subarray
// 9, 4, 2, 10, 7, 8, 8, 1, 9 -> 5.  because 4, 2, 10, 7, 8 are turbelent.
// 4, 8, 12, 16 -> 2. b
class turbulent {
    int test_turbulence(const vector<int>& input) {

        int d = 0;
        int cnt = 1;
        int max_cnt = 1;
        for (int i = 1; i < input.size(); ++i) {
            if (input[i] > input[i - 1]) {
                if (d <= 0) {
                    ++cnt;
                    if (cnt > max_cnt) {
                        max_cnt = cnt;
                    }
                } else {
                    cnt = 2;
                }
                d = 1;

            } else if (input[i] < input[i - 1]) {
                if (d >= 0) {
                    ++cnt;
                    if (cnt > max_cnt) {
                        max_cnt = cnt;
                    }
                } else {
                    cnt = 2;
                }
                d = -1;

            } else {
                d = 0;
                cnt = 1;
            }
        }
        if (cnt > max_cnt) {
            max_cnt = cnt;
        }

        return max_cnt;
    }

    public:
    void test() {
       cout << test_turbulence({9, 4, 2, 10, 7, 8, 8, 1, 9}) << "shout be 5" << endl; 
       cout << test_turbulence({4, 8, 12, 16}) << "should be 2 " << endl; 
    }
};
/*
  Given an unsorted array return whether an increasing subsequence of length 3 exists or not in the array.
 */
bool increasingTriplet(vector<int>& nums) {

    if (nums.size() == 0)
        return false;

    vector<int> v;

    v.push_back(nums[0]);

    for (int i = 1; i < nums.size(); ++i)
    {
        if (nums[i] > v.back())
        {
            v.push_back(nums[i]);
            if (v.size() == 3)
                return true;
        }
        else
        {
            *lower_bound(v.begin(), v.end(), nums[i]) = nums[i];

        }
    }

    return false;
}


// leetcode 373
// You are given two integer arrays nums1 and nums2 sorted in ascending order and an integer k.
// Define a pair (u,v) which consists of one element from the first array and one element from the second array.
//   Find the k pairs (u1,v1),(u2,v2) ...(uk,vk) with the smallest sums.

//   Example 1:
//                                         Input: nums1 = [1,7,11], nums2 = [2,4,6], k = 3
//   Output: [[1,2],[1,4],[1,6]]
//   Explanation: The first 3 pairs are returned from the sequence:
//                                         [1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]
vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {

  // see belowfor python implementation using min heap: this solution is using max heap. There is a solution using min heap. See the submission in the leetcode (python)
  using elem = pair<int, pair<int, int>>;
  vector<elem> v;

  auto comp = [](elem&a, elem &b) {

                return a.first < b.first;

              };

  priority_queue<elem, vector<elem>, decltype(comp)> pq(comp);


  for (int i = 0; i < nums1.size() && i < k; ++i)
    {
      for (int j = 0; j < nums2.size() && j < k; ++j)
        {
          if (pq.size() < k)
            {
              pq.push(elem(nums1[i] + nums2[j], {nums1[i], nums2[j]}));
            }
          else
            {
              if (nums1[i] + nums2[j] < pq.top().first)
                {
                  pq.push(elem(nums1[i] + nums2[j], {nums1[i], nums2[j]}));
                  pq.pop();
                }
            }
        }
    }

  vector<vector<int>> r;

  while (!pq.empty())
    {
      auto x = pq.top();
      r.push_back({x.second.first, x.second.second});
      pq.pop();
    }

  return r;
}

 
// also see leetcode 378


// Using min heap. See this!!
/*
def kSmallestPairs(self, A, B, k):
  """
        :type nums1: List[int]
        :type nums2: List[int]
        :type k: int
        :rtype: List[List[int]]
        """
  #
  La,Lb   = len(A) , len(B)
  ijvalid = lambda i,j: i<La and j<Lb
  genkey  = lambda i,j: (A[i]+B[j],i,j)
  #
  visited = { (0,0) }
  C       = [ genkey(0,0) ] if (A and B) else []
                                   D       = []
                                   #
                                   while len(D)<k and C:
                                                _,i,j = heapq.heappop(C)
                                                D.append( [ A[i] , B[j] ] )
                                                #
                                                for x,y in ((i+1,j),(i,j+1)):
                                                if  ijvalid(x,y) and not (x,y) in visited:
                                                heapq.heappush( C , genkey(x,y) )
                                                visited.add( (x,y) )
                                                #
                                                return D

*/


// leetcode 313 nth super ugly number
// write a program to find the nth super ugly number.
// Super ugly numbers are positive numbers whose all prime factors are in the given prime list primes of size k.
// Example:
// Input: n = 12, primes = [2,7,13,19]
//                           Output: 32
//                           Explanation: [1,2,4,7,8,13,14,16,19,26,28,32] is the sequence of the first 12
//                           super ugly numbers given primes = [2,7,13,19] of size 4.
int nthSuperUglyNumber(int n, vector<int>& primes) {
  vector<int> k(primes.size(), 0);
  vector<int> v(n, 0);
  v[0] = 1;

  for (int i = 1; i < n; ++i)
    {
      int m = INT_MAX;
      for (int j = 0; j < primes.size(); ++j)
        {
          int val = primes[j] * v[k[j]];
          m = min(val, m);
        }

      v[i] = m;
      for (int j = 0; j < primes.size(); ++j)
        {
          if (m == primes[j] * v[k[j]])
            ++k[j];
        }
    }

  return v[n - 1];
    }

//leetcode 363
class  MaxSumSubMatrix{
    // Given a non-empty 2D matrix matrix and an integer k, find the max sum of a rectangle in the matrix such that its sum is no larger than k.
    //     Example:
    //     Input: matrix = [[1,0,1],[0,-2,3]], k = 2
    //     Output: 2
    //     Explanation: Because the sum of rectangle [[0, 1], [-2, 3]] is 2,
    //     and 2 is the max number no larger than k (k = 2).
public:
    // copy from Discuss
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
              // Precompute column prefix sums
        for (int row = 0; row < matrix.size(); ++row) {
            int currSum = 0;
            for (int col = 0; col < matrix[row].size(); ++col) {
                currSum += matrix[row][col];
                matrix[row][col] = currSum;
            }
        }

        int maxSum = INT_MIN;
        for (int lCol = 0; lCol < matrix[0].size(); ++lCol) {
            for (int rCol = lCol; rCol < matrix[0].size(); ++rCol) {

                set<int> bst; // RB tree
                bst.insert(0);

                int rowPrefSum = 0;
                for (int row = 0; row < matrix.size(); ++row) {
                    int currSum = matrix[row][rCol] - (lCol == 0 ? 0 : matrix[row][lCol-1]);
                    rowPrefSum += currSum;

                    auto searchRes = bst.lower_bound(rowPrefSum - k);

                    if (searchRes != bst.end()) {
                        maxSum = max(maxSum, rowPrefSum - *searchRes);
                    }

                    bst.insert(rowPrefSum);
                }


            }
        }

        return maxSum;
    }
};

// Input:  words[] = {"baa", "abcd", "abca", "cab", "cad"}
// Output: Order of characters is 'b', 'd', 'a', 'c'
//                                      Note that words are sorted and in the given language "baa"
//                                      comes before "abcd", therefore 'b' is before 'a' in output.
//                                      Similarly we can find other orders.

// Input:  words[] = {"caa", "aaa", "aab"}
// Output: Order of characters is 'c', 'a', 'b'
void alien_language()
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

/*

  // DP palindrom
  // compute matrix v[i][j] which tells that substring s[i,j] is palindrom.
    void compute_palindrom_matrix(vector<vector<char>>& v, string& s)
    {
        for (int i = 0; i < v.size(); ++i)
        {
            v[i][i] = 1;
        }

        for (int step = 2; step <= v.size(); step += 2)
        {
            for (int i = 0; i + step <= v.size(); ++i)
            {
                char a = (s[i] == s[i + step - 1]);
                if (step == 2)
                {
                    v[i][i + step - 1] = a;
                }
                else
                {
                    v[i][i + step - 1] = a && v[i + 1][i + step - 2];
                }
            }
        }

        for (int step = 1; step < v.size(); ++step)
        {
            for (int i = step; i + step < v.size(); ++i)
            {
                char a = (s[i - step] == s[i + step]);
                if (step == 1)
                {
                    v[i - step][i + step] = a;
                }
                else
                {
                    v[i - step][i + step] = a && v[i - step + 1][i + step - 1];
                }
            }
        }
    }

 */



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

// moving average of last N numbers in a stream
// For example, if N=3 and the stream S=[2,3,4,1,2,-3,0,…] then moving averages at each each streamed number are = [2.0, 2.5, 3.0, 2.66, 2.33, 0, -0.33,…].
void moving_average_of_last_n()
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


void find_number_of_subarrays_sum_to_k()
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
// also see Leetcode 547.
void find_island_from_2_dimensional_array()
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

            int a = (i == 0)? 0 : v[i - 1][j] == 'x';
            int b = (j == 0)? 0 : v[i][j - 1] == 'x';

            if (a == 0 && b == 0)
            {
                vi.emplace_back(count);
                vr[cur][j] = count;
                ++count;
            }
            else if (a == 0)
            {
                vr[cur][j] = vr[cur][j - 1];
            }
            else if (b == 0)
            {
                vr[cur][j] = vr[prev][j];
            }
            else if (vr[cur][j - 1] == vr[prev][j])
            {
                vr[cur][j] = vr[cur][j - 1];
            }
            else
            {
                vr[cur][j] = vr[cur][j - 1];
                auto x = vr[prev][j];
                auto y = vr[cur][j];
                while (vi[x] != x)
                    x = vi[x];

                while (vi[y] != y)
                    y = vi[y];

                vi[x] = vi[y];
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


    r = non_dec_seq_dp(v);
    cout << "the result is " << r << endl;
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

void test_check_balanced()
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
    end = end->next;
    end->next = new node(0);

    node* r = reverse_word(head);
    node* r2 = r;
    while (r)
    {
        cout << r->data << " ";
        r = r-> next;
    }

    std::cout << std::endl;
    r = reverse_word(r2->next);
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

void test_merge_linked_list_unique()
{
  std::cout << "test merge list unique" << std::endl;
    node* head = new node(1);
    node* end = head;
    end->next = new node(3);
    end = end->next;
    end->next = new node(4);
    end = end->next;
    end->next = new node(7);
    end = end->next;
    end->next = new node(7);

    node* head2 = new node(2);
    node* end2 = head2;
    end2->next = new node(4);
    end2 = end2->next;
    end2->next = new node(5);
    end2 = end2->next;
    end2->next = new node(5);
    end2 = end2->next;
    end2->next = new node(6);

    node* r = merge_list_unique(head, head2);

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


class editor {
public:

    editor() : cur(l.begin()) {}

    void insert(char c)
    {
        cur = l.insert(cur, c);
        h.push({true, distance(l.begin(), cur), c});
        ++cur;
    }

    void backs()
    {
        if (cur == l.begin())
            return;

        --cur;
        char c = *cur;
        h.push({false, distance(l.begin(), cur), c});
        cur = l.erase(cur);
    }

    void ml()
    {
        if (cur == l.begin())
            return;

        --cur;
    }

    void mr()
    {
        if (cur == l.end())
            return;

        ++cur;
    }

    void undo()
    {
        if (h.empty())
        {
            cout << "no more history" << endl;
            return;
        }

        auto e = h.top();
        h.pop();
        if (e.type)
        {
            // if insert, perform remove
            l.erase(next(l.begin(), e.loc));
        }
        else
        {
            l.insert(next(l.begin(), e.loc), e.c);
        }
    }

    void print()
    {
        if (l.empty())
        {
            cout << "empty" << endl;
        }

        for (auto e: l)
        {
            cout << " " << e;
        }

        cout << endl;
    }


private:

    struct record {
        bool type;
        long int loc;
        char c;
    };

    list<char> l;
    stack<record> h;
    list<char>:: iterator cur;
};

void test_editor_using_list()
{
    editor e;

    e.ml();
    e.mr();
    e.backs();
    e.insert('c');
    e.print();
    e.insert('b');
    e.print();
    e.insert('a');
    e.print();
    e.ml();
    e.backs();
    e.print();
    e.mr();
    e.mr();
    e.mr();
    e.backs();
    e.print();
    e.backs();
    e.print();
    e.undo();
    e.print();
    e.undo();
    e.print();
    e.undo();
    e.print();
    e.undo();
    e.print();
    e.undo();
    e.print();
    e.undo();
    e.print();
    e.undo();
    e.print();
}


// reference
// https://github.com/andreis/interview
//


// for algorithm design or coding interview question,
// consider simple cases. For example, in uniformly randomised
// pixel of p percent black pixel, first consider if the number
// of black pixel is 1. and then 2. If the size is n, then how to
// handle n + 1?

void test_lower_bound_upper_bound()
{
    vector<int> v{1, 2, 3, 5, 6, 7};

    cout << "lower bound " << *lower_bound(v.begin(), v.end(), 4) << " and upper bound " << *upper_bound(v.begin(), v.end(), 4) << endl;

    vector<char> vc{1, 2, 3, 5, 6, 7};
    cout << "lower bound " << find_beg(vc, 0, vc.size() - 1, 4) << " and upper bound " << find_end(vc, 0, vc.size() - 1, 4) << endl;
}


pair<int, int> getnext(int x, int y, int& left, int& right, int& top, int& bottom, int& d)
{
    pair<int, int> r;
    if (d == 1)
    {
        if (x == right)
        {
            r.first = x;
            r.second = y + 1;
            d = 2;
            ++top;
        }
        else
        {
            r.first = x + 1;
            r.second = y;
        }
    }
    else if (d == 2)
    {
        if (y == bottom)
        {
            r.first = x - 1;
            r.second = y;
            d = 3;
            --right;
        }
        else
        {
            r.first = x;
            r.second = y + 1;
        }
    }
    else if (d == 3)
    {
        if (x == left)
        {
            r.first = x;
            r.second = y - 1;
            d = 4;
            --bottom;
        }
        else
        {
            r.first = x - 1;
            r.second = y;
        }
    }
    else
    {
        if (y == top)
        {
            r.first = x + 1;
            r.second = y;
            d = 1;
            ++left;
        }
        else
        {
            r.first = x;
            r.second = y - 1;
        }
    }

    return r;
}

void test_spiral()
{
    int n;

    cin >> n;

    int size = n * n;
    vector<vector<int>> v(n, vector<int>(n, 0));
    int x = 0, y = 0;
    int left = 0, right = n - 1, top = 0, bottom = n - 1, d = 1;

    for (int i = 0; i < size; ++i)
    {
        v[y][x] = i;
        auto r = getnext(x, y, left, right, top, bottom, d);
        x = r.first;
        y = r.second;
    }

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cout << v[i][j] << " ";
        }
        cout << endl;
    }
}

/*
  leetcode 318
Given a string array words, find the maximum value of length(word[i]) * length(word[j]) where the two words do not share common letters. You may assume that each word will contain only lower case letters. If no such two words exist, return 0.

Example 1:

Input: ["abcw","baz","foo","bar","xtfn","abcdef"]
Output: 16
Explanation: The two words can be "abcw", "xtfn".
*/
// using bit vector to check letters are unique between two strings
int maxProduct(vector<string>& words)
{
    if(!words.size()) return 0;

    vector<int> hash(words.size(), 0);

    for(int i = 0; i < words.size(); i++)
    {
        for(char c: words[i])
        {
            hash[i] |= (1 << (c - 'a'));
        }
    }

    int mx = 0;

    for(int i = 0; i < words.size() - 1; i++)
    {
        for(int j = i+1; j < words.size(); j++)
        {
            if((hash[i] & hash[j]) == 0)
            {
                mx = max(mx, (int)words[i].size() * (int)words[j].size());
            }
        }
    }
    return mx;
}

class LFUCache {
    int cap;

  // O(1) algorithm
    using elem = pair<int, list<pair<int, int>>::iterator>;
    unordered_map<int, elem> m; // key -> (freq, list_iter)
    unordered_map<int, list<pair<int, int>>> t; // freq -> list (key/val)
    unordered_map<int, list<int>::iterator> lm; // freq -> list(freq)
    list<int> l; // list of frequency

public:
    LFUCache(int capacity) : cap{capacity} {

    }

    int get(int key) {
        if (m.count(key) == 0)
            return -1;

        auto x = m[key];
        auto freq = x.first;
        auto b = x.second;

        int data = b->second;
        t[freq].erase(b);

        auto it = next(lm[freq]);  // next freq

        if (t[freq].empty())
        {
            t.erase(freq);
            l.erase(lm[freq]);
            lm.erase(freq);
        }

        if (it == l.end() || *it != (freq + 1))
        {
            auto iter = l.insert(it, freq + 1);
            lm[freq + 1] = iter;
        }

        t[freq + 1].push_back(pair<int, int>(key, data));

        m[key] = elem(freq + 1, prev(t[freq + 1].end()));

        return data;
    }

    void putImpl(int key, int value)
    {
        int freq = 0;
        list<int>::iterator it;

        if (m.count(key) != 0)
        {
            auto x = m[key];
            freq = x.first;
            auto b = x.second;

            t[freq].erase(b);

            it = next(lm[freq]);  // next freq

            if (t[freq].empty())
            {
                t.erase(freq);
                l.erase(lm[freq]);
                lm.erase(freq);
            }
        }
        else
        {
            it = l.begin();
        }

        if (it == l.end() || *it != (freq + 1))
        {
            auto iter = l.insert(it, freq + 1);
            lm[freq + 1] = iter;
        }

        t[freq + 1].push_back(pair<int, int>(key, value));

        m[key] = elem(freq + 1, prev(t[freq + 1].end()));
    }

    void remove()
    {
        auto it = l.begin();
        auto freq = *it;
        auto x = t[freq].begin();
        m.erase(x->first);
        t[freq].erase(x);
        cout << "remove: " << x-> first << " " << freq << endl;

        if (t[freq].empty())
        {
            t.erase(freq);
            l.erase(it);
            lm.erase(freq);
        }
    }

    void put(int key, int value) {
        if (cap == 0)
            return;
        if (m.size() == cap && m.count(key) == 0)
        {
            remove();
        }

        putImpl(key, value);
   }
};

void test_lfu_cache()
{
  LFUCache c(10);
  c.put(10, 13);
  c.put(3, 17);
  c.put(6, 11);
  c.put(10,5);
  c.put(9,10);
  c.get(13);
  c.put(2, 19);
  c.get(2);
  c.get(3);
  c.put(5,25);
  c.get(8);
  c.put(9,22);
  c.put(5,5);
  c.put(1,30);
  c.get(11);
  c.put(9,12);
  c.get(7);
  c.get(5);
  c.get(8);
  c.get(9);
  c.put(4,30);
  c.put(9,3);
  c.get(9);
  c.get(10);
  c.get(10);
  c.put(6,14);
  c.put(3,1);
  c.get(3);
  c.put(10,11);
  c.get(8);
  c.put(2,14);
  c.get(1);
  c.get(5);
  c.get(4);
  c.put(11,4);
  c.put(12,24);
  c.put(5,18);
  c.get(13);
  c.put(7,23);
  c.get(8);
  c.get(12);
  c.put(3,27);
  c.put(2,12);
  c.get(5);
  c.put(2,9);
  c.put(13,4);
  c.put(8,18);
  c.put(1,7);
  c.get(6);
}

void test_time()
{
  using namespace std::chrono;

  system_clock::time_point tp = system_clock::now();
  system_clock::duration dtn = tp.time_since_epoch();
  unsigned long long x = system_clock::now().time_since_epoch().count();

  std::cout << "current time since epoch, expressed in:" << std::endl;
  std::cout << "periods: " << dtn.count() << " " << x <<  std::endl;
  std::cout << "seconds: " << dtn.count() * system_clock::period::num / system_clock::period::den;
  std::cout << std::endl;
}

class TimeInterface {
public:
    virtual long long GetTime() = 0;
};

// which entity needed? RateLimiter, Rule, and Counter?

class RateLimiter {

public:
  RateLimiter(TimeInterface& ti) : mTime(ti) {}
  // time is msec
  bool rateLimit(int customerId)
  {
    return hit(customerId, mTime.GetTime());
  }

private:

  // need to be private? or exernal entity? if we want to scale then what?
  class Customer {
    public:
        deque<long long> queue;
        mutex  mtx;
        // these should be per customer as well?
        int MaxDur{1000}; // 1sec == 1000ms
        int MaxReq{2};
  };

  TimeInterface& mTime;
  unordered_map<int, unique_ptr<Customer>> m;
  mutex mtx;

  bool hit(int customerID, long long t)
  {
    if (!m.contains(customerID)) {
        scoped_lock<mutex> lck(mtx);
        if (!m.contains(customerID)) {
            // mutex or atomic made me to use unique_ptr.
            m.emplace(make_pair(customerID, unique_ptr<Customer>()));
        }
    }

    unique_lock<mutex> ulck(mtx);
    auto& c = m.at(customerID);
    ulck.unlock();

    // delete old timestamp than MaxDur
    // lock should be per client not for all of them
    // or can we use spinlock?
    scoped_lock<mutex> lck{c->mtx};
    while (!c->queue.empty() && c->queue.front() < t - c->MaxDur) {
        c->queue.pop_front();
    }

    if (c->queue.size() < c->MaxReq) {
        c->queue.push_back(t);
        return true;
    } else {
      return false;
    }
  }
};

class Bucket {
public:
  explicit Bucket(int size, int refill) : mRefill(refill), mSize(size), mCnt(refill) {}
  void Refill() {
    auto cnt = mCnt.load();
    if (cnt == mSize) { return; }
    auto expected = min(mSize, cnt + mRefill);
    
    while(!mCnt.compare_exchange_strong(cnt, expected)) {
      cnt = mCnt.load();
      if (cnt == mSize) { return; }
      expected = min(mSize, cnt + mRefill);
    }
  }

  bool Dec() {
    auto cnt = mCnt.load();
    if (cnt == 0) {
        return false;
    }
    while(!mCnt.compare_exchange_strong(cnt, cnt - 1)) {
      cnt = mCnt.load();
      if (cnt == 0) {
        return false;
      }
    }

    return true;
  }

private:
  int mRefill;
  int mSize;
  atomic<int> mCnt;
};

class TimerObserverInterface {
    virtual void Observe() = 0;
};

class RateLimiter2: public TimerObserverInterface {
public:
  RateLimiter2() {}
  bool RateLimit(int customer_id) {
    if (!m.contains(customer_id)) {
        unique_lock lck(mtx); // should use spinlock here?
        if (!m.contains(customer_id)) {
            // mutex or atomic made me to use unique_ptr.
            m.emplace(make_pair(customer_id, make_unique<Bucket>(10, 2))); 
        }
    }
    shared_lock lck(mtx);
    auto& c =  m.at(customer_id);
    lck.unlock();
    return c->Dec();
  }

  void Refill(int customer_id) {
    shared_lock lck(mtx);
    if (!m.contains((customer_id))) { return; }
    auto& c =  m.at(customer_id);
    lck.unlock();
    c->Refill();
  }

  void Observe() override {
    shared_lock lck(mtx);
    for (auto& e: m) {
        e.second->Refill();
    }
  }

private:
  unordered_map<int, shared_ptr<Bucket>> m;
  shared_mutex mtx;
};

// leetcode 353
class SnakeGame {
    public:

    SnakeGame(int w, int h, const vector<vector<int>>& f) : width(w), height(h), food(f) {
        // initial position.
        snake.push_back(make_pair(0, 0));
        snake_set.insert(make_pair(0, 0));
    }

    int move(const string& direction) {

        // get next position.
        auto [new_x, new_y] = snake.back(); // back is the head, front is the tail

        if (direction == "D") {
                new_y++;
        }
        else if (direction == "U") {
                new_y--;
        }
        else if (direction == "R") {
                new_x++;
        }
        else if (direction == "L") {
                new_x--;
        }

        if (new_x < 0 || new_x >= width || new_y < 0 || new_y >= height) {
            return -1;
        }

        if (cur_food < food.size() && food[cur_food][0] == new_x && food[cur_food][1] == new_y) {
            snake.push_back(make_pair(new_x, new_y));
            snake_set.insert(make_pair(new_x, new_y));
            ++cur_food;
            ++score;
        }
        else {
            snake_set.erase(snake.front());
            snake.pop_front(); // moving, so previous tail is removed
            // optimise: use map for faster lookup
            // if (find(snake.begin(), snake.end(), make_pair(new_x, new_y)) != snake.end()) {
            if (snake_set.find(make_pair(new_x, new_y)) != snake_set.end()) {
                return -1;
            } else {
                snake.push_back(make_pair(new_x, new_y));
                snake_set.insert(make_pair(new_x, new_y));
            }
        }

        return score;
    }

    private:

    int width;
    int height;
    int score{0};
    vector<vector<int>> food;
    int cur_food {0};
    deque<pair<int, int>> snake; // queue has no iterator, so search is impossible. same with stack.
    set<pair<int, int>> snake_set;
};


// Given a list of files with multiple tags associated with them, group the files based on tags and return a list of top tags based on total file size.
class FileTagging {
public:

vector<string> GetTopTags(vector<tuple<string, int, vector<string>>> file_list, int k) {
    map<string, vector<string>> tag_map;
    map<string, int> tag_map_size;
    for (auto& [file, size, tags] : file_list) {
        for (auto& tag : tags) {
            tag_map[tag].push_back(file);
            tag_map_size[tag] += size;
        }
    }

    using elem = pair<string, int>;
    auto comp = [](elem &a, elem& b) {
        return a.second > b.second;
    };

    priority_queue<elem, vector<elem>, decltype(comp)> pq(comp);
    for (auto& [tag, size] : tag_map_size) {
        if(pq.size() < k) {
            pq.push(make_pair(tag, size));
        } else if (size > pq.top().second) {
            pq.pop();
            pq.push(make_pair(tag, size));
        }
    }

    vector<string> r;
    while (!pq.empty()) {
        r.push_back(pq.top().first);
        pq.pop();
    }

    return r;
}

};

class optiver {
// driving to byron bay:
// find minimum petrol pay along the path. 1km/l for the car. petrol prices are different among the
// petrol station. each station is at most 50 km distance. car has empty tank, at station 0, and tank capacity is 50 liter.
// input is a list of petrol station distance and petrol prices. At the end, tank should be empty. if distance[0] is 30, means
// station 0 and station 1 is 30 km away. price[0] is 3 means that price at station 0 is 3/l.
//ex: [10, 20, 5, 20] and [3, 4, 2, 3] -> 140. 30 * 3 + 25 * 2.
// leetcode 410, 514
int foo(const vector<int>& d, const vector<int>& prices, int fuel_tank, int idx, vector<vector<int>>& v) {
    
    if (idx == d.size()) {
        if (fuel_tank == 0) {
            return 0;
        } else {
            return INT_MAX;
        }
    }
    
    if (v[fuel_tank][idx] != -1) {
        return v[fuel_tank][idx];
    }
    
    int start = fuel_tank >= d[idx] ? 0 : d[idx] - fuel_tank;
    
    int r = INT_MAX;
    for (int i = start; i <= 50 - fuel_tank; ++i) {
        int money = i * prices[idx]; 
        int x = foo(d, prices, fuel_tank + i - d[idx], idx + 1, v);
        if (x == INT_MAX) {
            continue;
        }
        r = min(x + money, r); 
    }
    v[fuel_tank][idx] = r;
    
    return r;
}

// leetcode 399 is the same problem.
// given a list of exchange rate, find the maximum amount of money you can get.
// input: {"USDAUD@1.4", "AUDNZD@1.1"}, "USD", "NZD", 1.0
// output: 1.4 * 1.1 * 1 = 1.6
// if no possible exchange rate, return -1.
// there would be a cycle, so use a visited array to avoid infinite loop. 
double dfs(unordered_map<string, vector<pair<string, double>>>& graph, const string& from, const string& end, double money, unordered_set<string>& visited) {
    if (from == end) {
        return money;
    }
    if (visited.find(from) != visited.end()) {
        return -1.0;
    }
    visited.insert(from);
    double r = -1;
    for (auto& [to, rate] : graph[from]) {
        double x = dfs(graph, to, end, money * rate, visited);
        r = max(r, x);
    }
    visited.erase(from);
    return r;
}
double GetMaxExchangeRate(const vector<string>& exchange_rate, const string& from, const string& to, double money) {
    // step1: graph structure
    unordered_map<string, vector<pair<string, double>>> graph;
    // setup graph structure
    unordered_set<string> visited;
    // step2: dfs with visited array. find the max result.
    return dfs(graph, "USD", "NZD",  money, visited);
}

int bar(const vector<int>& d, const vector<int>& prices) {

    vector<vector<int>> v(d.size() + 1, vector<int>(51, INT_MAX));

    v[d.size()][0] = 0;

    for (int i = d.size() - 1; i >= 0; --i) {
        for (int j = 0; j <= 50; ++j) { // fule tank
            int r = INT_MAX;
            for (int k = 0; k <= 50; ++k) { // petrol station fuel add
                // int a = (j >= d[i])? v[i + 1][j - d[i]] : INT_MAX;
                int b = (j + k <= 50) ? k : (50 - j);
                if (j + b < d[i]) {
                    continue;
                }
                if (v[i + 1][j + b - d[i]] == INT_MAX) {
                    continue;
                }

                r = min(r, b * prices[i] + v[i + 1][j + b - d[i]]);
            }
            v[i][j] = r;
        }
    }

    return v[0][0];
}

public:
int calculate(vector<int> distances, vector<int> prices) {

vector<vector<int>> v(50, vector<int>(distances.size(), -1));
//    return  foo(distances, prices, 0, 0, v);
   return  bar(distances, prices);
}
};

class ghost {
    // binary tree with int value. The value is either 1 or 0. The value of a node is 1 if and only if both of its child (left and right) are 1. 
    // You are given TREE_DEPTH as a global variable, and ClearNode(int level, int offset), bool GetNode(int level, int offset), SetNode(int level, int offset).
    // Implement ClearRanges(int offset, int range) and SetRanges(int offset, int range) that either clear or sets a range in the leaf nodes.
    // You should consider the invariants that a parent node should be 1 if and only if all if its child are 1. If one of the child became 0 then parent should be 0 as well.
    // The binary tree is full (all of its leaf nodes are full.)

    // offset is in range [0, size of all leaf nodes)
    // range is in range [1, size of all leaf nodes).
    // This tree has 3 levels (level 0, level 1, level 2). To clear the second node of the leaf level, ClearNode(2, 1).
    // 0
    // 0   1
    // 0 1 1 1
    int TREE_DEPTH = 3; // depth is 3
    void ClearNode(int level, int offset) {}
    void SetNode(int level, int offset) {}
    bool GetNode(int level, int offset) { return true;}
    void ClearRanges(int offset, int range) {
        if (offset < 0 || offset >= (1 << TREE_DEPTH)) {
            return;
        }
        if (range <= 0 || range > (1 << TREE_DEPTH)) {
            return;
        }

        int first = offset;
        int last = offset + range - 1;
        int level = TREE_DEPTH - 1;

        while (first <= last) {
            for (int i = first; i <= last; ++i) {
                ClearNode(level, i);
            }
            first = first / 2;
            last = last / 2;
            level -= 1;
        }
    }

    void SetRanges(int offset, int range) {
        int first = offset;
        int last = offset + range - 1;
        int level = TREE_DEPTH - 1;

        while (first <= last) {
            for (int i = first; i <= last; ++i) {
                SetNode(level, i);
            }
            first = first / 2;
            last = last / 2;
            level -= 1;

            if (!GetNode(level, first * 2)) {
                first++;
            }
            if (!GetNode(level, last * 2 + 1)) {
                last--;
            }
        }
    }

};

// leetcode 446. Arithmetic Slices II - Subsequence
// Given an integer array nums, return the number of all the arithmetic subsequences of nums.
// A sequence of numbers is called arithmetic if it consists of at least three elements and if the difference between any two consecutive elements is the same.
// For example, [1, 3, 5, 7, 9], [7, 7, 7, 7], and [3, -1, -5, -9] are arithmetic sequences.
// For example, [1, 1, 2, 5, 7] is not an arithmetic sequence.
// A subsequence of an array is a sequence that can be formed by removing some elements (possibly none) of the array.
// For example, [2,5,10] is a subsequence of [1,2,1,2,4,1,5,10].
// The test cases are generated so that the answer fits in 32-bit integer.

// Example 1:

// Input: nums = [2,4,6,8,10]
// Output: 7
// Explanation: All arithmetic subsequence slices are:
// [2,4,6]
// [4,6,8]
// [6,8,10]
// [2,4,6,8]
// [4,6,8,10]
// [2,4,6,8,10]
// [2,6,10]

   int numberOfArithmeticSlices(vector<int>& A) {
        if (A.size() < 3)
            return 0;

        vector<unordered_map<long, int>> m(A.size());
        int cnt = 0;
        for (int i = 0; i < A.size(); ++i)
        {
            for (int j = i + 1; j < A.size(); ++j)
            {
                long diff = A[j];
                diff -= A[i];
                m[j][diff]++;

                if (m[i].count(diff)) {
                    cnt += m[i][diff];
                    m[j][diff] += m[i][diff];
                }
            }
        }
        return cnt;
    }

/**
// Ghost Automotive 2022 coding interview.
// register callback

// void register(void(*callback)(void));
// void fire();

// void lock()
// void unlock()

typedef struct callbacks {
  void* ptr;
  struct callbacks* next;
}  callbacks;

int cas(void **ptr, void *expected, void *new_value) {
        int ret = (*ptr == expected);
        if (ret) *ptr = new_value;
        return ret;
}


volatile callbacks* head = NULL;

// keep a list of callbacks
void register(void(*callback)(void)) {
    callbacks* tmp = malloc(sizeof(callbacks));
    tmp->ptr = callback;
    tmp->next = head;
    
    while (!cas(&(head), tmp->next, tmp)) {
       tmp->next = head;
    }
}

// iterate the list to fire each callbakcs 
void fire() {
  callbacks* it = head;
  while (!it) {
    it->ptr();
    it = it->next;
  }
}
**/


// leetcode 209 minimum size subarray sum
// Given an array of positive integers nums and a positive integer target, return the minimal length of a contiguous subarray [numsl, numsl+1, ..., numsr-1, numsr] of which the sum is greater than or equal to target. If there is no such subarray, return 0 instead.
// Example 1:
// Input: target = 7, nums = [2,3,1,2,4,3]
// Output: 2
// Explanation: The subarray [4,3] has the minimal length under the problem constraint.
#ifdef java
class Solution {
  // O(nlog(n))
  public int minSubArrayLen1(int s, int[] nums) {
      int[] v = new int[nums.length + 1];
      v[0] = 0;
      for (int i = 1; i < v.length; ++i)
      {
          v[i] = v[i - 1] + nums[i - 1];
      }
      
      int r = 0;
      for (int i = 1; i < v.length; ++i)
      {
          int x = lowerBound(s + v[i - 1], v, i);
          //System.out.println("x is " + x  + " and i is " + i);

          if (x < v.length)
          {
              if (r == 0)
                  r = x - i + 1;
              else
                  r = Math.min(r, x - i + 1);
              
          }
      }
       
      return r;
  }
  
  int lowerBound(int s, int[] v, int a)
  {
      int e = v.length - 1;
      while (a <= e)
      {
          int m = (a + e) / 2;
          
          if (s > v[m])
          {
              a = m + 1;
          }
          else
          {
              e = m - 1;
          }
      }
      return a;
  }
  
  // O(n)
  public int minSubArrayLen(int s, int[] nums) {
      int beg = -1, end = -1;
      int left = 0, right = 0;
      int sum = 0;
      int r = 0;
      
      while (right < nums.length)
      {
          sum += nums[right];

          // System.out.println("sum is " + sum);
          
          while (sum >= s)
          {
              if ((beg == -1 && end == -1) ||
                  (end - beg > right - left))
              {
                  r = right - left + 1;
                  end = right;
                  beg = left;
              }
              
              sum -= nums[left];
              left += 1;
          }
          
          right += 1;
      }
      
      return r;
      
  }
}
#endif

// leetcode 207. Course Schedule
// There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]
// Given the total number of courses and a list of prerequisite pairs, is it possible for you to finish all courses?
// Example 1:
// Input: numCourses = 2, prerequisites = [[1,0]]
// Output: true
// Explanation: There are a total of 2 courses to take. To take course 1 you should have finished course 0. So it is possible.
// Example 2:
// Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
// Output: false
// Explanation: There are a total of 2 courses to take. To take course 1 you should have finished course 0, and to take course 0 you should also have finished course


// * BFS solution: Initialize a queue with all courses that have an in-degree of 0 (no prerequisites).
//  While the queue is not empty:
//      Dequeue a course.
//      For each of its direct dependent courses (neighbors), decrement their in-degree.
//      If a dependent course's in-degree becomes 0, enqueue it.
//  After the process, if the total number of courses processed (dequeued) equals numCourses, then a topological sort was possible, and thus no cycle exists. Otherwise, a cycle exists.

// * DFS solution: use visited array to detect cycle
class CourseScheduleUsingDFS {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        unordered_set<int> s;
        unordered_map<int, vector<int>> m;

        for (int i = 0; i < numCourses; ++i) {
            s.insert(i);
        }

        for (auto& p : prerequisites) {
            m[p[1]].push_back(p[0]);
            s.erase(p[0]);
        }

        vector<int> visit(numCourses, 0);
        for (auto i : s) {
            if (!search(m, i, visit)) {
                return false;
            }
        }

        for (auto v : visit) {
            if (v != 2) {
                return false;
            }
        }

        return true;
    }
    
    bool search(unordered_map<int, vector<int>>& m, int i, vector<int>& visit) {
        // cycle found
        if (visit[i] == 1) {
            return false;
        }

        visit[i] = 1;
        for (auto n : m[i]) {
            if (visit[n] != 2) {
                if (!search(m, n, visit)) {
                    return false;
                }
            }
        }

        visit[i] = 2;
        return true;
    }

};

// snap
// 1) leetcode 205. Isomorphic Strings
// 2) read line (i.e., "this is a test of the emergency broadcast system this is only a test") and print the number of words in the line. 
//     more frequent words should be printed first, and if two words have the same frequency, then they should be sorted by their length.
//     you should ask: order of print, do we to consider case, and what is the max length of a word.
//     Refer to leetcode 692. Top K Frequent Words.
//     Also consider Sorted Set in Redis.
// 3) in a string, () and words exist. words or ( or ) inside a () should be indented by 2 spaces. 
//   (hi) ->
//   (
//     hi
//   )
// lesson learned: ask cleaning questions. do not just jump into coding.

// snap refactoring
// question about type erasure. snap uses third party library for filters. They want to use it seemingly in a type safe way.
// there were two filters provided. Both filters return slightly different result, but basically image vector.
// I suggested to use a common interface for filters and images, and wrapper for the filters, basically a type erasure. 
// For the images I also suggested to use a common interface, and then use a wrapper for the images.



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
  //test_lfu_cache();

  vector<int> a = {1};

  auto it = lower_bound(a.begin(), a.end(), 2);
  auto jt = lower_bound(a.begin(), a.end(), 0);

  cout << distance(a.begin(), it) << " <<  " << distance(a.begin(), jt) << endl;
  cout << (a.begin() == it) << " <<  " << (a.begin() == jt) << endl;
  if (int x = a[0]; x == 1) {
    cout << "x is " << x << endl;
  }

  vector<pair<int, int>> p = {{1, 2}, {1, 3}, {1,1}, {2, 1}, {2, 4}, {2, 2}};
  sort(p.begin(), p.end());

  for (auto& x : p) {
    cout << x.first << " " << x.second << endl;
  }


test_merge_linked_list_unique();
test_reverse_word();
}

#include <assert.h>
#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <memory>

using namespace std;

template<class T>
class graph //jj
{
private:
    map<T, int> r;
    map<T, list<pair<T, int> > > node;
    // unordered_map is faster.
    unordered_map<T, bool> resolved;
    map<T, int> visited;
    map<T, vector<pair<T, int>> > parents;

public:
    typedef typename list<pair<T, int> >::iterator iter;

    graph()
    {
    }
    void push(T from, T to, int arg)
    {
        r[from] = r[to] = 100000;
        node[from].push_back(pair<T, int>(to, arg)); // pair(to, arg) does not work as pair is template type. We have to use template type to create
        // an instance of it.
    }

    list<pair<T, int> >
    adj(T from)
    {
        return node[from];
    }

    map<T, int>
    dijkstra(T from) //jj
    {
        // initial distance
        list<pair<T, int> > adjlist = adj(from);
        for (iter it = adjlist.begin();
             it != adjlist.end(); ++it) {
            r[it->first] = it->second;
        }

        set<T> s;
        set<T> v;
        s.insert(from);
        for (typename map<T, int>::iterator it = r.begin();
             it != r.end();
             ++it)
            if (it->first != from)
                v.insert(it->first);
        // done initialiation. node 0 is not added as it is just for easy of use.
        while (!v.empty()) {

            T m = from; //r[from]  has 100000 which means max
            for (typename set<T>::iterator i = v.begin(); i != v.end(); ++i) {
                if (r[*i] < r[m])
                    m = *i;
            } // how can we reduce this? priority queue?
            // but as r[] is changed at the end, heap could not be just
            // used. Do we have a better priority queue for this?
            // Or just checking with all is better?

            cout << " process node "  << m << endl;

            s.insert(m);
            v.erase(m);

            list<pair<T, int> > adj_m = adj(m);
            for(iter it = adj_m.begin();
                    it != adj_m.end(); ++it) {

                    r[it->first] = min(r[it->first], r[m] + it->second);
            }

        }
        return r;
    }

  void sort(T t) //jj
    {
        resolved[t] = true; // we now can work with cycle.

        for (typename list<pair<T, int> >::iterator it = node[t].begin();
             it != node[t].end();
             ++it)
          {
            if (!resolved[it->first])
              sort(it->first);
          }
        // actually visited can be here if there is no cycle
        // resolved[t] = true;
        cout << t << endl;
    }

  void sortFindCycle(T t) //jj
    {
        visited[t]++;
        if (visited[t] > 1)
        {
            cout << "cycle found" << endl;
            // Head up!!!
            // this only prints visited node sorted by map.
            // Acutally what I need is print by visited order.
            // So, probably we need a map that just iterated as a list,
            // and also privide fast access to element
            for (typename map<T, int>::iterator it = visited.begin();
                 it != visited.end();
                 ++it)
            {
                cout << it->first << " ";
            }

            cout << t << endl;
            visited[t]--;
            return;
        }

        if (!node[t].empty())
        {
            for (typename list<pair<T, int> >::iterator it = node[t].begin();
                 it != node[t].end();
                 ++it)
            {
                if (!resolved[it->first])
                    sortFindCycle(it->first);
            }
        }

        cout << t << endl;
        resolved[t] = true;
        visited[t]--;
    }

  void sortBfs(T t) //jj
    {
        resolved[t] = true; // we now can work with cycle.
        list<T> vt;
        vt.push_back(t);

        while (!vt.empty())
        {
            T e = vt.front();
            vt.pop_front();
            // actually visited can be here if there is no cycle
            // resolved[t] = true;
            cout << e << endl;
            for (typename list<pair<T, int> >::iterator it = node[e].begin();
                 it != node[e].end();
                 ++it)
            {
                if (!resolved[it->first])
                {
                    resolved[it->first] = true;
                    vt.push_back(it->first);
                }
            }
        }
    }

    void findParent(T t)
    {
        resolved[t] = true; // we now can work with cycle.
        list<T> vt;
        vt.push_back(t);

        while (!vt.empty())
        {
            T e = vt.front();
            vt.pop_front();
            // actually visited can be here if there is no cycle
            // resolved[t] = true;
            // cout << e << endl;
            for (typename list<pair<T, int> >::iterator it = node[e].begin();
                 it != node[e].end();
                 ++it)
            {
                if (!resolved[it->first])
                {
                    resolved[it->first] = true;
                    vt.push_back(it->first);
                }
                parents[it->first].push_back(pair<T, int>(e, it->second));
            }
        }
    }

    void printParent()
    {

        for (auto i : parents)
        {
            cout << "node is " << i.first << " and parent is ";
            for (auto e: i.second)
            {
                cout << e.first << " ";
            }
            cout << endl;
        }
    }

  int findMaxFlow(T s, T d) //jj
    {
        // actually this check is useless.
        // if (parents.find(d) == parents.end())
        //     return 0;

        int tmax = -1;
        for (auto e : parents[d])
        {
            int r;
            if (e.first == s)
                r = e.second;
            else
                r = min(e.second, findMaxFlow(s, e.first));

            if (tmax < r)
                tmax = r;
        }

        return tmax;
    }

    int findMaxFlow(T s, T d, list<T>& l)
    {
        // actually this check is useless.
        // if (parents.find(d) == parents.end())
        //     return 0;
        // if (s == d)
        //     return 0;

        visited[d]++;
        int tmax = -1;
        list<T> tlmax;
        for (auto e : parents[d])
        {
            int r;
            list<T> tl;

            tl.push_back(e.first);
            if (e.first == s)
            {
                r = e.second;
            }
            else
            {
                // cycle should not allowd here
                if (visited[e.first] == 0)
                {
                    list<T> tt;
                    r = min(e.second, findMaxFlow(s, e.first, tt));
                    copy(tt.begin(), tt.end(), back_inserter(tl));
                }
            }

            if (tmax < r)
            {
                tmax = r;
                tlmax = tl;
            }

        }

        visited[d]--;
        copy(tlmax.begin(), tlmax.end(), back_inserter(l));
        return tmax;
    }

    void update(T s, T t, list<T> l, int d)
    {
        for (auto e : l)
        {
            for (auto it = parents[t].begin(); it != parents[t].end(); ++it)
            {
                if (it->first == e)
                {
                    it->second -= d;
                    t = e;
                    break;
                }
            }
        }

        for (auto it = parents[t].begin(); it != parents[t].end(); ++it)
        {
            if (it->first == s)
            {
                it->second -= d;
                break;
            }
        }
    }

};




int t1()
{
    // test: find is by-value
    list<pair<int, int> > l;

    l.push_back(pair<int, int>(1, 1));
    l.push_back(pair<int, int>(1, 2));
    l.push_back(pair<int, int>(1, 3));
    l.push_back(pair<int, int>(1, 4));

    typedef list<pair<int, int> >::iterator iter;

    iter it = find(l.begin(), l.end(), pair<int, int>(1,3));

    if (it != l.end())
        cout << it->second << endl;

}

int t2()
{
    graph<int>  g;
    g.push(1, 2, 10);
    g.push(1, 4, 30);
    g.push(1, 5, 100);
    g.push(2, 3, 50);
    g.push(3, 5, 10);
    g.push(4, 3, 20);
    g.push(4, 5, 60);

    map<int, int> r = g.dijkstra(1);

    for (map<int, int>::iterator it = r.begin();
         it != r.end();
         ++it)
    {
        cout << it->first << " : " << it->second << endl;
    }
}

// async access to the graph (tree) structure.
#include <pthread.h>
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static int numTerm;

struct thread_bfs
{
    list<int> *pfnode;
    graph<int> *pg;
    int node;
    map<int,int> *pmap;

};

static void *
threadFunc1(void * args)
{
    int err;

    struct thread_bfs *thr = (struct thread_bfs *)args;
    list<pair<int, int> > adjlist = (*(thr->pg)).adj(thr->node);

    err = pthread_mutex_lock(&mtx);
    if (err)
        cout << "error in mutex_lock" << endl;

    for (list<pair<int, int> >::iterator it = adjlist.begin();
         it != adjlist.end(); ++it) {

        if ((*(thr->pmap))[it->first] == 0) {
            ++(*(thr->pmap))[it->first];
            (*(thr->pfnode)).push_back(it->first);
            cout << "added node " << it->first << endl;

        }
    }

    numTerm++;

    err = pthread_mutex_unlock(&mtx);
    if (err)
        cout << "error in mutex_unlock" << endl;

    err = pthread_cond_signal(&cond);
    if (err)
        cout << "error in cond_signalx" << endl;
}


int t_thread_bfs_1()
{
    // setup graph
    static list<int> fnode;
    static graph<int> g;
    static map<int, int> xmap;
    struct thread_bfs *thr_bfs;

    numTerm = 0;
    int numCre = 0;

    g.push(1, 2, 0);
    g.push(1, 4, 0);
    g.push(1, 5, 0);
    g.push(2, 3, 0);
    g.push(3, 5, 0);
    g.push(4, 3, 0);
    g.push(4, 5, 0);

    pthread_t thr;
    // main thread is waiting for the list to be updated, and
    fnode.push_back(1);
    xmap[1]++; // mark visited. Otherwise you might end up with revisit the node

    bool done = false;

    while (!done) {

        int err = pthread_mutex_lock(&mtx);
        if (err)
            cout << " error in mutex_lock " << endl;

        // if work to do in the Q then create a thread do a task
        // Or, I can create as much tasks as possible by taking all the tasks in the Q
        if (!fnode.empty()) {
            int n = fnode.front();
            fnode.pop_front();
            cout << endl << "visited " << n << endl;
            // setup data for the worker thread to access
            thr_bfs = new struct thread_bfs;
            thr_bfs->pfnode = &fnode;
            thr_bfs->pg = &g;
            thr_bfs->pmap = &xmap;
            thr_bfs->node = n;
            int err = pthread_create(&thr, NULL, threadFunc1, thr_bfs); // at the moment, I am not worry about joining the created thread.
            if (err)
                cout << " error in creating thread " << endl;
            numCre++; // num created threads

        } else if (numCre > numTerm) {
            // we do not have anything in the Q but worker threads are pending
            // wait for signal from the thread to avoid busy waiting
            cout << endl << "wait for new Data" << endl;

            err = pthread_cond_wait(&cond, &mtx);
            if (err)
                cout << " error in cond_wait " << endl;

        } else if (numCre == numTerm) {
            done = true; // if all threads are terminated and nothing to do more.
            cout << endl << "processed all" << endl;
        } else {
            cout << "error" << endl;
        }

        err = pthread_mutex_unlock(&mtx);
        if (err)
            cout << " error in mutex_unlock " << endl;

    }

}


int t3()
{
    graph<int>  g;
    g.push(1, 2, 10);
    g.push(1, 4, 30);
    g.push(1, 5, 100);
    g.push(2, 3, 50);
    g.push(3, 5, 10);
    g.push(4, 3, 20);
    g.push(4, 5, 60);
    g.push(5, 2, 30); // add cycle

    g.sort(1);
}

// how can we find cycle?
int t4()
{
    graph<int>  g;
    g.push(1, 2, 10);
    g.push(1, 4, 30);
    g.push(1, 5, 100);
    g.push(2, 3, 50);
    g.push(3, 5, 10);
    g.push(4, 3, 20);
    g.push(4, 5, 60);
    g.push(5, 2, 30); // add cycle

    g.sortFindCycle(1);
}

int t3_1()
{
    graph<int>  g;
    g.push(1, 2, 10);
    g.push(1, 4, 30);
    g.push(1, 5, 100);
    g.push(2, 3, 50);
    g.push(3, 5, 10);
    g.push(4, 3, 20);
    g.push(4, 5, 60);
    g.push(5, 2, 30); // add cycle

    g.sortBfs(1);
}

class trie { //jj
private:
    class node {
    public:
        node():complete{false} {}
        unordered_map<char, shared_ptr<node> > ms;
        bool complete;
        ~node() { cout << "deleted" << endl; }
    };
    shared_ptr<node> root;

public:
    trie(): root{new node()} {}
    void add(string s);
    void remove(string s);
    bool find(string s);
    vector<string> fuzzy_find(string s);
    void visit_all(vector<string> &vs, vector<char> &vc, shared_ptr<node>& n);

};


void trie::add(string s)
{
    int i = 0;
    int len = s.size();
    //
    shared_ptr<node> n = root;
    while(i < len)
    {
        auto it = n->ms.find(s[i]);
        if (it == n->ms.end())
            break;
        n = it->second;
        ++i;
    }

    //
    while(i < len)
    {
        shared_ptr<node> temp{new node()};
        n->ms[s[i]] = temp;
        n = temp;
        ++i;
    }

    n->complete = true;
}

void trie::remove(string s)
{
    int i = 0;
    int len = s.size();

    //
    shared_ptr<node> n = root;
    shared_ptr<node> prev_n = root;
    char prev_ch;
    bool begin = false;
    while(i < len)
    {
        auto it = n->ms.find(s[i]);
        if (it == n->ms.end())
            return;

        if (it->second->ms.size() <= 1)
        {
            if (!begin)
            {
                prev_ch = s[i];
                prev_n = n;
                begin = true;
            }
        }
        else
        {
            begin = false;
            prev_n = n;
            prev_ch = s[i];
        }

        n = it->second;
        ++i;
    }

    if (n->ms.empty())
    {
        auto it = prev_n->ms.find(prev_ch);
        prev_n->ms.erase(it);
    }
    else
    {
        n->complete = false;
    }
}

bool trie::find(string s)
{
    int len = s.size();
    int i = 0;

    shared_ptr<node> n = root;
    while (i < len)
    {
        auto it = n->ms.find(s[i]);
        if (it == n->ms.end())
            return false;
        n = it->second;
        ++i;
    }

    return n->complete;
}


void trie::visit_all(vector<string> &vs, vector<char> &vc, shared_ptr<node>& n)
{
    if (n->complete)
        vs.push_back(string(vc.begin(), vc.end()));

    for (auto it = n->ms.begin(); it != n->ms.end(); ++it)
    {
        vc.push_back(it->first);
        visit_all(vs, vc, it->second);
        vc.pop_back();
    }
}

vector<string> trie::fuzzy_find(string s)
{
    int len = s.size();
    int i = 0;

    vector<char> vc;
    vector<string> vs;
    shared_ptr<node> n = root;
    while (i < len)
    {
        auto it = n->ms.find(s[i]);
        if (it == n->ms.end())
            return vs;
        vc.push_back(s[i]);
        n = it->second;
        ++i;
    }

    visit_all(vs, vc, n);
    return vs;
}


void t5()
{
    trie t;
    string s;

    t.add("this");
    t.add("that");
    t.add("they");
    t.add("the");

    assert(true == t.find("they"));
    assert(true == t.find("this"));
    assert(true == t.find("that"));
    assert(true == t.find("the"));

    t.remove("the");
    assert(false == t.find("the"));
    cout << "delete the" << endl;
    getline(cin, s);

    t.remove("they");
    assert(false == t.find("they"));
    cout << "delete they" << endl;
    getline(cin, s);

    t.remove("this");
    assert(false == t.find("this"));
    cout << "delete this" << endl;
    getline(cin, s);

    t.remove("that");
    assert(false == t.find("that"));
    cout << "delete that" << endl;
    getline(cin, s);
}


void t6()
{
    trie t;
    string s;

    t.add("this");
    t.add("that");
    t.add("they");
    t.add("the");
    auto vs = t.fuzzy_find("the");
    for (auto it = vs.begin(); it != vs.end(); ++it)
        cout << *it << endl;
}


// given a weighted grath, find a max flow path from source to dest
void t7()
{
    graph<int>  g;
    g.push(1, 2, 25);
    g.push(1, 4, 30);
    // g.push(1, 5, 100);
    g.push(2, 3, 50);
    g.push(3, 5, 10);
    g.push(4, 3, 20);
    g.push(4, 5, 60);
    // g.push(5, 2, 30); // add cycle

    g.findParent(1);
    cout << g.findMaxFlow(1, 5) << endl;
    cout << g.findMaxFlow(1, 3) << endl;
}


void t7_1()
{
    graph<int>  g;
    g.push(1, 2, 25);
    g.push(1, 4, 30);
    // g.push(1, 5, 100);
    g.push(2, 3, 50);
    g.push(3, 5, 10);
    g.push(4, 3, 20);
    g.push(4, 5, 60);
    // g.push(5, 2, 30); // add cycle

    g.findParent(1);
    list<int> tl;
    cout << g.findMaxFlow(1, 5, tl) << endl;

    for (auto e : tl)
        cout << e << " ";

    cout << endl;
    tl.clear();
    cout << g.findMaxFlow(1, 3, tl) << endl;

    for (auto e : tl)
        cout << e << " ";

    cout << endl;
}

void t7_2()
{
    graph<int>  g;
    g.push(1, 2, 16);
    g.push(1, 3, 13);
    g.push(2, 3, 10); // add cycle
    g.push(2, 4, 12);
    g.push(3, 2, 4);
    g.push(3, 5, 14);
    g.push(4, 3, 9); // add cycle
    g.push(4, 6, 20);
    g.push(5, 4, 7);
    g.push(5, 6, 4);
    g.push(5, 2, 30); // add cycle

    g.findParent(1);
    cout << "parent found" << endl;
    // g.printParent();
    list<int> tl;
    int tmax = g.findMaxFlow(1, 6, tl);;
    while (tmax != 0)
    {
        cout << tmax << endl;

        for (auto e : tl)
            cout << e << " ";

        cout << endl;
        g.update(1, 6, tl, tmax);
        tl.clear();

        tmax = g.findMaxFlow(1, 6, tl);
    }
}

void t7_3()
{
    graph<int>  g;
    g.push(1, 2, 40);
    g.push(1, 4, 20);
    g.push(2, 4, 20);
    g.push(2, 3, 30);
    g.push(3, 4, 10);

    g.findParent(1);
    cout << "parent found" << endl;
    // g.printParent();
    list<int> tl;
    int tmax = g.findMaxFlow(1, 4, tl);;
    while (tmax != 0)
    {
        cout << tmax << endl;

        for (auto e : tl)
            cout << e << " ";

        cout << endl;
        g.update(1, 4, tl, tmax);
        tl.clear();

        tmax = g.findMaxFlow(1, 4, tl);
    }
}

#if 0
 // union find //jj
int Find(int x) {
     while(x != L[x]) x = L[x];
     return x;
 }
void Union(int x, int y) {
    L[Find(x)] = Find(y);
}


// path compression
int Find(int x) {
    if(x == L[x]) return x;
    int root = Find(L[x]);
    L[x] = root;
    return root;
}
int Find(int x) {
    return x == L[x] ? x : L[x] = Find(L[x]);
}
#endif

// how can we handle graph with extremely large nodes?
// which data structure or algorithm to use?

// suffix trie
//http://www.geeksforgeeks.org/pattern-searching-set-8-suffix-tree-introduction/


struct node {
    node() : a(0), b(0), left(nullptr), right(nullptr) {}
    int a;
    int b;
    node* left;
    node* right;
};

// find whether there is a depth n which has both value a and b.
bool bfs_pair(node* n, int a, int b) //jj
{
    if (!n) return false;

    // we don't need this map as this is binary tree.
    map<node*, bool> visited;
    list<node*> nl;
    visited[n] = true;
    nl.push_back(n);
    node r; // end mark
    nl.push_back(&r);

    set<int> sr;
    set<int> sl;
    int depth = 0;

    while (!nl.empty())
    {
        node* t = nl.front();
        nl.pop_front();
        if (t == &r) {
            if (nl.empty())
                return false;
            else {
                depth++;
                nl.push_back(t);
            }
        }
        else {
            if (t->a == a)
                sl.insert(depth);
            if (t->b == b)
                sr.insert(depth);

            vector<int> va;
            set_intersection(sl.begin(), sl.end(), sr.begin(), sr.end(),
                             back_inserter(va));
            if (!va.empty())
            {
                cout << "found" << endl;
                return true;
            }

            if (t->left && (visited[t->left] == false))
            {
                visited[t->left] = true;
                nl.push_back(t->left);
            }
            if (t->right && (visited[t->right] == false))
            {
                visited[t->right] = true;
                nl.push_back(t->right);
            }
        }
    }

    return false;
}

void test_bfs_pair()
{
    node a;
    node b;
    node c;
    node d;
    node e;

    a.left = &b; a.a = 1; a.b = 2; a.right = &c;
    b.left = &d; b.a = 3; b.b = 4; b.right = &e;
    c.a = 5;c.b = 6;
    d.a = 7;d.b = 8;
    e.a = 9;e.b = 10;

    cout << bfs_pair(&a, 1, 2) << endl;
    cout << bfs_pair(&a, 3, 6) << endl;
    cout << bfs_pair(&a, 2, 9) << endl;
    cout << bfs_pair(&a, 12, 2) << endl;
}

/*
  In Docker, building an image has dependencies. An image can only be built once its dependency is built (If the dependency is from outside, then the image can be built immediately).

  Sometimes, engineers make mistakes by forming a cycle dependency of local images. In this case, ignore the cycle and all the images depending on this cycle.

  Input is vector of pair of images (image, its dependency). 
  Output the order of images to be built in order. 

  ##Example: 
  ``` 
  Example 1: 
  {{"master", "ubuntu"}, {"numpy", "master"}, {"tensorflow", "numpy"}} 
  Output: master, numpy, tensorflow 

  Example 2: 
  {{"python", "numpy"}, {"numpy", "python"}, {"tensorflow", "ubuntu"}} 
  Output: tensorflow 

  Example 3: 
  {{"b", "c"}, {"c", "d"}, {"a", "b"}, {"d", "e"}, {"e","c"}, {"f", "g"}} 
  Ouput: f
 */

void test_find_dependency() //jj
{
    // sol: 1. get dependency of each node, and get a set of root
    //      2. from node in root set, find a set of nodes which forms cycle
    //      3. bfs from node in root set, excluding nodes in cycle set.

}

int main()
{
    test_bfs_pair();
}

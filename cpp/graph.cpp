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
class graph 
{

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
    dijkstra(T from) 
    {
        auto c1 = [&](T a, T b){ return r[a] > r[b];};
        // initial distance
        list<pair<T, int> > adjlist = adj(from);
        for (iter it = adjlist.begin();
             it != adjlist.end(); ++it) {
            r[it->first] = it->second;
        }

        list<T> s;
        vector<T> v;
        s.push_back(from);        
        for (typename map<T, int>::iterator it = r.begin();
             it != r.end();
             ++it)
            if (it->first != from)
                v.push_back(it->first);
        // done initialiation. node 0 is not added as it is just for easy of use.

        make_heap(v.begin(), v.end(), c1);
        while (!v.empty()) {

            T m = v.front();
            cout << " process node "  << m << endl;

            s.push_back(m);
            pop_heap(v.begin(), v.end(), c1);
            v.pop_back();

            list<pair<T, int> > adj_m = adj(m);
            for(iter it = adj_m.begin();
                    it != adj_m.end(); ++it) {

                    r[it->first] = min(r[it->first], r[m] + it->second);
            }
            
        }
        return r;
    }

    void sort(T t)
    {
        resolved[t] = true; // we now can work with cycle.

        if (!node[t].empty())
        {
            for (typename list<pair<T, int> >::iterator it = node[t].begin();
                 it != node[t].end();
                 ++it)
            {
                if (!resolved[it->first])
                    sort(it->first);
            }
        }
        // actually visited can be here if there is no cycle
        // resolved[t] = true;
        cout << t << endl;
    }

    void sortFindCycle(T t)
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
    }

    void sortBfs(T t)
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

    int findMaxFlow(T s, T d)
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

        int tmax = -1;
        list<T> tlmax;
        for (auto e : parents[d])
        {
            int r;
            list<T> tl;
                
            if (e.first == s)
            {
                r = e.second;
                tl.push_back(e.first);
            }
            else 
            {
                list<T> tt;
                int t = findMaxFlow(s, e.first, tt);
                tl.push_back(e.first);
                if (e.second < t)
                {
                    r = e.second;
                }
                else
                {
                    r = t;
                    copy(tt.begin(), tt.end(), back_inserter(tl));
                }
            }

            if (tmax < r)
            {
                tmax = r;
                tlmax = tl;
            }

        }

        copy(tlmax.begin(), tlmax.end(), back_inserter(l));
        return tmax;
    }

    private:
    map<T, int> r;
    map<T, list<pair<T, int> > > node;
    // unordered_map is faster.
    unordered_map<T, bool> resolved;
    map<T, int> visited;
    map<T, vector<pair<T, int>> > parents;
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

class trie {
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

#if 0
 // union find
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

int main()
{
    t2();
}

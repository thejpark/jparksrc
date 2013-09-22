#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;


// a = a - b
void list_subtract(list<int> a, list<int> b)
{
    typedef list<int>::iterator iter;

    iter it = a.begin();
    
    while (it != a.end()) {
        if (find(b.begin(), b.end(), *it) != b.end())
            it = a.erase(it);
        else
            ++it;
    }
}


class graph 
{

public:
    graph(int n) : node(n + 1) // node name start from 1
    {
    }
    
    void push(int from, int to, int arg)
    {
        node[from].push_back(pair<int, int>(to, arg)); // pair(to, arg) does not work as pair is template type. We have to use template type to create
        // an instance of it.
    }

    list<pair<int, int> >
    adj(int from) 
    {
        return node[from];
    }

    vector<int>
    dijkstra(int from) 
    {
        // initial distance
        vector<int> r(node.size(), 100000);
        list<pair<int, int> > adjlist = adj(from);
        for (list<pair<int, int> >::iterator it = adjlist.begin();
             it != adjlist.end(); ++it) {
            r[it->first] = it->second;
        }

        list<int> s, v;
        s.push_back(from);        
        for (int i = 1; i < node.size(); i++)
            if (i != from)
                v.push_back(i);
        // done initialiation. node 0 is not added as it is just for easy of use.

        while (!v.empty()) {

            int m = 0; //r[0]  has 100000 which means max
            for (list<int>::iterator i = v.begin(); i != v.end(); ++i) {
                if (r[*i] < r[m])
                    m = *i;
            } // how can we reduce this? priority queue? 

            cout << " process node "  << m << endl;

            s.push_back(m);
            v.erase(remove(v.begin(), v.end(), m), v.end());

            list<pair<int, int> > adj_m = adj(m);
            for(list<pair<int, int> >::iterator it = adj_m.begin();
                    it != adj_m.end(); ++it) {

                    r[it->first] = min(r[it->first], r[m] + it->second);
            }
            
        }
        return r;
    }

private:
    vector<list<pair<int, int> > > node;
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
    graph g(5);
    g.push(1, 2, 10);
    g.push(1, 4, 30);
    g.push(1, 5, 100);
    g.push(2, 3, 50);
    g.push(3, 5, 10);
    g.push(4, 3, 20);
    g.push(4, 5, 60);

    vector<int> r = g.dijkstra(1);
        
    for (int i = 1; i < r.size(); ++i)
        cout << ' ' << r[i];

    cout << endl;
}

// async access to the graph (tree) structure.
#include <pthread.h>
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static int numTerm;

struct thread_bfs 
{
    list<int> *pfnode;
    graph *pg;
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
    static graph g(5);
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


int main()
{

    t_thread_bfs_1();

}



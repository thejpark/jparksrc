// integer set with adding and deleting in a constant time
// can we use map only? ( that means, add will take more than O(1).

#include <map>
#include <iostream>
#include <stdexcept>

using namespace std;
class mySet {

public:
    mySet() : head(NULL), tail(NULL), count(0)
    {
    }
    bool add(int x);
    bool remove(int x);
    bool contains(int  x);
    int size();
    void removeAll();

private:
    class node {
    public:
        node(int x) : data(x), prev(NULL), next(NULL) {}
        int data;
        node* prev;
        node* next;
    };
    node* head;
    node* tail;
    map<int, node*> mc;
    int count;
};

bool mySet::add(int x)
{
    if (mc.find(x) != mc.end())
        return false;

    node* n = new node(x);
    if (!n)
        throw domain_error("student has done no homework");

    if (head == NULL)
        head = tail = n; 
    else 
    {
        tail->next = n;
        n->prev = tail;
        tail = n;
    }

    mc[x] = n;
    count++;
    return true;
}

bool mySet::remove(int x)
{
    auto it = mc.find(x);
    if (it == mc.end())
        return false;

    node* n = it->second;
    mc.erase(it);
    count--;

    if (n == head && n == tail)
    {
        head = tail = NULL;
    }
    else if (n == head)
    {
        head = head->next;
        head->prev = NULL;
    }
    else if (n == tail)
    {
        tail = tail->prev;
        tail->next = NULL;
    }
    else
    {
        n->prev->next = n->next;
        n->next->prev = n->prev;
    }

    n->next = NULL;
    n->prev = NULL;
    delete n;
    return true;
}


void mySet::removeAll()
{
    while (head)
    {
        node* h = head;
        head = head->next;
        h->next = h->prev = NULL;
        delete h;
    }
    
    head = tail = NULL;
    count = 0;
    mc.clear();
    // mc.erase(mc.begin(), mc.end());   
}


bool mySet::contains(int x)
{
    if(mc.find(x) == mc.end())
        return false;
    return true;
}


int mySet::size()
{
    return count;
}


int main(int argc, char * argv[])
{
    mySet ms;
    ms.add(1);
    ms.add(2);
    cout << ms.contains(1) << " " << ms.contains(2) << " " << ms.size() << endl;
    cout << ms.remove(2) << endl;
    cout << ms.remove(1) << endl;
    cout << ms.size() << endl;

    ms.add(1);
    ms.add(2);
    ms.add(3);
    cout << ms.contains(1) << " " << ms.contains(2) << " " << ms.contains(3) <<  " " << ms.size() << endl;
    cout << ms.remove(3) << endl;
    cout << ms.add(1) << endl;
    cout << ms.size() << endl;
    cout << ms.contains(1) << " " << ms.contains(2) << " " << ms.contains(3) <<  " " << ms.size() << endl;

    ms.removeAll();
    cout << ms.contains(1) << " " << ms.contains(2) << " " << ms.contains(3) <<  " " << ms.size() << endl;

    cout << ms.remove(3) << endl;
    cout << ms.add(1) << endl;
    cout << ms.size() << endl;
    cout << ms.contains(1) << " " << ms.contains(2) << " " << ms.contains(3) <<  " " << ms.size() << endl;

 }

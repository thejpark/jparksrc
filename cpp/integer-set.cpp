// integer set with adding and deleting in a constant time
// can we use map only? ( that means, add will take more than O(1).

#include <map>

class mySet {

public:
    mySet() : head(NULL), tail(NULL)
    {
    }
    bool add(int x);
    bool remove(int x);
    bool contains(int  x);
    int size();

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
};

bool mySet::add(int x)
{
    if (mc[x])
        return false;

    node n = new node(x);
    if (!n)
        throw domain_error("student has done no homework");

    if (head == NULL)
        head = tail = n; 
    else 
    {
        tail->next = n;
        n->prev = tail;
        tail = n;
        n->next = NULL;
    }

    mc[x] = n;
    count++;
    return true;
}

bool mySet::remove(int x)
{
    node* n = mc[x];
    if (!n)
        return false;

    mc[x] = NULL;
    count--;

    if (n == head && n == tail)
    {
        head = tail = NULL;
        delete n;
    }
    else if (n == head)
    {
        head = head->next;
        head->prev = NULL;
        delete n;
    }
    else if (n == tail)
    {
        tail = tail->prev;
        tail->next = NULL;
        delete n;
    }
    else
    {
        n->prev->next = n->next;
        n->next->prev = n->prev;
        delete n;
    }

    return true;
}

bool mySet::contains(int x)
{
    if (mc[x])
        return true;

    return false;
}


int mySet::size()
{
    return count;
}

// integer set with adding and deleting in a constant time
// can we use map only? ( that means, add will take more than O(1).


import java.util.HashMap;

class mySet {

    class node {
	node(int x) 
	{
	    data = x;
	    prev = next = null;
	}
        int data;
        node prev;
        node next;
    }
    
    public static void main(String[] args)
    {

    }

public:
    mySet()
    {
	head = tail = null;
	count = 0;
    }
    
    boolean add(int x)
    {
	if (mc[x])
	    return false;

	node n = new node(x);
	if (!n)
	   throw domain_error("student has done no homework");

	if (head == null)
	    head = tail = n; 
	else 
	    {
		tail.next = n;
		n.prev = tail;
		tail = n;
	    }

	mc[x] = n;
	count++;
	return true;
    }
 
    boolean remove(int x)
    {
{
    node n = mc[x];
    if (!n)
        return false;

    mc[x] = null;
    count--;

    if (n == head && n == tail)
    {
        head = tail = null;
        delete n;
    }
    else if (n == head)
    {
        head = head.next;
        head.prev = null;
        delete n;
    }
    else if (n == tail)
    {
        tail = tail.prev;
        tail.next = null;
        delete n;
    }
    else
    {
        n.prev.next = n.next;
        n.next.prev = n.prev;
        delete n;
    }

    return true;
}

void removeAll()
{
    while (head)
    {
        node h = head;
        head = head.next;
        mc[h.data] = null;
	h = null;
    }
    head = tail = null;
    count = 0;
}


boolean contains(int x)
{
    if (mc[x])
        return true;

    return false;
}


int size()
{
    return count;
}

    private node head;
    private node tail;
    private HashMap<int, node> mc;
    private int count;
};



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

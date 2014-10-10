// integer set with adding and deleting in a constant time
// can we use map only? ( that means, add will take more than O(1).


import java.util.HashMap;
import java.util.Map;

class mySet {

    class node {
	node(int x) 
	{
	    data = new Integer(x);
	    prev = next = null;
	}
        Integer data;
        node prev;
        node next;
    }

    private node head;
    private node tail;
    private Map<Integer, node> mc;
    private int count;
    
    public static void main(String[] args)
    {
	mySet ms = new mySet();
	ms.add(1);
	ms.add(2);
	System.out.println(ms.contains(1) + " " + ms.contains(2) + " " + ms.size()) ;
	System.out.println(ms.remove(2)); 
	System.out.println(ms.remove(1));
	System.out.println(ms.size());

	ms.add(1);
	ms.add(2);
	ms.add(3);
	System.out.println(ms.contains(1) +  "  " +  ms.contains(2) + "  " + ms.contains(3)  + "  "  + ms.size());
	System.out.println(ms.remove(3) );
	System.out.println(ms.add(1) );
	System.out.println(ms.size() );
	System.out.println(ms.contains(1) + "  " + ms.contains(2) + " " + ms.contains(3)  + "  " + ms.size() );

	ms.removeAll();
	System.out.println(ms.contains(1) + "  " +  ms.contains(2) + "  " + ms.contains(3) + "  " + ms.size() );

	System.out.println(ms.remove(3) );
	System.out.println(ms.add(1) );
	System.out.println(ms.size() );
	System.out.println(ms.contains(1) + "  " + ms.contains(2) + "  " + ms.contains(3)  + "  " + ms.size() );

    }

    mySet()
    {
	mc = new HashMap<Integer, node>();
	head = tail = null;
	count = 0;
    }
    
    boolean add(int i)
    {
	Integer x = new Integer(i);
	node n = mc.get(x);

	if (n != null)
	    return false;

	n = new node(x);

	if (head == null)
	    head = tail = n; 
	else 
	    {
		tail.next = n;
		n.prev = tail;
		tail = n;
	    }

	mc.put(x, n);
	count++;
	return true;
    }
 
    boolean remove(int i)
    {
	Integer x = new Integer(i);
	node n = mc.get(x);

	if (n == null)
	    return false;

	mc.put(x, null);
	count--;

	if (n == head && n == tail)
	{
	    head = tail = null;
	    n = null;
	}
	else if (n == head)
	{
	    head = head.next;
	    head.prev = null;
	    n = null;
	}
	else if (n == tail)
	{
	    tail = tail.prev;
	    tail.next = null;
	    n = null;
	}
	else
	{
	    n.prev.next = n.next;
	    n.next.prev = n.prev;
	    n = null;
	}

	return true;
    }

    void removeAll()
    {
	while (head != null)
	{
	    node h = head;
	    head = head.next;
	    mc.put(h.data, null);
	    h = null;
	}
	head = tail = null;
	count = 0;
    }


    boolean contains(int i)
    {
	Integer x = new Integer(i);
	if (mc.get(x) != null)
	    return true;

	return false;
    }


    int size()
    {
	return count;
    }

}


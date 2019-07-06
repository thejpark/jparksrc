// integer set with adding and deleting in a constant time
// can we use map only? ( that means, add will take more than O(1).


import java.util.HashMap;
import java.util.Map;

class mySet<T extends Number> {

    private class node {
        node(T x)
        {
            data = x;
            prev = next = null;
        }
        T data;
        node prev;
        node next;
    }

    private node head;
    private node tail;
    private Map<T, node> mc;
    private int count;

    public static void main(String[] args)
    {
        mySet ms = new mySet<Integer>();
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
        mc = new HashMap<T, node>();
        head = tail = null;
        count = 0;
    }

    boolean add(T i)
    {
        node n = mc.get(i);

        if (n != null)
            return false;

        n = new node(i);

        if (head == null)
            head = tail = n;
        else
        {
            tail.next = n;
            n.prev = tail;
            tail = n;
        }

        mc.put(i, n);
        count++;
        return true;
    }

    boolean remove(T i)
    {
        node n = mc.get(i);

        if (n == null)
            return false;

        mc.put(i, null);
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


    boolean contains(T i)
    {
        if (mc.get(i) != null)
            return true;

        return false;
    }


    int size()
    {
        return count;
    }

}

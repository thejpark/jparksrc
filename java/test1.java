import java.util.List;
import java.util.Queue;
import java.util.ArrayList;
import java.util.LinkedList;
import java.lang.Integer;
import java.util.Iterator;
import java.util.ListIterator;
import java.util.Map;
import java.util.HashMap;
import java.util.TreeMap;

class A
{
    public A ()
    {
        System.out.println("A is created");
    }
}

class B extends A
{
    public B ()
    {
        System.out.println("B is created");
    }
}


class C
{
    String n;
    int x = y; // x can refer y as y is static. If y is not static, then it cause compile error.
    static int y = 3;

    {
        n = new String("this is instance initializer");
        System.out.println(n);
        System.out.println("x is " + x);
    }

    static String name;

    static
    {
        name = new String("this is static initializer");
        System.out.println(name);
        System.out.println("y is " + y);
    }

    C()
    {
        this(0); // this should be the first to come in the constructor
        System.out.println("C is created");
    }
    C(int a)
    {
        System.out.println("C is created with " + a);
        _a = a;
    }
    int get()
    {
        return _a;
    }

    public boolean isConfusing()
    {
        try {

            return true;
        }
        finally {

            return false;
        }
    }
    protected int _a;
}


/*
 *
 *Access Levels
 *Modifier     Class Package Subclass World
 *public        Y      Y        Y      Y
 *protected     Y      Y        Y      N
 *no modifier   Y      Y        N      N
 *private       Y      N        N      N
 *
 *
 *
 *
 */
// Nested classes are divided into two categories: static and non-static.
// Nested classes that are declared static are simply called static nested
// classes. Non-static nested classes are called inner classes.
// Static nested classes are accessed using the enclosing class name:
// OuterClass.StaticNestedClass
// OuterClass.StaticNestedClass nestedObject = new OuterClass.StaticNestedClass();

// An instance of InnerClass can exist only within an instance of OuterClass and has
// direct access to the methods and fields of its enclosing instance.
// To instantiate an inner class, you must first instantiate the outer class.
// Then, create the inner object within the outer object with this syntax:

// OuterClass.InnerClass innerObject = outerObject.new InnerClass();


// this class cannot be public class, as public class should be in the same file name (Gingleton.java)
class Gingleton
{
    private static Gingleton INSTANCE = null;
    public static Gingleton getInstance()
    {
        if ( INSTANCE == null )
        {
            INSTANCE = new Gingleton();
        }

        return INSTANCE;
    }
    private Gingleton()
    {
    }

}


class Outer {

    class Inner {
        // inner class cannot have static methodd
        public void bar() {
            System.out.println("Inner::bar");
            foo();
        }

        Inner() {
            System.out.println("Inner");
        }
    }

    Outer() {
        System.out.println("outer");
    }

    public Inner ix = new Inner();

    static {
        System.out.println("outer static");
    }

    static void foo() {
        System.out.println("Outer::foo");
    }
}


class test1
{
    static class StaticNested {
        public static void foo() {
            System.out.println("StaticNexted Inner::foo");
            test1();
        }
    }
    public static void main(String args[])
    {
        ArrayList<Integer> a = new ArrayList<Integer>();
        a.add(Integer.parseInt("1"));
        a.add(2);
        a.add(3);
        Iterator<Integer> it = a.iterator();
        int i = 0;
        while(it.hasNext()) {
            System.out.println(">" + it.next() + " == " + a.get(i++));
        }
        int[] b = new int[3];
        System.out.println("the size is " + b.length); // java has no size()
        String ss = new String("Hello World !!!");
        for (String s: ss.split(" "))
            System.out.println(s);
        argtest(ss);
        System.out.println(ss);
        String x[] = {"a", "this", "is", "this", "b"};
        maptest(x);
        StaticNested ix = new StaticNested();
        ix.foo();
        Outer ox = new Outer();
        ox.ix.bar();
        ox = new Outer();
        ListExample();
        stringTest();
    }

    static void argtest(String s)
    {
        s = new String("this is old world");
    }


    public static void maptest(String args[])
    {
        Map<String, Integer> m = new HashMap<String, Integer>();

        // Initialize frequency table from command line
        for (String a : args) {

            Integer freq = m.get(a);

            m.put(a, (freq == null) ? 1 : freq + 1);

        }

        System.out.println(m.size() + " distinct words:");
        System.out.println(m);

        for (Map.Entry e : m.entrySet()) // there are keySet() and valueSet() as well.
            System.out.println(e.getKey() + " : " + e.getValue());

        // same
        System.out.println("****************************1");

        for (Map.Entry<String, Integer> e : m.entrySet()) // Map.Entry<..>
            System.out.println(e.getKey() + " : " + e.getValue());

        System.out.println("****************************2");

        for (Iterator<Map.Entry<String, Integer>> it = m.entrySet().iterator(); it.hasNext();) { // Should specify iterator type. Otherwise error.
            Map.Entry e = it.next(); // works fine
            System.out.println(e.getKey() + " : " + e.getValue());
        }

        System.out.println("****************************3");

        for (Iterator<Map.Entry<String, Integer>> it = m.entrySet().iterator(); it.hasNext();) { // Should specify iterator type. Otherwise error.
            Map.Entry<String, Integer>  e = it.next(); // works fine a well
            System.out.println(e.getKey() + " : " + e.getValue());
        }

        System.out.println("sorted map");

        Map<String, Integer> sm = new TreeMap<String, Integer>(m);
        for (Map.Entry<String, Integer> e : sm.entrySet()) {
            System.out.println(e.getKey());
        }

        Map<String, Integer> m2 = new HashMap<String, Integer>(m);

        m2.put("test", 1);

        if(m2.keySet().equals(m.keySet()))
            System.out.println("m and m2 has same keyset");


        if(m2.keySet().containsAll(m.keySet()))
            System.out.println("m2 contains m");

    }

    // this function is declared as static, as non-static function cannot be called in static function.
    public static void test2()
    {
        Gingleton a = Gingleton.getInstance();
        System.out.println(a);
    }

    public static void test1()
    {
        System.out.println("test 1 started");

        A a;

        A b = new B();

        b = null;

        C c = new C(3);

        System.out.println("_a is " + c._a + " " + c.get());

        if (c instanceof Object)
            System.out.println("C is instance of Object");

        System.out.println("c.isConfusing() is " + c.isConfusing());
    }

    /*
     * http://stackoverflow.com/questions/339699/java-generics-type-erasure-when-and-what-happens
     *
     *Type erasure applies to the use of generics. There's definitely metadata in the class file to say whether or not a method/type is generic, and what the constraints are etc. But when generics are used, they're converted into compile-time checks and execution-time casts. So this code:
     *
     *List<String> list = new ArrayList<String>();
     *list.add("Hi");
     *String x = list.get(0);
     *is compiled into
     *
     *List list = new ArrayList();
     *list.add("Hi");
     *String x = (String) list.get(0);
     *At execution time there's no way of finding out that T=string for the list object - that information is gone.
     *
     *... but the List<T> interface itself still advertises itself as being generic.
     *
     *EDIT: Just to clarify, the compiler does retain the information about the variable being a List<String> - but you still can't find out that T=string for the list object itself.
     *
     *
     */

    public static void ListExample()
    {
        List<String> ls = new ArrayList<String>();
        ls.add("One");
        ls.add("Three");
        ls.add("Two");

        Iterator it = ls.iterator();

        while(it.hasNext())
        {
            String value = (String)it.next();
            System.out.println("Value: " + value);
        }

        if (ls instanceof ArrayList)
            System.out.println("ls is string arraylist");
        else
            System.out.println("NO!!");

        if (ls instanceof List)
            System.out.println("ls is string list");
        else
            System.out.println("NO!!");

        if (ls instanceof ArrayList<?>)
            System.out.println("ls is string arraylist");
        else
            System.out.println("NO!!");

        if (ls instanceof List<?>)
            System.out.println("ls is string list");
        else
            System.out.println("NO!!");
    }

    public static void stringTest()
    {
        String a = "foo";

        String b = "food".substring(0, 3);

        String c = b.intern();

        System.out.println(" " + a + " " + b + " " + c);

        if (a.equals(b)) {

            if (a == b) {
                System.out.println("1");
            } else if (a == c) {
                System.out.println("2");
            } else {
                System.out.println("3");
            }

        } else {
            System.out.println("4");
        }

        System.out.println("abc");

        String cde = "cde";

        System.out.println("abc" + cde);

        String e = "abc".substring(2,3);

        String f = cde.substring(1, 2);

        System.out.println(e);
        System.out.println(f);
    }
}


// leetcode 332. Reconstruct Itinerary

// Given a list of airline tickets represented by pairs of departure and arrival airports [from, to], reconstruct the itinerary in order. All of the tickets belong to a man who departs from JFK. Thus, the itinerary must begin with JFK.

// Note:

// If there are multiple valid itineraries, you should return the itinerary that has the smallest lexical order when read as a single string. For example, the itinerary ["JFK", "LGA"] has a smaller lexical order than ["JFK", "LGB"].
// All airports are represented by three capital letters (IATA code).
// You may assume all tickets form at least one valid itinerary.
// One must use all the tickets once and only once.
// Example 1:

// Input: [["MUC", "LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]]
// Output: ["JFK", "MUC", "LHR", "SFO", "SJC"]
// Example 2:

// Input: [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
// Output: ["JFK","ATL","JFK","SFO","ATL","SFO"]
// Explanation: Another possible reconstruction is ["JFK","SFO","ATL","JFK","ATL","SFO"].
//              But it is larger in lexical order.

class Solution {
    public List<String> findItinerary(List<List<String>> tickets) {
        HashMap<String, PriorityQueue<String>> m = new HashMap<>();
        for (var t : tickets)
        {
            var depart = t.get(0);
            m.putIfAbsent(depart, new PriorityQueue<String>());
            m.get(depart).add(t.get(1));
        }


        LinkedList<String> r = new LinkedList<>();
        foo(m, r, "JFK");

        return r;

    }

    void foo(Map<String, PriorityQueue<String>> m, LinkedList<String> r, String depart)
    {
        PriorityQueue<String> q = m.get(depart);

        while (q != null && !q.isEmpty())
        {
            var newDep = q.poll();
            foo(m, r, newDep);
        }

        r.addFirst(depart);
    }
}

class Solution2 {
    public List<String> findItinerary(List<List<String>> tickets) {
        Map<String, List<Integer>> m = new HashMap<>();
        Collections.sort(tickets, new Comparator<List<String>>() {
            @Override
            public int compare(List<String> o1, List<String> o2) {
                    int r = o1.get(0).compareTo(o2.get(0));
                    if (r == 0)
                    {
                        return o1.get(1).compareTo(o2.get(1));
                    }
                    return r;
            }
        });
        int i = 0;
        for (var t : tickets)
        {
            var depart = t.get(0);
            var l = m.getOrDefault(depart, new LinkedList<Integer>());
            l.add(i);
            m.put(depart, l);
            i += 1;
        }

        LinkedList<String> r = new LinkedList<>();
        r.add("JFK");
        boolean[] visit = new boolean[tickets.size()];
        foo("JFK", tickets, m, visit, r);

        return r;

    }

    boolean foo(String depart, List<List<String>> t, Map<String, List<Integer>> m, boolean[] v, LinkedList<String> r)
    {
        if (r.size() == v.length + 1)
        {
            return true;
        }

        var l = m.get(depart);
        if (l == null)
            return false;
        for (var e: l)
        {
            if (!v[e])
            {
                v[e] = true;
                var str = t.get(e).get(1);
                r.add(str);
                boolean result = foo(str, t, m, v, r);
                if (result)
                    return true;
                r.removeLast();
                v[e] = false;
            }
        }

        return false;
    }
}


class pair {
    int k;
    int v;

    public pair(int key, int value) {
        this.k = key;
        this.v = value;
    }
}


// leetcode 218 skyline.
// A city's skyline is the outer contour of the silhouette formed by all the buildings in that city when viewed from a distance. Given the locations and heights of all the buildings, return the skyline formed by these buildings collectively.
class Skyline {
    public List<List<Integer>> getSkyline(int[][] buildings) {
        List<List<Integer>> res = new ArrayList<>();

        pair[] p = new pair[buildings.length * 2];

        for (int i = 0, j = 0; i < buildings.length; ++i, j += 2)
        {
            p[j] = new pair(buildings[i][0], -buildings[i][2]);
            p[j + 1] = new pair(buildings[i][1], buildings[i][2]);
        }

        Arrays.sort(p, new Comparator<pair>() {
            @Override public int compare(pair p1, pair p2)
            {
                if (p1.k == p2.k)
                   return p1.v - p2.v;
                return p1.k - p2.k;
            }
        });
        int prev = 0, cur = 0;

        TreeMap<Integer, Integer> m = new TreeMap<>();

        m.put(0, 1);
        for (pair e : p) {

            if (e.v < 0)
            {
                int h = -e.v;
                Integer x = m.getOrDefault(h, 0);
                m.put(h, x + 1);
            }
            else
            {
                int h = e.v;
                Integer x = m.get(h);
                if (x == 1)
                    m.remove(h);
                else
                    m.put(h, x - 1);

            }

            cur = m.lastKey();
            if (cur != prev) {
                List<Integer> l = new ArrayList<>();
                l.add(e.k);
                l.add(cur);
                res.add(l);
                prev = cur;
            }
        }
        return res;

    }
}
class SummaryRanges {
    // from discussion
    /** Initialize your data structure here. */
    TreeSet<Integer> set;
    int max = 0;
    int min = Integer.MAX_VALUE;
    public SummaryRanges() {
        set = new TreeSet<>();
    }

    public void addNum(int val) {
        set.add(val);
        max = Math.max(max, val);
        min = Math.min(min, val);
    }

    public List<int[]> getIntervals() {
        List<int[]> list = new ArrayList<>();
        int i = min;
        while (i <= max) {
            if (!set.contains(i)) {
                i++;
                continue;
            }
            int j = i + 1;
            while (j <= max && set.contains(j)) {
                j++;
            }
            list.add(new int[] {i, j - 1});
            i = j;
        }
        return list;
    }
}

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges obj = new SummaryRanges();
 * obj.addNum(val);
 * int[][] param_2 = obj.getIntervals();
 */



public class RateLimiter {
    public int REQUEST_LIMIT = 100;
    public Long TIME_LIMIT = 1000L;
    public class HitCounter {
        public Queue<Long> queue;
        public HitCounter() {
            queue = new LinkedList<>();
        }
        public boolean hit(long timestamp) {
            /* when a timestamp hit, we should poll all the timestamp before TIME_LIMIT*/
            while (!queue.isEmpty() && queue.peek() - timestamp >= TIME_LIMIT) queue.poll();
            if (queue.size() < REQUEST_LIMIT) {
                queue.add(timestamp); return true;
            }
            return false;
        }
    }
    public HashMap<String, HitCounter> clientTimeStampMap = new HashMap<>();
    public boolean isAllow(String clientId) {
        // if test is needed, then probably need to take am interface to get the time, as  an  interface.
        // or use another argument for current time.
        long currTime = System.currentTimeMillis();
        if (!clientTimeStampMap.containsKey(clientId)) {
            HitCounter h = new HitCounter();
            clientTimeStampMap.put(clidneId, h);
            h.hit(currTime); return true;
        } else {
            HitCounter h = clientTimeStampMap.get(clientId);
            return h.hit(currTime);
        }
    }

}

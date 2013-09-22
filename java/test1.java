import java.util.List;
import java.util.Queue;
import java.util.ArrayList;
import java.util.LinkedList;
import java.lang.Integer;
import java.util.Iterator;
import java.util.ListIterator;
import java.util.Map;
import java.util.HashMap;

// test for Atlatian
import findarray.MyFindArray;
import iteration.MyFolder;
import iteration.Function2;
import flatten.Tree;
import flatten.MyFlattenTree;
import flatten.Either;
import flatten.Triple;
import findcommonancestor.MyFindCommonAncestor;

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



//parameterized
class MyFunc2<T extends Integer, U extends Integer, R extends Integer > implements Function2<T, U, R>
{
    public R apply(T t, U u) 
    {
        int x = u.intValue() + t.intValue();
        Integer i = new Integer(x);
        return (R)i;
        
    }
}

class MyFunc3 implements Function2<Integer, Integer, Integer>
{
    public Integer apply(Integer t, Integer u) 
    {
        int x = u.intValue() + t.intValue();
        Integer i = new Integer(x);
        return i;
        
    }
}

class myfunc4 implements Function2<Integer, List, List>
{
    public List apply(Integer t, List u)
    {
        u.add(t);
        return u;
    }
}



class test1 
{
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
        

        flatten();

        System.out.println("test folder");
        folder4();
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

            System.out.println("****************************4");

            /*
            for (Iterator it = m.entrySet().iterator(); it.hasNext();) { // Should specify iterator type. Otherwise error. Iterator is Object type.
                                                                         // but m.entrySet.iterator() is Map.Entry<String, Integer> type
                Map.Entry<String, Integer>  e = it.next(); // works fine a well
                System.out.println(e.getKey() + " : " + e.getValue());
            }
            */

            Map<String, Integer> m2 = new HashMap<String, Integer>(m);

            m2.put("test", 1);

            if(m2.keySet().equals(m.keySet()))
                System.out.println("m and m2 has same keyset");
            

            if(m2.keySet().containsAll(m.keySet()))
                System.out.println("m2 contains m");
            
    }
    
    
    public static void commonAncestor()
    {
        String[] commits = {"G", "F", "E", "D", "C", "B", "A"
        };
        String[][] parents ={
            {
                "F","D"
            },{"E"
            }, {"B"
            }, {"C"
            }, {"B"
            }, {"A"
            }, null
        };
        String commit1 = "D";
        String commit2 = "F";
        MyFindCommonAncestor finder = new MyFindCommonAncestor();
        
        System.out.println(finder.findCommmonAncestor(commits, parents, commit1, commit2));
        System.out.println(finder.findCommmonAncestor(commits, parents, "A", "B"));
        System.out.println(finder.findCommmonAncestor(commits, parents, "E", "G"));
        System.out.println(finder.findCommmonAncestor(commits, parents, "E", "D"));
        System.out.println(finder.findCommmonAncestor(commits, parents, "B", "F"));
    }
    

    public static void flatten()
    {

        Tree<Integer> n = Tree.Node.tree(new Integer(5), new Integer(4), new Integer(9));  // static method does not need type parameter? ^^;
        Tree<Integer> l1 = Tree.Leaf.leaf(new Integer(1));
        Tree<Integer> l2 = Tree.Leaf.leaf(new Integer(6));
        Tree<Integer> t = new Tree.Node(l1, n, l2);
        MyFlattenTree<Integer> mt = new MyFlattenTree<Integer>();
        List<Integer> l = mt.flattenInOrder(t);
        Iterator<Integer> it = l.iterator();
        //ListIterator<Integer> it = l.listIterator()
        while(it.hasNext()) {
            int p = it.next();
            System.out.println(p + " " );
            
        }
        
    }
    
    public static void flatten2()
    {
        MyFlattenTree<Integer> mt = new MyFlattenTree<Integer>();
        List<Integer> l = mt.flattenInOrder(null);
        ListIterator<Integer> it = l.listIterator();
        while(it.hasNext()) {
            int p = it.next();
            System.out.println(p + " " );
            
        }
        
    }
    
    
    public static void folder()
    {
                
        Queue<java.lang.Integer> x = new LinkedList<java.lang.Integer>();
        MyFolder<Integer, Integer> mf = new MyFolder<Integer, Integer>();
        x.add(1);
        x.add(2);
        x.add(3);
        MyFunc2<Integer, Integer, Integer> mf2 = new MyFunc2<Integer, Integer, Integer>();
        
        Integer r = mf.fold(new Integer(0), x, mf2);
        System.out.println(r);
    }

    public static void folder3()
    {
                
        Queue<java.lang.Integer> x = new LinkedList<java.lang.Integer>();
        MyFolder<Integer, Integer> mf = new MyFolder<Integer, Integer>();
        x.add(1);
        x.add(2);
        x.add(3);
        MyFunc3 mf2 = new MyFunc3();
        
        Integer r = mf.fold(new Integer(0), x, mf2);
        System.out.println(r);
    }

    public static void folder4()
    {
                
        Queue<java.lang.Integer> x = new LinkedList<java.lang.Integer>();
        MyFolder<Integer, List> mf = new MyFolder<Integer, List>();
        x.add(1);
        x.add(2);
        x.add(3);
        
        myfunc4 mf2 = new myfunc4();
        List r = mf.fold(new ArrayList<Integer>(), x, mf2);
        Iterator<Integer> it = r.iterator();
        while(it.hasNext())
            System.out.println(it.next());
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

    
    static void findarray()
    {
        int a[] = {4, 9, 3, 7, 8
        };
        int b[] = {3, 7
        };

        int a1[] = {1, 3, 5
        };
        int b1[] = {1
        };

        int a2[] = {7, 8, 9
        };
        int b2[] = {8, 9, 10
        };

        int a3[] = {7, 8
        };
        int b3[] = {8, 9, 10
        };

        int a4[] = {7, 8, 9
        };
        int b4[] = {7, 8, 9
        };

        int a5[] = {
        };
        int b5[] = {
        };


        int a6[] = {7, 8, 9
        };
        int b6[] = {
        };

        int a7[] = {
        };
        int b7[] = {7, 8, 9
        };


        
        MyFindArray fa = new MyFindArray();
        
        System.out.println(fa.findArray(a, b));
        System.out.println(fa.findArray(a1, b1));
        System.out.println(fa.findArray(a2, b2));
        
        System.out.println(fa.findArray(a3, b3));
        System.out.println(fa.findArray(a4, b4));
        System.out.println(fa.findArray(a5, b5));
        System.out.println(fa.findArray(a6, b6));
        System.out.println(fa.findArray(a7, b7));
    }
    
}

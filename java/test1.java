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

class test1 
{
    static class StaticNested {

	public static void foo() {
	    System.out.println("inner::foo");
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

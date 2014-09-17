// Java class definition does not ends with ';'

// The most commonly used type parameter names are:

// E - Element (used extensively by the Java Collections Framework)
// K - Key
// N - Number
// T - Type
// V - Value
// S,U,V etc. - 2nd, 3rd, 4th types

// Java generic class and generic method

import java.lang.Integer;
import java.lang.String;

public class Util {
    // Generic static method
    public static <K, V> boolean compare(Pair<K, V> p1, Pair<K, V> p2) {
        return p1.getKey().equals(p2.getKey()) &&
               p1.getValue().equals(p2.getValue());
    }
}

public class Pair<K, V> {

    private K key;
    private V value;

    // Generic constructor
    public Pair(K key, V value) {
        this.key = key;
        this.value = value;
    }

    // Generic methods
    public void setKey(K key) { this.key = key; }
    public void setValue(V value) { this.value = value; }
    public K getKey()   { return key; }
    public V getValue() { return value; }
}

Pair<Integer, String> p1 = new Pair<>(1, "apple");
Pair<Integer, String> p2 = new Pair<>(2, "pear");

// The complete syntax for invoking this method would be:

boolean same = Util.<Integer, String>compare(p1, p2);

// The type has been explicitly provided, as shown in bold.
// Generally, this can be left out and the compiler will infer the type that is needed:

boolean same2 = Util.compare(p1, p2);




// Bounded Type Parameters
// There may be times when you want to restrict the types that can be used as type arguments in a parameterized type. For example, a method that operates on numbers might only want to accept instances of Number or its subclasses. This is what bounded type parameters are for.

// To declare a bounded type parameter, list the type parameter's name, followed by the extends keyword, followed by its upper bound, which in this example is Number. Note that, in this context, extends is used in a general sense to mean either "extends" (as in classes) or "implements" (as in interfaces).


// also define class using bounded type parameter
public class NaturalNumber<T extends Integer> {

    private T n;

    public NaturalNumber(T n)  { this.n = n; }

    public boolean isEven() {
        return n.intValue() % 2 == 0;
    }
}


// Multiple Bounds

// The preceding example illustrates the use of a type parameter with a single bound,
// but a type parameter can have multiple bounds:

// <T extends B1 & B2 & B3>
// A type variable with multiple bounds is a subtype of all the types listed in the bound.
// If one of the bounds is a class, it must be specified first. For example:

// Class A { /* ... */ }
// interface B { /* ... */ }
// interface C { /* ... */ }

// class D <T extends A & B & C> { /* ... */ }



public static <T> int countGreaterThan(T[] anArray, T elem) {
    int count = 0;
    for (T e : anArray)
        if (e > elem)  // compiler error
            ++count;
    return count;
}


// the greater than operator (>) applies only to primitive types such as short,
// int, double, long, float, byte, and char. You cannot use the > operator to compare
// objects. To fix the problem, use a type parameter bounded by the Comparable<T> interface:

public static <T extends Comparable<T>> int countGreaterThan(T[] anArray, T elem) {
    int count = 0;
    for (T e : anArray)
        if (e.compareTo(elem) > 0)
            ++count;
    return count;
}



// Assume a class Box, and its instantiation of  Box<Number> and Box<Integer>.
// Though Integer is subtype of NUmber, Box<Integer> is not a subtype of Box<Nu
// Although Integer is a subtype of Number, List<Integer> is not a subtype of
// List<Number> and, in fact, these two types are not related. The common paren
// List<Number> and List<Integer> is List<?>.

// upper bounded wildcard
//The following code adds the numbers 1 through 10 to the end of a list:

public static void addNumbers(List<? super Integer> list) {
    for (int i = 1; i <= 10; i++) {
        list.add(i);
    }
}

// unbounded wildcard
public static void printList(List<?> list) {
    for (Object elem: list)
        System.out.print(elem + " ");
    System.out.println();
}



// lower bound wildcard
// The following code adds the numbers 1 through 10 to the end of a list:

public static void addNumbers(List<? super Integer> list) {
    for (int i = 1; i <= 10; i++) {
        list.add(i);
    }
}

// wildcard as an argument 1

public static double sumOfList(List<? extends Number> list) {
    double s = 0.0;
    for (Number n : list)
        s += n.doubleValue();
    return s;
}

// wildcard as an argument 2
if (ls instanceof ArrayList<?>)
    System.out.println("ls is string arraylist");


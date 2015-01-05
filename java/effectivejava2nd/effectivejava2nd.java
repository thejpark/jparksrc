/**
   Java access privilege
   http://docs.oracle.com/javase/tutorial/java/javaOO/accesscontrol.html
*
*/

package effectivejava2nd;

import java.util.Date;
import java.util.Calendar;
import java.util.TimeZone;
import java.util.Arrays;

class effectivejava2nd {
    private static Person p;

    public static void main(String[] args) {
	System.out.println("Hello World");
	System.out.println(factory.valueOf(true));

	// finally?
	if (isConfusing())
	    System.out.println(factory.valueOf(true));
	else
	    System.out.println(factory.valueOf(false));

	// the following creates anonymous subsclas of Person
	p = new Person() {
		@Override
		public boolean isBabyBoomer() {
		    System.out.println("this is subclass");
		    return super.isBabyBoomer();
		}
	    };

	if (p instanceof Object)
	    System.out.println("Person is Object");
    }

    public static boolean isConfusing() {
	try {
	    return true;
	} finally {
	    return false;
	}
    }

    public static void testBuilder()
    {
	NutritionFacts cocaCola = new NutritionFacts.NBuilder(240, 8).
	    calories(100).sodium(35).carbohydrate(27).build();
    }
}

/*

Integer.parseInt() takes string and returns primitive
Integer.valueOf() takes primitive type and return object reference

a == b compares reference, not value
a.equals(b) compares value
*/

class factory {
    /*
      advantages
      static factory has name,
      static factory not need to create instance for each call (flyweight), use == instead of equals
      static factory can return subtype, interface based framework
      static factory can reduce the verbosity of creating parameterized type instance

      disadvantages
      providing only static factory methods, classes without public or protected constructors cannot be subclassed.
      they are not readily distinguishable from other static methods

      so, avoid the reflex to provide public constructors without first considering static factories
    */

    public static Boolean valueOf(boolean b) {
	return b ? Boolean.TRUE : Boolean.FALSE;
    }
}


// Builder Pattern. The Builder pat- tern simulates named optional parameters as found in Ada and Python.
class NutritionFacts {
    private final int servingSize;
    private final int servings;
    private final int calories;
    private final int fat;
    private final int sodium;
    private final int carbohydrate;
    public static class NBuilder implements Builder<NutritionFacts> {
        // Required parameters
        private final int servingSize;
        private final int servings;
        // Optional parameters - initialized to default values
        private int calories      = 0;
        private int fat           = 0;
        private int carbohydrate  = 0;
        private int sodium        = 0;
        public NBuilder(int servingSize, int servings) {
            this.servingSize = servingSize;
            this.servings    = servings;
	}
        public NBuilder calories(int val)
            { calories = val;      return this; }
        public NBuilder fat(int val)
            { fat = val;           return this; }
        public NBuilder carbohydrate(int val)
            { carbohydrate = val;  return this; }
        public NBuilder sodium(int val)
            { sodium = val;        return this; }
        public NutritionFacts build() {
            return new NutritionFacts(this);
	}
    }

    private NutritionFacts(NBuilder builder) {
        servingSize  = builder.servingSize;
        servings     = builder.servings;
        calories     = builder.calories;
        fat          = builder.fat;
        sodium       = builder.sodium;
        carbohydrate = builder.carbohydrate;
    }
 }


// Singleton with public final field
class Elvis {
    public static final Elvis INSTANCE = new Elvis();
    private Elvis() { }
    public void leaveTheBuilding() {}
}

// To make a singleton class that is implemented using either of the
// previous approaches serializable (Chapter 11), it is not sufficient
// merely to add imple- ments Serializable to its declaration.
// To maintain the singleton guarantee, you have to declare all
// instance fields transient and provide a readResolve method.
// Otherwise, each time a serialized instance is deserialized, a new
// instance will be created, leading, in the case of our example, to
// spurious Elvis sightings. To prevent this, add this readResolve
// method to the Elvis class:
   // readResolve method to preserve singleton property
   // private Object readResolve() {
   //      // Return the one true Elvis and let the garbage collector
   //      // take care of the Elvis impersonator.
   //     return INSTANCE;
   // }

// Singleton with static factory part 2
class Elvis2 {
    private static final Elvis2 INSTANCE = new Elvis2();
    private Elvis2() {  }
    public static Elvis2 getInstance() { return INSTANCE; }
    public void leaveTheBuilding() {}
}


// Singleton with static factory part 3 (from Java 1.5)
// Enum singleton - the preferred approach.
// This approach is functionally equivalent to the public
// field approach, except that it is more concise, provides
// the serialization machinery for free, and provides an ironclad
// guarantee against multiple instantiation, even in the face of
// sophisticated serialization or reflection attacks.
// Single-element enum type. Examples of enum is in
// http://docs.oracle.com/javase/tutorial/java/javaOO/enum.html

enum Elvis3 {
    INSTANCE;
    public void leaveTheBuilding() {}
}


class Person {
    private final Date birthDate;
    // Other fields, methods, and constructor omitted
    /**
     * The starting and ending dates of the baby boom.
     */
    private static final Date BOOM_START;
    private static final Date BOOM_END;

    static {
	// avoid creating unnecessary object. Instead of creating it
	// in the isBabyBoomer method, create it in static
	Calendar gmtCal =
	    Calendar.getInstance(TimeZone.getTimeZone("GMT"));
	gmtCal.set(1946, Calendar.JANUARY, 1, 0, 0, 0);
	BOOM_START = gmtCal.getTime();
	gmtCal.set(1965, Calendar.JANUARY, 1, 0, 0, 0);
	BOOM_END = gmtCal.getTime();
    }

    private Person(Date date)
    {
	birthDate = date;
    }

    Person()
    {
	birthDate = new Date();
    }

    public boolean isBabyBoomer() {
	return birthDate.compareTo(BOOM_START) >= 0 &&
	    birthDate.compareTo(BOOM_END)   <  0;
    }
}

// avoid creating unnecessary object, such as adapter in adapter
// pattern. every call to keySet on a given Map object may return
// the same Set instance.


// 7. Avoid finalizer. If terminating upon exception is required, then
// do t explicitly.
// try-finally block guarantees execution of termination method
   // Foo foo = new Foo(...);
   // try {
   //     // Do what must be done with foo
   //     ...
   // } finally {
   //     foo.terminate();  // Explicit termination method
   // }

// Manual finalizer chaining.
// It is important to note that finalizer chaining is not performed automatically.
// @Override means you are overriding the base class method. In java6, it
// also mean you are implementing a method from an interface. It protects
// you from typos when you think are overriding a method but you mistyped
// something.
// @Override protected void finalize() throws Throwable {
//     try {
// 	... // Finalize subclass state
//     } finally {
// 	super.finalize();
//     }
//  }


// item 8. The equals method implements an equivalence relation. Reflexive,
// symmetric, transitive, consistent...

// item 9. You must override hashCode in every class that overrides equals
final class PhoneNumber implements Comparable<PhoneNumber> {
    private final short areaCode;
    private final short prefix;
    private final short lineNumber;
    public PhoneNumber(int areaCode, int prefix, int lineNumber) {
	rangeCheck(areaCode,    999, "area code");
	rangeCheck(prefix,      999, "prefix");
	rangeCheck(lineNumber, 9999, "line number");
	this.areaCode  = (short) areaCode;
	this.prefix  = (short) prefix;
	this.lineNumber = (short) lineNumber;
    }
    private static void rangeCheck(int arg, int max,
				   String name) {
	if (arg < 0 || arg > max)
	    throw new IllegalArgumentException(name +": " + arg);
    }

    // item 8
    @Override public boolean equals(Object o) { if (o == this)
	    return true;
	if (!(o instanceof PhoneNumber))
	    return false;
	PhoneNumber pn = (PhoneNumber)o;
	return pn.lineNumber == lineNumber
	    && pn.prefix  == prefix
	    && pn.areaCode  == areaCode;
    }
    // item 9
    @Override public int hashCode() {
	int result = 17;
	result = 31 * result + areaCode;
	result = 31 * result + prefix;
	result = 31 * result + lineNumber;
	return result;
    }
    // item 10
    @Override public String toString() {
	return String.format("(%03d) %03d-%04d",
			     areaCode, prefix, lineNumber);
    }
    // item 11. clone method
    // never make the client do anything the library can do for the client
    @Override public PhoneNumber clone() {
	try {
	    return (PhoneNumber) super.clone();
	} catch(CloneNotSupportedException e) {
	    throw new AssertionError();  // Can't happen
	}
    }

    public int compareTo(PhoneNumber pn) {
	// Compare area codes
	if (areaCode < pn.areaCode)
	    return -1;
	if (areaCode > pn.areaCode)
	    return 1;
	// Area codes are equal, compare prefixes
	if (prefix < pn.prefix)
	    return -1;
	if (prefix > pn.prefix)
	    return 1;
	// Area codes and prefixes are equal, compare line numbers
	if (lineNumber < pn.lineNumber)
	    return -1;
	if (lineNumber > pn.lineNumber)
	    return 1;
	return 0;  // All fields are equal
    }

   // this  version not always work not
   // enough to hold the difference between two arbitrary signed 32-bit integers. If i is a large
   // positive int and j is a large negative int, will overflow and return a negative value.
   // The resulting compareTo method will return incorrect results
   //  public int compareTo(PhoneNumber pn) {
   //     // Compare area codes
   //     int areaCodeDiff = areaCode - pn.areaCode;
   //     if (areaCodeDiff != 0)
   //         return areaCodeDiff;
   //     // Area codes are equal, compare prefixes
   //     int prefixDiff = prefix - pn.prefix;
   //     if (prefixDiff != 0)
   //         return prefixDiff;
   //     // Area codes and prefixes are equal, compare line numbers
   //     return lineNumber - pn.lineNumber;
   // }
}

class Stack {
    private Object[] elements;
    private int size = 0;
    private static final int DEFAULT_INITIAL_CAPACITY = 16;
    public Stack() {
	this.elements = new Object[DEFAULT_INITIAL_CAPACITY];
    }
    public void push(Object e) {
	ensureCapacity();
	elements[size++] = e;
    }
    public Object pop() {
	if (size == 0)
	    return null;
	Object result = elements[--size];
	elements[size] = null; // Eliminate obsolete reference
	return result;
    }
    // Ensure space for at least one more element.
    private void ensureCapacity() {
	if (elements.length == size)
	    elements = Arrays.copyOf(elements, 2 * size + 1);
    }

    // deep clone. otherwise two stack may point to the same element.
    // item 11.
    // In order to make a class cloneable, it may be necessary to remove final modifiers from
    // some fields.
    // To make a thread-safe class imple- ment Cloneable, remember that its clone method must
    // be properly synchronized just like any other method
    //
    // so, don't use clone (or provide clone) except array copy
    @Override public Stack clone() {
	try {
	    Stack result = (Stack) super.clone();
	    // if elements have references, then each element should be deep copied as well.
	    result.elements = elements.clone();
	    return result;
	} catch (CloneNotSupportedException e) {
	    throw new AssertionError();
	}
    }
}

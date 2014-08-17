/**
   Java access privilege
   http://docs.oracle.com/javase/tutorial/java/javaOO/accesscontrol.html
*
*/

package effectivejava2nd;

import java.util.Date;
import java.util.Calendar;
import java.util.TimeZone;

class effectivejava2nd {
    public static void main(String[] args) {
	System.out.println("Hello World");
	System.out.println(factory.valueOf(true));

	// finally?
	if (isConfusing())
	    System.out.println(factory.valueOf(true));
	else
	    System.out.println(factory.valueOf(false));

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
// Single-element enum type
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
// @Override protected void finalize() throws Throwable {
//     try {
// 	... // Finalize subclass state
//     } finally {
// 	super.finalize();
//     }
//  }

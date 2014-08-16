/**
   Java access privilege
   http://docs.oracle.com/javase/tutorial/java/javaOO/accesscontrol.html
*
*/

package effectivejava2nd;

class effectivejava2nd {
    public static void main(String[] args) {
	System.out.println("Hello World");
	System.out.println(factory.valueOf(true));
	
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

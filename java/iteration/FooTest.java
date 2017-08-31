package iteration;


import static org.junit.Assert.assertEquals;
import org.junit.Test;
import org.junit.Ignore;
import org.junit.runner.RunWith;
import org.junit.runners.JUnit4;
import java.util.*;

/**
 * Tests for {@link Foo}.
 *
 * @author user@example.com (John Doe)
 */
public class FooTest {

    @Test
    public void test1() {
        Queue<Integer> x = new LinkedList();
        MyFolder<Integer, Integer> mf = new MyFolder();
        x.add(1);
        x.add(2);
        x.add(3);
        MyFunc2<Integer, Integer, Integer> mf2 = new MyFunc2();

        Integer r = mf.fold(new Integer(0), x, mf2);
        org.junit.Assert.assertEquals("failure - not equal", new Integer(6), r);
    }

    @Test
    public void test2() {
        Queue<Integer> x = new LinkedList();
        MyFolder<Integer, Integer> mf = new MyFolder();
        x.add(1);
        x.add(2);
        x.add(3);
        MyFunc3 mf3 = MyFunc3.INSTANCE;

        Integer r = mf.fold(new Integer(0), x, mf3);
        org.junit.Assert.assertEquals("failure - not equal", 6, r.intValue());
    }

    @Test
    public void test3() {
        Queue<Integer> x = new LinkedList();
        MyFolder<Integer, List> mf = new MyFolder<Integer, List>();
        x.add(1);
        x.add(2);
        x.add(3);

        myfunc4 mf4 = new myfunc4();
        List r = mf.fold(new ArrayList<Integer>(), x, mf4);
        Iterator<Integer> it = r.iterator();
        int i = 1;
        while(it.hasNext())
            org.junit.Assert.assertEquals("failure - not equal", it.next().intValue(), i++);
    }

    @Test
    public void test4() {
        Queue<Integer> x = new LinkedList();
        MyFolder<Integer, Integer> mf = new MyFolder();
        x.add(1);
        x.add(2);
        x.add(3);

        // function object can be anonmous class
        Integer r = mf.fold(new Integer(0), x, new Function2<Integer, Integer, Integer>() {
                public Integer apply(Integer t, Integer u) {
                    int x = u.intValue() + t.intValue();
                    Integer i = new Integer(x);
                    return i;
                }
            });
        org.junit.Assert.assertEquals("failure - not equal", 6, r.intValue());
    }


    @Test
    public void checkQueueEmpty() {
        Queue<Integer> x = new LinkedList();
        MyFolder<Integer, Integer> mf = new MyFolder();
        x.add(1);
        x.add(2);
        x.add(3);
        MyFunc2<Integer, Integer, Integer> mf2 = new MyFunc2();

        Integer r = mf.fold(new Integer(0), x, mf2);
        org.junit.Assert.assertEquals("failure - not equal", true, x.isEmpty());
    }

    @Test
    @Ignore
    public void thisIsIgnored() {
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

    class myfunc4 implements Function2<Integer, List, List>
    {
        public List apply(Integer t, List u)
        {
            u.add(t);
            return u;
        }
    }

}

class MyFunc3 implements Function2<Integer, Integer, Integer>
{
    // function object is stateless, so should be singleton.
    private MyFunc3() {};
    public static final MyFunc3 INSTANCE = new MyFunc3();
    public Integer apply(Integer t, Integer u)
    {
        int x = u.intValue() + t.intValue();
        Integer i = new Integer(x);
        return i;
    }
}

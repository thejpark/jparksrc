package concurrency;

import static org.junit.Assert.*;
import org.junit.Test;
import org.junit.Ignore;
import org.junit.runner.RunWith;
import org.junit.runners.JUnit4;
import java.util.*;
import java.util.concurrent.*;
import java.lang.*;
import java.util.concurrent.atomic.*;
import java.math.BigInteger;

/**
 * Tests for {@link Foo}.
 *
 * @author user@example.com (Jung Gyu Park)
 */
class UnsafeIntData
{
    UnsafeIntData()
    {
        count = 0;
    }

    void inc() {
        for (int i = 0; i < 100; ++i)
            count++;
    }

    int count;
}

class AtomicIntData
{
    AtomicIntData()
    {
        count = new AtomicInteger(0);
    }

    void inc() {
        for (int i = 0; i < 100; ++i)
            count.incrementAndGet();
    }

    AtomicInteger count;
}

class SafeIntData
{
    SafeIntData()
    {
        count = 0;
    }

    synchronized void inc() {
        for (int i = 0; i < 100; ++i)
            count++;
    }

    int count;
}

// for singleton implementation we can either use synchronized getInstance() method
// or use double locking. double locking is to implement getInstance method as
// normal method, check if instance is null, the enter synchronized block and then
// check if the instance is still null (as the privous value of instance may be stale)
// then do create the instance. But the instance may be still stale if it is not volatile (am I right?), so you should either use volatile or create the instance in the static initialization code (static code is thread safe). Please take a look at effective java.
public class CTest { //jj

    @Ignore
    public void test1() {
        final UnsafeIntData count = new UnsafeIntData();

        List<Runnable> r = new ArrayList();
        for (int i = 0; i < 1000; ++i) {
            r.add(new Runnable() {
                    public void run() {
                        count.inc();
                    }
                });
        }
        try {
            AssertConcurrency.assertConcurrent("failed to run concurrently", r, 5);
        } catch (final Throwable e) {
            System.out.println("Error failed" + e);
        }
        assertEquals("count should be 100000", 100000, count.count);
    }

    @Test
    public void test2() throws InterruptedException {
        final SafeIntData count = new SafeIntData();

        List<Runnable> r = new ArrayList();
        for (int i = 0; i < 1000; ++i) {
            r.add(new Runnable() {
                    public void run() {
                        count.inc();
                    }
                });
        }
        AssertConcurrency.assertConcurrent("failed to run concurrently", r, 5);
        assertEquals("count should be 100000", 100000, count.count);
    }

    @Test
    public void test3() {
        final AtomicIntData count = new AtomicIntData();

        List<Runnable> r = new ArrayList();
        for (int i = 0; i < 1000; ++i) {
            r.add(new Runnable() {
                    public void run() {
                        count.inc();
                    }
                });
        }
        try {
            AssertConcurrency.assertConcurrent("failed to run concurrently", r, 5);
        } catch (final Throwable e) {
            System.out.println("Error failed" + e);
        }
        assertEquals("count should be 100000", 100000, count.count.get());
    }

    @Test
    public void test4() {
        List<IpCheckable> r = new ArrayList();
        for (int i = 0; i < 1000; ++i) {
            r.add(new CheckIp());
        }

        Vector<Map<String, Integer> > vm = new Vector<Map<String, Integer> >();

        List<String> ls = new ArrayList();
        String[] s = {"163.152", "123.456", "192.111"};
        int[] ai = new int[3];
        // populate ls (input data) here
        Random ran = new Random();
        int size = s.length;
        for (int i = 0; i < 10000; ++i) {
            int index = ran.nextInt(size);
            ls.add(s[index]);
            ai[index]++;
        }
        assertEquals("total number of items shouls be same", 10000, ai[0] + ai[1] + ai[2]);
        assertEquals("total number of items shouls be same", 10000, ls.size());

        try {
            AssertConcurrency.assertConcurrent2("failed to run concurrently", r, 5, ls, vm);
        } catch (final Throwable e) {
            System.out.println("Error failed" + e);
        }
        assertEquals("the size of vm should be the same with the number of tasks", r.size(), vm.size());

        Map<String, Integer> result = new HashMap<String, Integer>();
        Map<String, Integer> exp = new HashMap<String, Integer>();
        for (int i = 0; i < s.length; ++i) {
            result.put(s[i], 0);
            exp.put(s[i], ai[i]);
        }

        int count = 0;
        for (Map<String, Integer> m : vm) {
            for (Map.Entry<String, Integer> e : m.entrySet()) {
                Integer i = result.get(e.getKey());
                result.put(e.getKey(), i + e.getValue());
                count += e.getValue();
            }
        }

        assertEquals("the size of elements should be the same with the number of result", 10000, count);

        for (String si: s) {
            assertEquals("the number of occurences should be same", result.get(si), exp.get(si));
            // System.out.println("the result is " + si + " : " + result.get(si));
        }
        System.out.println("Time spend in test 4 is " + (endTime - startTime));
    }

    // cache hit test with big synchronized block, fine grained synchronized block, and read-write lock.
    // add sortedset x = new treeset to test1.java file or here.
    // Hashtable, synchronizedMap, concurrentMap, concurrentHashMap
    // vector, copyonwritearraylist, copyonwritearrayset, synchronizedlist, synchronizedset
    // blockingqueue, concurrentlinkedqueue, priorityqueue
    // set, synchronizedSet, copyonwritearrayset
    // item tracker
    // file crawler
    // for producer/consumer pattern, work stealing (using deque) is a way to improve.
    // lock striping for concurrentMap
    @Test
    public void test5()
    {
    }

}

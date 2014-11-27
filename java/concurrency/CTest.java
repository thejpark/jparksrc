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


class UnsafeFactorizesss
{
    private final AtomicReference<BigInteger> lastNumber =
	new AtomicReference();
    private final AtomicReference<BigInteger[]> lastFactors =
	new AtomicReference();

}

public class CTest {

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
	    assertConcurrent("failed to run concurrently", r, 5);
	} catch (final Throwable e) {
	    System.out.println("Error failed" + e);
	}
	assertEquals("count should be 100000", 100000, count.count);
    }

    @Test
     public void test2() {
	final SafeIntData count = new SafeIntData();
	
	List<Runnable> r = new ArrayList();
	for (int i = 0; i < 1000; ++i) {
	    r.add(new Runnable() {
		    public void run() {
			count.inc();
		    }
		});
	}
	try {
	    assertConcurrent("failed to run concurrently", r, 5);
	} catch (final Throwable e) {
	    System.out.println("Error failed" + e);
	}
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
	    assertConcurrent("failed to run concurrently", r, 5);
	} catch (final Throwable e) {
	    System.out.println("Error failed" + e);
	}
	assertEquals("count should be 100000", 100000, count.count.get());
    }

    public static void assertConcurrent(final String message,
		final List<? extends Runnable> runnables,
		final int maxTimeoutSeconds) throws InterruptedException {
	final int numThreads = runnables.size();
	final List<Throwable> exceptions = Collections.synchronizedList(new ArrayList<Throwable>());
	final ExecutorService threadPool = Executors.newFixedThreadPool(numThreads);
	try {
            final CountDownLatch allExecutorThreadsReady = new CountDownLatch(numThreads);
            final CountDownLatch afterInitBlocker = new CountDownLatch(1);
            final CountDownLatch allDone = new CountDownLatch(numThreads);
            for (final Runnable submittedTestRunnable : runnables) {
		threadPool.submit(new Runnable() {
			public void run() {
			    allExecutorThreadsReady.countDown();
			    try {
				afterInitBlocker.await();
				submittedTestRunnable.run();
			    } catch (final Throwable e) {
				exceptions.add(e);
			    } finally {
				allDone.countDown();
			    }
			}
		    });
            }
            // wait until all threads are ready
            assertTrue("Timeout initializing threads! Perform long lasting initializations before passing runnables to assertConcurrent",
		       allExecutorThreadsReady.await(runnables.size() * 10, TimeUnit.MILLISECONDS));
            // start all test runners
            afterInitBlocker.countDown();
            assertTrue(message +" timeout! More than" + maxTimeoutSeconds + "seconds", allDone.await(maxTimeoutSeconds, TimeUnit.SECONDS));
	} finally {
            threadPool.shutdownNow();
	}
	assertTrue(message + "failed with exception(s)" + exceptions, exceptions.isEmpty());
    }
}

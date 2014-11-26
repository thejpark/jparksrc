package concurrency;

import static org.junit.Assert.*;
import org.junit.Test;
import org.junit.Ignore;
import org.junit.runner.RunWith;
import org.junit.runners.JUnit4;
import java.util.*;
import java.util.concurrent.*;
import java.lang.*;

/**
 * Tests for {@link Foo}.
 *
 * @author user@example.com (Jung Gyu Park)
 */
public class CTest {

    @Test
    public void test1() {

    }

    @Test
    public void test2() {

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

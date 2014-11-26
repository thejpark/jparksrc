package concurrency;

import static org.junit.Assert.assertEquals;
import org.junit.Test;
import org.junit.Ignore;
import org.junit.runner.RunWith;
import org.junit.runners.JUnit4;
import java.util.*;
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

    public static void assertConcurrent(final String message,
		final List<? extends Runnable> runnables,
		final int maxTimeoutSeconds) throws InterruptedException {
	final int numThreads = runnables.size();
	final List<Throwable> exceptions = Collections.synchronizedList(new ArrayList<Throwable>());
	final java.util.concurrent.ExecutorService threadPool = java.util.concurrent.Executors.newFixedThreadPool(numThreads);
	try {
            final java.util.concurrent.CountDownLatch allExecutorThreadsReady = new java.util.concurrent.CountDownLatch(numThreads);
            final java.util.concurrent.CountDownLatch afterInitBlocker = new java.util.concurrent.CountDownLatch(1);
            final java.util.concurrent.CountDownLatch allDone = new java.util.concurrent.CountDownLatch(numThreads);
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
            org.junit.Assert.assertTrue("Timeout initializing threads! Perform long lasting initializations before passing runnables to assertConcurrent",
		       allExecutorThreadsReady.await(runnables.size() * 10, java.util.concurrent.TimeUnit.MILLISECONDS));
            // start all test runners
            afterInitBlocker.countDown();
            org.junit.Assert.assertTrue(message +" timeout! More than" + maxTimeoutSeconds + "seconds", allDone.await(maxTimeoutSeconds, java.util.concurrent.TimeUnit.SECONDS));
	} finally {
            threadPool.shutdownNow();
	}
	org.junit.Assert.assertTrue(message + "failed with exception(s)" + exceptions, exceptions.isEmpty());
    }
}

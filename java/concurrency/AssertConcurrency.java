package concurrency;

import java.util.*;
import java.util.concurrent.*;
import java.lang.*;
import java.util.concurrent.atomic.*;
import static org.junit.Assert.*;

class AssertConcurrency {

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

    public static void assertConcurrent2(final String message,
                                         final List<? extends IpCheckable> runnables,
                                         final int maxTimeoutSeconds,
                                         final List<String> data,
                                         final Vector<Map<String, Integer> > output) throws InterruptedException {
        final int numThreads = runnables.size();
        final List<Throwable> exceptions = Collections.synchronizedList(new ArrayList<Throwable>());
        final ExecutorService threadPool = Executors.newFixedThreadPool(numThreads);
        try {
            final CountDownLatch allExecutorThreadsReady = new CountDownLatch(numThreads);
            final CountDownLatch afterInitBlocker = new CountDownLatch(1);
            final CountDownLatch allDone = new CountDownLatch(numThreads);
            final AtomicInteger index = new AtomicInteger(-1);
            for (final IpCheckable submittedTestRunnable : runnables) { //jj
                threadPool.submit(new Runnable() {
                        public void run() {
                            allExecutorThreadsReady.countDown();
                            try {
                                afterInitBlocker.await();
                                int i = index.incrementAndGet();
                                while (i < data.size()) {
                                    submittedTestRunnable.check(data.get(i));
                                    i = index.incrementAndGet();
                                }
                                submittedTestRunnable.emit(output);
                                submittedTestRunnable.clear();
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
            // start timer here if you want to get time spent for processing
            afterInitBlocker.countDown();
            // process data
            assertTrue(message +" timeout! More than" + maxTimeoutSeconds + "seconds", allDone.await(maxTimeoutSeconds, TimeUnit.SECONDS));
            // get time here if you want to get time spent for processing
        } finally {
            threadPool.shutdownNow();
        }
        assertTrue(message + "failed with exception(s)" + exceptions, exceptions.isEmpty());
    }
}

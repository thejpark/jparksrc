package barrier;

import java.util.concurrent.*;

class Solver {
    final int N;
    final float[][] data;
    final CyclicBarrier barrier;
    final CountDownLatch initBlocker;

    class Worker implements Runnable {
        int myRow;
        Worker(int row) { myRow = row; }
        public void run() {
            while (!done()) {
                processRow(myRow);

                try {
                    barrier.await();
                } catch (InterruptedException ex) {
                    return;
                } catch (BrokenBarrierException ex) {
                    return;
                }
            }
            initBlocker.countDown();
        }
    }

    public Solver(float[][] matrix) {
        data = matrix;
        N = matrix.length;
        initBlocker = new CountDownLatch(1);
        barrier = new CyclicBarrier(N,
                                    new Runnable() {
                                        public void run() {
                                            // mergeRows(...);
                                        }
                                    });
        for (int i = 0; i < N; ++i)
            new Thread(new Worker(i)).start();

        initBlocker.await();
    }

    private boolean done() {
        return true;
    }
}

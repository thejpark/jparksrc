package memoizer;

import java.util.concurrent.*;

class Memoizer<A, V> implements Computable<A, V> {

    private final ConcurrentMap<A, Future<V>> cache
        = new ConcurrentHashMap();
    private final Computable<A, V> c;

    Memoizer(Computable<A, V> c) {
        this.c = c;
    }

    public V compute(final A arg) throws InterruptedException {

        while (true) {
            Future<V> f = cache.get(arg);
            if (f == null) {

                Callable<V> e = new Callable() {
                        public V call() throws InterruptedException {
                            return c.compute(arg);
                        }
                    };
                FutureTask<V> ft = new FutureTask(e);
                f = cache.putIfAbsent(arg, ft);
                if (f == null) {
                    f = ft;
                    ft.run();
                }
            }

            try {
                return f.get();
            } catch (CancellationException ce) {
                cache.remove(arg, f);
            } catch (ExecutionException ee) {
                // throw launderThrowable(ee.getCause());
            }
        }

    }
}

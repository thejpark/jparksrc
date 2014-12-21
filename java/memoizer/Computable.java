package memoizer;

interface Computable<A, V> {
    V compute(A arg) throws InterruptedException;
}

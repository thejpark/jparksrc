package lockstrip;


class StripedMap {
    // Synchronization policy: buckets[n] guarded by locks[n%N_LOCKS]
    private static finnal int N_LOCKS = 16;
    private final Node[] buckets;
    private final Object[] locks;

    private static class Node {
	private int n;
    }

    StripedMap(int numBuckets) {
	buckets = new Node[numBuckets];
	locks = new Object[N_LOCKS];
	for (int i = 0; i < N_LOCKS; ++i)
	    locks[i] = new Object();
    }

    private final int hash(Object key) {
	return Math.abs(key.hashCode() % buckets.length);
    }

    Object get(Object key) {
	int hash = hash(key);
	synchronized (locks[hash % N_LOCKS]) {
	    for (Node m = buckets[hash]; m != null; m = m.next)
		if (m.key.equals(key))
		    return m.value;
	}
	return null;
    }

    void clear() {
	for (int i = 0; i < buckets.length; ++i) {
	    synchronized (locks[i % N_LOCKS]) {
		buckets[i] = null;
	    }
	}
    }
}
	   

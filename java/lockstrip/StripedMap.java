package lockstrip;


class StripedMap<K, V> {
    // Synchronization policy: buckets[n] guarded by locks[n%N_LOCKS]
    private static final int N_LOCKS = 16;
    private final Node[] buckets;
    private final Object[] locks;

    private class Node {
	K key;
        V value;
        Node next;
	Node(K key, V value) 
	{
	    next = null;
	    this.key = key;
	    this.value = value;
	}
    }

    StripedMap(int numBuckets) {
	buckets = new Node[numBuckets];
	locks = new Object[N_LOCKS];
	for (int i = 0; i < N_LOCKS; ++i)
	    locks[i] = new Object();
    }

    private final int hash(K key) {
	return Math.abs(key.hashCode() % buckets.length);
    }

    V get(K key) {
	int hash = hash(key);
	synchronized (locks[hash % N_LOCKS]) {
	    for (Node m = buckets[hash]; m != null; m = m.next)
		if (m.key.equals(key))
		    return m.value;
	}
	return null;
    }

    V put(K key, V value) {
	int hash = hash(key);
	synchronized (locks[hash % N_LOCKS]) {
	    Node tail;
	    for (Node m = buckets[hash]; m != null; m = m.next)
		tail = m;
		if (m.key.equals(key)) {
		    V old = m.value;
		    m.value = value;
		    return old;
		}

	    Node n = new Node(key, value);
	    if (tail == null) {
		bucket[hash] = n;
	    } else {
		tail->next = n;
		tail = n;
	    }
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

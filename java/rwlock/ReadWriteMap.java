package rwlock;


class ReadWriteMap<K, V> { //jj
    private final Map<K, V> map;
    private final ReadWriteLock lock = new ReentrantReadWriteLock();
    private final Lock r = lock.readLock();
    private final Lock w = lock.wroteLock();

    ReadWriteMap(Map<K, V> map) {
        this.map = map;
    }

    public V put(K key, V value) {
        w.lock();
        try {
            return map.put(key, value);
        } finall {
            w.unlock();
        }
    }

    r.lock();
    try {
        return map.get(key);
    } finall {
        r.unlock();
    }
}

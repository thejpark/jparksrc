// use flag to cancel already running task
class PrimeGenerator implements Runnable {
    private final List<BigInteger> primes = new ArrayList<BigInteger>();
    private volatile boolean cancelled;

    public void run() {
	BigInteger p = BigInteger.ONE;
	while (!cancelled) {
	    p = p.nextProbablePrime();
	    synchronized (this) {
		primes.add(p);
	    }
	}
    }

    public void cancel() {
	cancelled = true;
    }

    public synchronized List<BigInteger> get() {
	return new ArrayList(primes);
    }
}

// use interrupt to cancel already running task
// as above method may fail with blocking method

class PrimeProducer implements Runnable {
    private final BlockingQueue<BigInteger> queue;

    PrimeProducer(BlockingQueue<BigInteger> q) {
	queue = q;
    }

    public void run() {
	try {
	    BigInteger p = BigInteger.ONE;
	    while (!Thread.currentThread.isInterrupted()) {
		queue.put(p = p.nextProbablePrime());
		synchronized (this) {
		    primes.add(p);
		}
	    }
	} catch (InterruptedException e) {
	    // do something here to allow thread to exit
	}
    }

    public void cancel() {
	interrupt();
    }

}

package boundedbuffer;

import java.util.concurrent.Semaphore;

// Is this same with blocking queue?

class BoundedBuffer<E> {
    private final Semaphore availItems, availSpace;
    private final E[] items;
    private int putPosition = 0, takePosition = 0;
    
    BoundedBuffer(int capacity) {
	availSpace = new Semaphore(capacity);
	availItems = new Semaphore(0);
	items = (E[]) new Object[capacity];
    }

    public boolean isEmpty() {
	 return availItems.availablePermits() == 0;
    }

     public boolean isFull() {
	 return availSpace.availablePermits() == 0;
    }

     public void put(E e) throws InterruptedException {
	 availSpace.acquire();
	 doInsert(e);
	 availItems.release();
     }

     public E take() throws InterruptedException {
	 availItems.acquire();
	 E e = doExtract();
	 availSpace.release();
	 return e;
     }

     private synchronized void doInsert(E e) {
	     int i = putPosition;
	     items[i] = e;
	     putPosition = (++i == items.length)? 0  : i;
	 }

     private synchronized E doExtract() {
	     int i = takePosition;
	     E e = items[i];
	     items[i] = null;
	     takePosition = (++i == items.length)? 0  : i;
	     return e;
	 }

}

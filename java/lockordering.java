private static final Object tieLock = new Object();

public void transferMoney(final Account fromAcct,//jj
                          final Account toAcct,
                          final DollarAmount amout)
    throws InsufficientFundException {

    class Helper {
        public void transfer() {
            if (fromAcct.getBalance.compareTo(amout) < 0)
                throw new InsufficientFundException();
            else
                {
                    fromAcct.debit(amout);
                    toAcct.credit(amout);
                }

        }
    }

    int fromHash = System.identityHashCode(fromAcct);
    int toHash = System.identityHashCode(toAcct);


    if (fromHash < toHash) {
        synchronized(fromHash) {
            synchronized(toHash) {
                new Helper().transfer();
            }
        }
    }
    else if (fromHash > toHash) {
        synchronized(toHash) {
            synchronized(fromHash) {
                new Helper().transfer();
            }
        }
    }
    else {
        synchronized(tieHash) {
            synchronized(fromHash) {
                synchronized(toHash) {
                    new Helper().transfer();
                }
            }
        }
    }
}

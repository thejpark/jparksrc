package concurrency;

import java.util.*;

interface IpCheckable {
    public void check(String s);
    public void emit(Vector<Map<String, Integer> > vm);
    public void clear();
}


package concurrency;

import java.util.*;
import java.lang.*;

class CheckIp implements IpCheckable {
    CheckIp() {
        m = new HashMap();
    }

    public void check(String s) {
        Integer count = m.get(s);
        m.put(s, (count == null) ? 1 : count + 1);
        // System.out.println(s + " " + m.get(s));
    }

    public void emit(Vector<Map<String, Integer> > vm) {
        vm.add(new HashMap(m));
    }

    public void clear() {
        m.clear();
    }

    Map<String, Integer> m;
}


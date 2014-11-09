package mygraph;

import java.util.Map;
import java.lang.Math;
import java.util.HashMap;
import java.util.List;
import java.util.ArrayList;

class graph <T>
{
    static final int MAX = 100000;
    Map<T, List<Pair<T, Integer> > > node;
    Map<T, Integer> r;

    graph()
    {
	node = new HashMap<T, List<Pair<T, Integer> > >();
	r = new HashMap<T, Integer>();
    }

    void add(T from, T to, int arg)
    {
	r.put(from, MAX);
	r.put(to,  MAX);
	List<Pair<T, Integer> > l = node.get(from);
	if (l == null)
	    node.put(from, new ArrayList<Pair<T, Integer> >());
	node.get(from).add(new Pair(to, arg));
    }

    List<Pair<T, Integer> > adj(T from) {
	return node.get(from);
    }

    void dijkstra(T from) {
	List<Pair<T, Integer> > adjlist = adj(from);
	for (Pair<T, Integer> p : adjlist) {
	    r.put(p.getKey(), p.getValue());
	}

	List<T> s = new ArrayList();
	List<T> v = new ArrayList();

	s.add(from);

	for(Map.Entry<T, Integer> entry : r.entrySet()) {
	    if (entry.getKey() != from) {
		v.add(entry.getKey());
	    }
	}

	while (!v.isEmpty()) {
	    T m = from;
	    for (T t : v) {
		if (r.get(t) < r.get(m))
		    m = t;
	    }

	    System.out.println("Process node " + m);

	    s.add(m);
	    v.remove(m);

	    List<Pair<T, Integer> > adj_m = adj(m);

	    if (adj_m != null) {
		for (Pair<T, Integer> p : adj_m) {
		    r.put(p.getKey(), Math.min(r.get(p.getKey()),
					       r.get(m) + p.getValue()));
		}
	    }
	}

	printPath(from);
    }

    void printNode()
    {
	for (Map.Entry<T, List<Pair<T, Integer> > > entry : node.entrySet()) {
	    T from = entry.getKey();
	    System.out.println(from);
	    System.out.println("{");
	    for (Pair<T, Integer> p : entry.getValue()) {
		System.out.println(" (" + p.getKey() + ", " + p.getValue() + ") ");
	    }
	    System.out.println("}");

	}
    }

    private void printPath(T from)
    {
	for (Map.Entry<T, Integer> entry : r.entrySet()) {
	    T to = entry.getKey();
	    if (to == from)
		continue;
	    System.out.println(entry.getKey() + " : " + entry.getValue());
	}
    }

    public static void main(String[] args)
    {
	System.out.println("start");
	graph g = new graph<Integer>();

	g.add(1, 2, 10);
	g.add(1, 4, 30);
	g.add(1, 5, 100);
	g.add(2, 3, 50);
	g.add(3, 5, 10);
	g.add(4, 3, 20);
	g.add(4, 5, 60);
	g.dijkstra(1);
    }
}		

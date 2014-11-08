import java.util.Map;
import java.util.HashMap;
import java.util.List;
import java.util.ArrayList;

class Pair<K, V> {

    private K key;
    private V value;

    // Generic constructor
    public Pair(K key, V value) {
        this.key = key;
        this.value = value;
    }

    // Generic methods
    public void setKey(K key) { this.key = key; }
    public void setValue(V value) { this.value = value; }
    public K getKey()   { return key; }
    public V getValue() { return value; }
}

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

    void print()
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

	g.print();
    }
}

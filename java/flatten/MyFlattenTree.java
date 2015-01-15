package flatten;

import java.util.List;
import java.util.ArrayList;

public class MyFlattenTree<T> implements FlattenTree<T>
{
    // replace this with enum class? or singletone? this needs to be static class?
    class myfunc implements Function<T, List<T>>
    {
        public myfunc() {}
        public List<T> apply(T p) 
        {
	    List<T> r = new ArrayList();
            r.add(p);
            return r;
        }
    }

    class myfunc2 implements Function<Triple<Tree<T>>, List<T>>
    {
        public myfunc2() {}
        
        public List<T> apply(Triple<Tree<T>> p) 
        {
            List<T> r = new ArrayList();

            r.addAll(flattenInOrder(p.left()));
            r.addAll(flattenInOrder(p.middle()));
            r.addAll(flattenInOrder(p.right()));
            return r;
        }
    }
    
    private myfunc f1;
    private myfunc2 f2;

    MyFlattenTree() {
	f1 = new myfunc();
	f2 = new myfunc2();
    }

    public List<T> flattenInOrder(Tree<T> tree) 
    {
        if (tree == null)
	    return new ArrayList<T>();
        
        Either<T, Triple<Tree<T>>> n =  tree.get();

        if (n.isLeft()) {
            List<T> l = n.ifLeft(f1); 
            return l;
        } else {
            List<T> l = n.ifRight(f2);
            return l;
        }
    }
}

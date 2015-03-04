package flatten;


import static org.junit.Assert.assertEquals;
import org.junit.Test;
import org.junit.Ignore;
import org.junit.runner.RunWith;
import org.junit.runners.JUnit4;
import java.util.*;

/**
 * Tests for {@link Foo}.
 *
 * @author user@example.com (Jung Gyu Park)
 */
public class FooTest {

    @Test
    public void test1() {
	int[] a = {1, 5, 4, 9, 6};
        Tree<Integer> a1 = Tree.Leaf.leaf(a[1]);
        Tree<Integer> a2 = Tree.Leaf.leaf(a[2]);
        Tree<Integer> a3 = Tree.Leaf.leaf(a[3]);
        Tree<Integer> n = Tree.Node.tree(a1, a2, a3);
        Tree<Integer> l1 = Tree.Leaf.leaf(a[0]);
        Tree<Integer> l2 = Tree.Leaf.leaf(a[4]);
        Tree<Integer> t = Tree.Node.tree(l1, n, l2);
        MyFlattenTree<Integer> mt = new MyFlattenTree<Integer>();
        List<Integer> l = mt.flattenInOrder(t);
        Iterator<Integer> it = l.iterator();
	int i = 0;
        while(it.hasNext()) {
            int p = it.next();
	    org.junit.Assert.assertEquals("failure - not equal", a[i++], p);
        }
    }
    
    @Test
    public void test2() {
	int[] a = {1, 5, 4, 9, 6, 3};
        Tree<Integer> a1 = Tree.Leaf.leaf(a[1]);
        Tree<Integer> a2 = Tree.Leaf.leaf(a[2]);
        Tree<Integer> a3 = Tree.Leaf.leaf(a[3]);
	Tree<Integer> n = Tree.Node.tree(a1, a2, a3);
        Tree<Integer> l1 = Tree.Leaf.leaf(a[0]);
        Tree<Integer> l2 = Tree.Leaf.leaf(a[4]);
        Tree<Integer> t = Tree.Node.tree(l1, n, l2);
        t = Tree.Node.tree(t, Tree.Leaf.leaf(a[5]), null);
        MyFlattenTree<Integer> mt = new MyFlattenTree<Integer>();
        List<Integer> l = mt.flattenInOrder(t);
        Iterator<Integer> it = l.iterator();
	int i = 0;
        while(it.hasNext()) {
            int p = it.next();
	    org.junit.Assert.assertEquals("failure - not equal", a[i++], p);
        }
       
    }
}

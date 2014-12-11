//export CLASSPATH=~/wrk/jparksrc/java/hamcrest-core-1.3.jar:~/wrk/jparksrc/java/junit-4.12-beta-3.jar:$CLASSPATH
//java -cp .:./junit-4.12-beta-3.jar:./hamcrest-core-1.3.jar  org.junit.runner.JUnitCore findcommonancestor.FooTest
// how to run in windows cygwin?
 // java -classpath `cygpath -wp "/cygdrive/c/home/junggyup/wrk/jparksrc/java:/cygdrive/c/home/junggyup/wrk/jparksrc/java/hamcrest-core-1.3.jar:/cygdrive/c/home/junggyup/wrk/jparksrc/java/junit-4.12-beta-3.jar"` org.junit.runner.JUnitCore concurrency.CTestpackage concurrency;


package findcommonancestor;

import static org.junit.Assert.assertEquals;
import org.junit.Test;
import org.junit.Ignore;
import org.junit.runner.RunWith;
import org.junit.runners.JUnit4;
import java.util.*;

/**
 * Tests for {@link Foo}.
 *
 * @author user@example.com (John Doe)
 */
public class FooTest {

    @Test
    public void testFindParent() {
	Set<String> s = mfc.findParent("D", commits, parents);
	Set<String> r = new HashSet<String>();
	r.add("C");
	r.add("A");
	org.junit.Assert.assertEquals("failure - strings are not equal", r, s);
    }

    @Test
    public void testFindParent2() {
	Set<String> s = mfc.findParent("F", commits, parents);
	Set<String> r = new HashSet<String>();
	r.add("B");
	r.add("E");
	r.add("A");
	org.junit.Assert.assertEquals("failure - strings are not equal", r, s);
    }

    @Test
    public void testFindParent3() {
	Set<String> s = mfc.findParent("G", commits, parents);
	Set<String> r = new HashSet<String>();
	String[]t = {"A", "B", "C", "D", "E", "F"};
	for (String e: t)
	    r.add(e);
	org.junit.Assert.assertEquals("failure - strings are not equal", r, s);
    }

    @Test
    public void test1() {
	String s = mfc.findCommmonAncestor(commits, parents, "D", "F");
	org.junit.Assert.assertEquals("failure - strings are not equal", "A", s);
    }

    @Test
    public void test2() {
	String s = mfc.findCommmonAncestor(commits, parents, "E", "D");
	org.junit.Assert.assertEquals("failure - strings are not equal", "A", s);
    }

    @Test
    @Ignore
    public void thisIsIgnored() {
    }

    private MyFindCommonAncestor mfc = new MyFindCommonAncestor();
    private static String[] commits = {"G", "F", "E", "D", "C", "B", "A"};;
    private static String[][] parents = {
            {
                "F","D"
            },{"E"
            }, {"B"
            }, {"C"
            }, {"A"
            }, {"A"
            }, null
        };
}

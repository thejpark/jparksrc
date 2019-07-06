package findarray;


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
    public void test1() {
        int a[] = {4, 9, 3, 7, 8
        };
        int b[] = {3, 7
        };

        MyFindArray fa = new MyFindArray();
        int i = fa.findArray(a, b);
        org.junit.Assert.assertEquals("failure - not equal", 2, i);
    }

    @Test
    @Ignore
    public void thisIsIgnored() {
    }

}

package boundedbuffer;

import static org.junit.Assert.*;
import org.junit.Test;
import org.junit.Ignore;
import org.junit.runner.RunWith;
import org.junit.runners.JUnit4;

/**
 * Tests for {@link Foo}.
 *
 * @author user@example.com (Jung Gyu Park)
 */

public class BTest {

    @Test
    public void test1() {
	BoundedBuffer<Integer> bb = new BoundedBuffer(10);
	assertTrue(bb.isEmpty());
	assertFalse(bb.isFull());
    }

    @Test
    public void test2() throws InterruptedException {
	BoundedBuffer<Integer> bb = new BoundedBuffer(10);
	for (int i = 0; i < 10; ++i)
	    bb.put(i);
	assertTrue(bb.isFull());
	assertFalse(bb.isEmpty());
    }
}

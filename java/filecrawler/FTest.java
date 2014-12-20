package filecrawler;

import static org.junit.Assert.*;
import org.junit.Test;
import org.junit.Ignore;
import org.junit.runner.RunWith;
import org.junit.runners.JUnit4;
import java.util.*;
import java.util.concurrent.*;
import java.util.concurrent.atomic.*;
import java.io.File;
import java.io.FileFilter;


/**
 * Tests for {@link Foo}.
 *
 * @author user@example.com (Jung Gyu Park)
 */
public class FTest {
    final int BOUND = 1000;
    final int N_CONSUMERS = 5;

    @Test
    public void test1() {
	BlockingQueue<File> queue = new LinkedBlockingQueue(BOUND);
	FileFilter ft = new FileFilter() {
		public boolean accept (File pathname) {
		    return true;
		}
	    };

	File roots[] = (new File("/Users/jpark/wrk/jparksrc/java")).listFiles(ft);
	for (File root : roots)
	    new Thread(new FileCrawler(queue, ft, root)).start();
	for (int i = 0; i < N_CONSUMERS; ++i)
	    new Thread(new Indexer(queue)).start();
    }

}

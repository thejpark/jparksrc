package filecrawler;

import java.util.*;
import java.util.concurrent.*;
import java.io.File;

class Indexer implements Runnable { //jj
    private final BlockingQueue<File> queue;

    Indexer(BlockingQueue<File> q) {
        queue = q;
    }

    public void run() {
        try {
            while (true)
                indexFile(queue.take());
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    private void indexFile(File file) throws InterruptedException {
        System.out.println("indexing file" + file);
    }
}

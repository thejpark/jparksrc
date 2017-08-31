package filecrawler;

import java.util.*;
import java.util.concurrent.*;
import java.io.File;
import java.io.FileFilter;

class FileCrawler implements Runnable {
    private final BlockingQueue<File> fileQueue;
    private final FileFilter fileFilter;
    private final File file;

    FileCrawler(BlockingQueue<File> q, FileFilter ft, File f)  {
        fileQueue = q;
        file = f;
        fileFilter = ft;
    }

    public void run() {
        try {
            crawl(file);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    private void crawl(File root) throws InterruptedException {//jj
        File[] entries = root.listFiles(fileFilter);
        if (entries != null) {
            for (File entry : entries) {
                if (entry.isDirectory())
                    crawl(entry);
                else if (!alreadyIndexed(entry)) {
                    fileQueue.put(entry);
                }
            }
        }
    }

    private boolean alreadyIndexed(File entry) {
        return fileQueue.contains(entry);
    }
}



// file crawling request to server, and server respondes asynch, then how it will be?
// 1) single request and single response, with queue, after processing response and q is empty then it is done.
// 2) if single request thread and multiple response, then a blocking queue will be fine
// 3) if multiple request thread and multiple response, then deq and work stealing queue

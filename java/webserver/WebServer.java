package webserver;

import java.util.concurrent.*;

class WebServer { //jj
    // single thread
    public service1() throws IOException {
        ServerSocket s = new ServerSocket(80);
        while (true) {
            Socket conn = s.accept();
            handleRequest(conn);
        }
    }

    // thread per connection
    public service2() throws IOException {
        ServerSocket s = new ServerSocket(80);
        while (true) {
            final Socket conn = s.accept();
            Runnable task = new Runnable () {
                    public void run() {
                        handleRequest(conn);
                    }
                };
            new Thread(task).start();   
        }
    }

    // thread pool
    public service3() throws IOException {
        ServerSocket s = new ServerSocket(80);
        final int NTHREADS = 10;
        Executor ex = Executors.newFixedThreadPool(NTHREADS);
        while (true) {
            final Socket conn = s.accept();
            Runnable task = new Runnable () {
                    public void run() {
                        handleRequest(conn);
                    }
                };
            ex.execute(task);
        }
    }

}


class WebServer2 {

    final int NTHREADS;
    final ExecutorService ex;
    WebServer2() {
        NTHREADS = 10;
        ex = Executors.newFixedThreadPool(NTHREADS);
    }

    // thread pool
    public start() throws IOException {
        ServerSocket s = new ServerSocket(80);
        while (!ex.isShutdown()) {
            final Socket conn = s.accept();
            Runnable task = new Runnable () {
                    public void run() {
                        handleRequest(conn);
                    }
                };
            ex.submit(task);
            // ex.execute(task);
        }
    }

    public stop() {
        ex.shutdown();
    }

}

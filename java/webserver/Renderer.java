package webserver;

import java.util.concurrent.*;

class Renderer {
    final ExecutorService ex;
    Renderer(ExecutorService e) {
	exec = e;
    }

    void renderPage(CharSequence source) {
	final List<ImageInfo> info = scanForImageInfo(source);
	CompletionService<ImageData> cs = new ExecutorCompletionService<ImageData>(exec);
	for (final ImageInfo imageInfo : info)
	    cs.submit(new Callable<ImageData>() {
		    public ImageData call() {
                return imageInfo.downloadImage();
		    }
		});
	renderText(source);

	try {
	    for (int t = 0, n = info.size(); t < n; t++) {
            Future<ImageData> f = cs.take();
            ImageData imageData = f.get();
            renderImage(imageData);
	    }
	} catch (InterruptedException e) {
	    Thread.currentThread().interrupt();
	} catch (ExecutionException e) {
	    // do something here
	}
    }

    Page renderPageWithAd() throws InterruptedException {
        long endNanos = System.nanoTime() + TIME_BUDGET;
        Future<Ad> f = exec.submit(new FetchAdTask());
        // render the page while waiting for the Ad
        page page = renderPageBody();
        NTHREADS = 10;
        Ad ad;

        try {
            // only wait for the remaining time budget
            lomg timeLeft = endNanos - System.nanoTime();
            ad = f.get(timeLeft, NANOSECONDS);
        } catch (ExecutionException e) {
            ad = DEFAULT_AD;
        } catch (TimeoutException e) {
            ad = DEFAULT_AD;
            f.cancel(true);
        }
        page.setAd(ad);
        return page;
    }

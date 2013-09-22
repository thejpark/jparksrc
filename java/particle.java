import java.awt.Graphics;
import java.util.Random;
import java.applet.Applet;
import java.awt.Canvas;
import java.awt.Dimension;
import java.lang.System;



class Particle {
  protected int x;
  protected int y;
  protected final Random rng = new Random();
 
  public Particle(int initialX, int initialY) { 
    x = initialX;
    y = initialY;
  }

  public synchronized void move() {
    x += rng.nextInt(10) - 5;
    y += rng.nextInt(20) - 10;
  }

  public void draw(Graphics g) {
    int lx, ly;
    synchronized (this) { lx = x; ly = y; }
    g.drawRect(lx, ly, 10, 10);
  }
}

class ParticleCanvas extends Canvas {

  private Particle[] particles = new Particle[0]; 

  ParticleCanvas(int size) {
    setSize(new Dimension(size, size));
  }
 
  // Intended to be called by applet
  synchronized void setParticles(Particle[] ps) {
    if (ps == null) 
      throw new IllegalArgumentException("Cannot set null");

    particles = ps; 
  }

  protected synchronized Particle[] getParticles() { 
    return particles; 
  }
 
  public void paint(Graphics g) { // override Canvas.paint
    Particle[] ps = getParticles();

    for (int i = 0; i < ps.length; ++i) 
      ps[i].draw(g);

  }

}


class ParticleApplet extends Applet {

  protected Thread[] threads; // null when not running

  protected final ParticleCanvas canvas 
                                      = new ParticleCanvas(100);

  public void init() { add(canvas); }

  protected Thread makeThread(final Particle p) { // utility
    Runnable runloop = new Runnable() {
      public void run() {
        try {
          for(;;) {
            p.move();
            canvas.repaint();
            Thread.sleep(100); // 100msec is arbitrary
            System.out.println("thread wake up\n");
            
          }
        }
        catch (InterruptedException e) { return; }
      }
    };
    return new Thread(runloop);
  }

  public synchronized void start() {
    int n = 10; // just for demo

    if (threads == null) { // bypass if already started
      Particle[] particles = new Particle[n];
      for (int i = 0; i < n; ++i) 
        particles[i] = new Particle(50, 50);
      canvas.setParticles(particles);

      threads = new Thread[n];
      for (int i = 0; i < n; ++i) {
        threads[i] = makeThread(particles[i]);
        threads[i].start();
      }
    }
  }

  public synchronized void stop() {
    if (threads != null) { // bypass if already stopped
      for (int i = 0; i < threads.length; ++i)
        threads[i].interrupt();
      threads = null;
    }
  }
}

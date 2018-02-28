package ch14_concurrency;

import javax.sound.midi.Soundbank;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.concurrent.ThreadLocalRandom;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicLong;
import java.util.concurrent.atomic.LongAccumulator;
import java.util.concurrent.atomic.LongAdder;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

public class Cls_14_5_5 {
  public static void main(String[] args) {
    long id = nextNum.incrementAndGet(); // return ++i; atomic

    long oldVal, newVal, observed=0;
    do {
      oldVal = largest.get();
      newVal = Math.max(oldVal, observed);
    } while (!largest.compareAndSet(oldVal, newVal));
//     if (largest == oldVal) {
//       largest = newVal;
//       return true;
//     } else
//       return false;
    largest.updateAndGet(x -> Math.max(x, observed));

    final LongAdder adder = new LongAdder();
//    for ()
//      pool.submit( () - {
//        while (...) {
//          ...;
//          if (...)
//            adder.increment();
//      }
//      });
    long total = adder.sum();
    LongAccumulator adder2 = new LongAccumulator(Long::sum, 0);
    // In some thread ...
//    adder2.accumulate(val); // 对某个ai, ai = ai op val
  }
  private static volatile boolean done;
  public static boolean isDone() { return done;}
  public void setDone() { done = true;}
  // 不能提供原子性 比如 done = !done;
  // 原子性 java.util.concurrent.atomic

  public static AtomicLong nextNum = new AtomicLong();
  public static AtomicLong largest = new AtomicLong();

  // 线程局部变量 创建
  public static final ThreadLocal<SimpleDateFormat> dataFormat
          = ThreadLocal.withInitial(() -> new SimpleDateFormat("yyyy-MM-dd"));
  public static void f1() {
    // 首次 get 会调用 InitialValue，之后 get返回属于当前线程的那个实例
    dataFormat.get().format(new Date());
//    int random = ThreadLocalRandom.current().nextInt(upperBound);
  }

  public static void timeout() {
    Lock lk = new ReentrantLock();
    if (lk.tryLock()) {
//      lk.tryLock(10, TimeUnit.SECONDS);
//      TimeUnit.MILLISECONDS, TimeUnit.MICROSECONDS, TimeUnit.NANOSECONDS
      // now the thread owns the lock
      try { }
      finally { lk.unlock();}
    } else
      System.out.println("do sth else");
  }
  public static void rw_lock() {
    ReentrantReadWriteLock rwl = new ReentrantReadWriteLock();
    Lock rlock = rwl.readLock();
    Lock wlock = rwl.writeLock();
    // 读写操作
    try {
//      rlock.lockInterruptibly();
//      wlock.lockInterruptibly();
    } finally {
      rlock.unlock();
//      wlock.unlock();
    }
  }
}

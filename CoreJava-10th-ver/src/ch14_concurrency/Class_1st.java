package ch14_concurrency;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Class_1st {
  public static void main(String[] args) {
//    parallel_1();
    parallel_2();
  }

  private static int cnt = 0;
  private static final long DELAY = 1000;

  public static void parallel_1() {
    Runnable r = () -> {
      try {
        while (cnt < 8) {
          System.out.println("cnt = " + cnt);
          ++cnt;
          Thread.sleep(DELAY);
        }
      } catch (InterruptedException e) {

      } finally {
        System.out.println("interrupted");
        // cleanup, if required
      }
    };
    Thread t = new Thread(r);
    t.start();
    try {
      Thread.sleep(DELAY);
      Thread.sleep(DELAY);
      Thread.sleep(DELAY);
    } catch (InterruptedException e) {

    }
    t.interrupt();
  }

  public static void parallel_2() {
    Bank bank = new Bank(8, 100);
//    System.out.println(bank.getTotalBalance());

    double MAX_AMOUNT = 100 * 8;

//    int toAccount = (int) (bank.getSize() * Math.random());
//    int fromAc = 8 - toAccount;
//    double amount = MAX_AMOUNT * Math.random();
//    bank.xfer(fromAc, toAccount, amount);

    Runnable r = () -> {
      try {
        while (true) {
          int toAccount = (int) (bank.getSize() * Math.random());
          int fromAc = 8 - 1 - toAccount;
          double amount = MAX_AMOUNT * Math.random();
          bank.xfer(fromAc, toAccount, amount);
          Thread.sleep(300);
        }
      } catch (InterruptedException e) {
      }
    };
//    Thread t = new Thread(r);
    List<Thread> threadList = new ArrayList<>(3); // capacity
//    Arrays.fill(threadList, new Thread(r));
    threadList.add(new Thread(r));
    threadList.add(new Thread(r));
    threadList.add(new Thread(r));
//    System.out.println(threadList.size());
//    Collections.fill(threadList, new Thread(r));
    threadList.forEach(t -> t.start());
    threadList.forEach(t -> System.out.println(t.getId() + " : " + t.getState()));
//    t.start();
    try {
      Thread.sleep(3000);
    } catch (InterruptedException e) {
    } finally {
      threadList.forEach(t -> t.interrupt());
      System.out.println("end");
    }
  }
}

class Bank {
  private Lock bLock;
  private Condition enoughFunds;

  private double[] accounts;
  private int size = 8;

  public Bank(int aSize, double perAccount) {
    size = aSize;
    accounts = new double[size];
    Arrays.fill(accounts, perAccount);
    bLock = new ReentrantLock();
    enoughFunds = bLock.newCondition();
//    bLock.unlock();
  }

  public double getTotalBalance() {
    double sum = 0.0;
//    Arrays.asList(account).forEach(val -> {sum += val});
    for (double e : accounts)
      sum += e;
    return sum;
  }

  public void xfer(int from, int to, double amount)
          throws InterruptedException {
//    bLock.lock(); // uninterruptible
//    System.out.println("locked");

    try {
      bLock.lockInterruptibly(); // 会 throw exception
      System.out.println(Thread.currentThread());
      while (accounts[from] < amount) {
        enoughFunds.await(); // mutex lock
      }
      accounts[from] -= amount;
      System.out.printf("%10.2f from %d to %d ", amount, from, to);
      accounts[to] += amount;
      // wakeup other waiting thread
      enoughFunds.signalAll();
      System.out.printf(" total balance: %10.2f%n", getTotalBalance());
    } finally {
      bLock.unlock();
//      System.out.println("unlocked");
    }
  }

  public synchronized void xfer2(int from, int to, double amount)
          throws InterruptedException {
    while (accounts[from] < amount)
      wait();
    accounts[from] -= amount;
    accounts[to] += amount;
    notify();
  }
  // 静态方法也可以，同一时刻只执行一个 synchronized

  public int getSize() {
    return size;
  }
}
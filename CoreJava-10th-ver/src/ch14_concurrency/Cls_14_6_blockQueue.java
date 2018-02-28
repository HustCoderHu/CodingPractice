package ch14_concurrency;

import java.io.File;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.concurrent.*;

public class Cls_14_6_blockQueue {
  private static final int FILE_QUEUE_SZ = 10;
  private static final int SEARCH_THREAD = 100;
  private static final File DUMMY = new File("");
  private static BlockingQueue<File> q = new ArrayBlockingQueue<>(FILE_QUEUE_SZ);
//  ArrayBlockingQueue<String>(int capacity) 循环数组实现
//  LinkedBlockingQueue， and Deque  链表实现
  // 可以带一个 int capacity 指定容量

//  PriorityBlockingQueue() (int initialCapacity) (int, Comparator<? super E>comparator)
  // 无边界，初始容量默认 11
  // comp 比较器， 堆实现

  public static void func() throws InterruptedException {
    File f;
    q.put(new File("aaa"));
    f = q.take(); // 阻塞方法
    // add, remove, element 异常
    // 多线程用 offer, poll, peek 无异常，返回值判断


    f.isDirectory();
    File[] files = f.listFiles();
    while (q.isEmpty())

    for (File af : files) {

    }

  }
//  Thread<>
  public static void main(String[] args) {

  }
}
package ch9_jihe;

import java.time.LocalDate;
import java.util.*;

public class Class_9_2 {
  public static void main(String[] args) {
    Class_9_2 cont = new Class_9_2();
//    cont.linkedList();
//    cont.hashset();
//    cont.treeset();
    cont.prioQueue();
  }
  public void linkedList() {
    List<String> staff = new LinkedList<>();
    staff.add("Amy"); // add to tail
    staff.add("Bob");
    staff.add("Carl");
    Iterator iter = staff.iterator();
    String first = (String)iter.next();
    String second = (String)iter.next();
//    iter.remove(); // remove last visited element

    ListIterator<String> iter2 = staff.listIterator();
    iter2.next(); // skip past first "Amy"
    iter2.add("Juliet"); // Juliet lies between "Amy" and "Bob"
    System.out.println(staff.toString());

    iter2 = staff.listIterator();
    String oldVal = iter2.next();
    iter2.set("Alice"); // "Amy" -> "Alice"

    System.out.println(staff.toString());
  }
  // Vector 有同步开销，多线程时用
  // 单线程用 ArrayList

  public void hashset() {
    Set<String> words = new HashSet<>();
    // 指定容量(bucket 数)，默认16 2^n
//    Set<String> words = new HashSet<>(10);
    words.add("a");
    words.add("a");
    words.add("b");
    words.add("b");
    words.add("c");

    Iterator<String> iter = words.iterator();
    while (iter.hasNext()) {
      System.out.println(iter.next());
    }
    // a b c
  }

  public void treeset() {
    SortedSet<String> sorter = new TreeSet<>();
    sorter.add("Bob");
    sorter.add("Amy");
    sorter.add("Carl");
    for (String s : sorter) {
      System.out.println(s);
    }
  }

  public void queue() {
    // Queue
    // 1 boolean add (E element)
    // 2 boolean offer(E element)
    // 如果满了， 1 异常，2 false
    // E remove() 异常
    // E poll()   null

    // Dequeue 双端
    // addFirst, addLast
    // offerFirst, offerLast
    // removeFirst removeLast
    // pollFirst, pollLast
    // E getFirst(), getLast() 异常
    // E peekFirst(), peekLast()
  }

  public void prioQueue() {
    // 堆，根最小
    // 典型场景 任务调度
    PriorityQueue<LocalDate> pq = new PriorityQueue<>();
    pq.add(LocalDate.of(1906, 12, 9));
    pq.add(LocalDate.of(1815, 12, 10));
    pq.add(LocalDate.of(1903, 12, 3));
    pq.add(LocalDate.of(1910, 6, 22));
    System.out.println("Iterating over elements");
    for (LocalDate d : pq) {
      System.out.println(d);
    }
    System.out.println("removing elements");
    while(!pq.isEmpty())
      System.out.println(pq.remove());
  }
}

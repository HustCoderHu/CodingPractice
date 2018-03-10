package ch8_generics;

import java.io.Serializable;
import java.util.ArrayList;

// 看作普通类的工厂
// 类似 C++ 的模板类
public class Pair<T> {
  // 自动提供原始类型， 擦除类型变量 并替换为限定类型(无限定的变量用 Object)
  // 结果是普通类
  // 相比C++模板区别大， C++ 中每个模板的实例化产生不同的类型，
  // 这一现象称为 "模板代码膨胀"， Java 不存在这个问题的困扰

  // Java 泛型转换的事实
  // 1 虚拟机中没有泛型，只有普通的类和方法
  // 2 所有的类型都用它们的限定类型替换
  // 3 桥方法被合成来保持多台
  // 4 为保持类型安全性，必要时插入强制类型转换
  public static void main(String[] args) {
    // 不能创建参数化类型的数组
//    Pair<String>[] table = new Pair<String>[10]; // error
    ArrayList<Pair<String>> pairList = new ArrayList<>();
  }

  private T first;
  private T second;

  public Pair() {
    first = null;
    second = null;
  }

  public Pair(T first, T second) {
    this.first = first;
    this.second = second;
  }

  public T getFirst() {
    return first;
  }

  public T getSecond() {
    return second;
  }

  public void setFirst(T first) {
    this.first = first;
  }

  public void setSecond(T second) {
    this.second = second;
  }
}

// 使用两种类型
class Pair2<T, U> {
}

class ArrayAlg {
  public static void main(String[] args) {
    String mid = ArrayAlg.<String>getMid("John", "Q.", "Public");
    System.out.println("mid = " + mid);
  }
  // 泛型方法 可以定义在普通类中
  public static <T> T getMid(T... a) {
    return a[a.length / 2];
  }


  // 使用 extends 而不是 implements 虽然Comparable是接口
  // 记法 <T extends BoundingType> 表示子类型 ，可以说类也可以接口
  // T extends Comparable & Serializable

  //  public static <T> T min(T[] a) { // almost correct
  // 类型在前 接口在后
//  public static <T extends Comparable> T min(T[] a) {
  public static <T extends Comparable<? super T>> T min(T[] a) {
    if (a == null || a.length == 0)
      return null;
    T smallest = a[0];
//    smallest.compareTo(? super T);
    for (int i = 1; i < a.length; i++) {
      if (smallest.compareTo(a[i]) > 0)
        smallest = a[i];
    }

    return smallest;
  }
}

class Interval<T extends Comparable & Serializable> implements Serializable {
  private T lower;
  private T upper;

  public Interval(T first, T second) {
    if (first.compareTo(second) <= 0) {
      lower = first;
      upper = second;
    } else {
      lower = second;
      upper = first;
    }
  }
}

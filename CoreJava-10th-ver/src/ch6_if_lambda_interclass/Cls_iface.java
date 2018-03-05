package ch6_if_lambda_interclass;

import java.nio.file.FileSystem;
import java.nio.file.FileSystems;
import java.util.Arrays;
import java.util.Comparator;

public class Cls_iface {
  public static void main(String[] args) {
  }
}

interface Comparable<T> {
  int compareTo(T other); // 默认 public
  // 不能有实例域
}

class Employee implements Comparable<Employee> {
  private double salary = 400.0;

  @Override
  public int compareTo(Employee other) {
    return Double.compare(salary, other.salary);
  }
}

interface Moveable {
  void move(double x, double y);
}

interface Powered extends Moveable {
  double milesPerGallon();
  double SPEED_LIMIT = 95; // a public static final constant  自动
}

// SE 8
// 就不需要伴随类 Paths 了
//interface Path {
//  public static Path get(String first, String... more) {
//    return FileSystems.getDefault().getPath(first, more);
//  }
//}

interface Collection {
  int size();
  default boolean isEmpty() { // 如果实现类没有覆盖，
    // 就执行这里的 default
    return size() == 0;
  }
}

// 一个接口 default ，另一个super或者接口定义同样的方法
// 1 父类优先
// 2 接口冲突，必须覆盖
interface Named {
  default String getName() {
    return getClass().getName() + "_" + hashCode();
  }
}

interface Person {
  String getName();
}

class Student implements Person, Named {
  String name;
  @Override
  public String getName() {
    return name;
  }
}

// string 可以排序，因为实现了 Comaparable<String>
class lenComparator implements Comparator<String> {
  @Override
  public int compare(String o1, String o2) {
    return o1.length() - o2.length();
  }
}

class test2 {
  public static void main(String[] args) {
    Comparator<String> comp = new lenComparator();
    String[] friends = {"Peter", "Paul", "Mary"};
    Arrays.sort(friends, comp);

    // 数组类型都有一个public的clone，而不是protected
    int[] luckyNum = {2, 3, 5, 7, 11, 13};
    int[] cloned = luckyNum.clone();
    cloned[5] = 12;
    // 卷II 第2章 串行化 实现克隆
  }
}
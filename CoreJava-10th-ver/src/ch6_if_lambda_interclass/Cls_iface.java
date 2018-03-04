package ch6_if_lambda_interclass;

import java.nio.file.FileSystem;
import java.nio.file.FileSystems;

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
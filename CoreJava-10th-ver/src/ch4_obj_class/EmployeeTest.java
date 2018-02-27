package ch4_obj_class; // 类似 namespace
//package com.horstmann,corejava;
// import 类似 using
import java.text.NumberFormat;
import java.time.LocalDate;
import java.util.Random;
import static java.lang.Math.*;

//import static java.lang.Math.pow;
//import static java.lang.Math.sqrt;

// 文件名必须和 public 类匹配
// 只能有一个 public，私有类数量不限
public class EmployeeTest {
  public static void main(String[] args) {
    // fill the staff array with 3 employee objects
    Employee[] staff = new Employee[3];
    staff[0] = new Employee("Carl Cracker", 75000, 1987, 12, 15);
    staff[1] = new Employee("Harry Hacker", 50000, 1989, 10, 1);
    staff[2] = new Employee("Tony Tester", 40000, 1990, 3, 15);

    // raise everyone's salary by 5%
    for (Employee e : staff)
      e.raiseSalary(5);

    // print out info about all
    for (Employee e : staff)
      System.out.println("namne= " + e.getName() + ", salary= " + e.getSalary()
        + ", hireDay= " + e.getHireDay());

    int x = 3;
    int y = 4;
    double z = sqrt(pow(x, 2) + pow(y, 2));
    System.out.println("z = " + z);
  }
  public static void factoryMethod() {
    NumberFormat curFormatter = NumberFormat.getCurrencyInstance();
    NumberFormat percentFormatter = NumberFormat.getPercentInstance();
    double x = 0.1;
    System.out.println(curFormatter.format(x));
    System.out.println(percentFormatter.format(x));
  }
}

class Employee { // 同一包中的其他类可以访问
//public class Employee {
  private final String name;
  private double salary = 10000; // 比如基本工资 c++ 不能这样， 要用初始化列表
  private LocalDate hireDay;
  // 静态域
  private static int nextId = 1;
  private int id = assignId(); //
  public static final double PI = 3.1415926;
//  System.out.println(Employee.PI);

  // 静态初始化 block, 类第一次加载时执行
  static {
    Random gen = new Random();
    nextId = gen.nextInt(); // nextInt(n) 返回1个 0 ~ n-1 随机数
  }

  public Employee(double s) {
    this("Employee #" + nextId, s); // 调用了下面的构造函数
    // 可以集中公共的代码部分
    ++nextId;
  }

  public Employee(String str, double s) {
    name = str;
  }

  public Employee(String n, double s, int year, int month, int day) {
    name = n;
    salary = s;
    hireDay = LocalDate.of(year, month, day);
  }
  public String getName() {
    return name;
  }
  public double getSalary() {
    return salary;
  }
  public LocalDate getHireDay() {
    return hireDay;
//    hireDay.clone(); // 返回可变数据域的副本
  }
  public void raiseSalary(double byPercent) {
    double raise = salary * byPercent / 100;
    salary += raise;
  }
  public static int getNextId() {
    return nextId;
  }
  private static int assignId() {
    int r = nextId;
    ++nextId;
    return r;
  }
  // int n = Employee.getNextId();
}

// call by value 按值调用
// 方法得到的是参数值的副本

// 域与局部变量区别，域 默认值 0, false, null
package ch5_inheritance;

public class Cls_5_1 {
  public static void main(String[] args) {
    Manager boss = new Manager("BOSS", 300.0);
    Employee[] staff = new Employee[3];
    staff[0] = boss;

//    boss = staff[1]; // runtime Error ClassCastException
    if (staff[1] instanceof Manager) {
      boss = (Manager)staff[1];
    }
    // C++
//    Manager *boss = dynamic_cast<Manager*>(staff[1]);

    Person[] people = new Person[2];
    people[0] = new Employee("Amy", 4000.0);
    people[1] = new Student("Bob", "CS");

    for (Person p : people)
      System.out.println(p.getName() + ", " + p.getDescription());
  }
}

// protected 本包和所有子类可见
// default 本包可见

class Manager extends Employee {
  private double bonus = 0.0;
  public Manager(String n, double s) {
    super(n, s);
    // C++ 中用初始化列表 : Employee(s)
  }
  @Override
  public double getSalary() {
    return super.getSalary() + bonus;
  }

  public void setBonus(double bonus) {
    this.bonus = bonus;
  }
  // 重载解析，方法的名字和参数列表 -> 方法的签名
  // 返回类型不是签名的部分
  // private static final 方法或者构造器，静态绑定
  // 类 方法表， C++ 虚函数表
  // override, super 方法是 public，则sub也要public

  // final 类 禁止继承， 域非final
  // final 方法 禁止覆盖
}

class Employee extends Person{
  private double salary;

  public Employee(String n, double s) {
    super(n);
    salary = s;
  }
  public double getSalary() {
    return salary;
  }
  @Override
  public String getDescription() {
    return "this employee salary is " + salary;
  }
}

// 不能被实例化，即使不含 抽象方法 也可以抽象类
abstract class Person { // 如果下面 abs 类也必须 abs
  private String name;
  public Person(String n) {
    name = n;
  }
  public abstract String getDescription();
  // 尽量放通用方法
  public String getName() {
    return name;
  }
}
// C++ virtual func()=0 纯虚函数 抽象类

class Student extends Person {
  String major ="";
  public Student(String n, String m) {
    super(n);
    major = m;
  }
  @Override
  public String getDescription() {
    return "this student majoring in " + major;
  }
}
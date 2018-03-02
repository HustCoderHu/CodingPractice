package ch5_inheritance;

import java.util.ArrayList;

public class Cls_5_3_TarrayList {
  public static void main(String[] args) {
    int initialCapacity = 10;
    ArrayList<Employee> staff = new ArrayList<>(initialCapacity);
    // similar to C++ vector<>.reserve(initCapacity);
    staff.ensureCapacity(10); // minCapacity
    staff.add(new Employee("Amy", 400.0));
    // add 满时，创建更大的数组, 并cp过去
//    List<Employee> st2 = new ArrayList<>(); // List 没有 ensureCapacity
    staff.size(); // 等价 int[].length
    staff.trimToSize(); // 存储容量削减到当前size()

    // C++ vector a=b 赋值会构造长度为b.len的a
    // Java则只是引用

    staff.get(0);
    staff.set(1, staff.get(2));
  }

  public static void _5_4() {
    // 基本类型有对应的类， 称为 wrapper，不可变
    // final 不可继承
    ArrayList<Integer> l = new ArrayList<>();
    // 效率远低于 int 适合小型集合
    // 自动装箱 autoboxing
    l.add(3);
//    l.add(Integer.valueOf(3));
    // 自动拆箱
    int n = l.get(0);
    n = l.get(0).intValue();

    // 算数表达式 拆 and 装
    Integer m = 3;
    ++m;

    // boolean, byte, char <= 127
    // -128 ~ 127 的 short, int 重复使用相同对象
    // 所以下面为 true
    Integer a = 100;
    Integer b = 100;
    Integer c = 130;
    Integer d = 130;
    boolean _true = a == b;
    boolean _false = c == d;

    // 编译器插入必要的方法调用，JVM只是执行
    // atoi
    String s = "123";
    int x = Integer.parseInt(s); // static method
    // parseInt(s, 进制)
    // 其他类型类似

    double m2 = max(3.1, 30.3, -5);
  }

  public static double max(double...values) {
    double largest = Double.NEGATIVE_INFINITY;
    for (double v : values)
      if (v > largest)
        largest = v;
    return largest;
  }

  public static void cls_enum() {
    Size.SMALL.toString(); // "SMALL"
    // 逆方法
    Size s = Enum.valueOf(Size.class, "SMALL");
    Size[] values = Size.values(); // 包含所有
    Size.MEDIUM.ordinal(); // 返回位置 1
  }
}

enum Size { SMALL, MEDIUM, LARGE, EXTRA_LARGE }

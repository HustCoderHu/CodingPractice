package ch5_inheritance;

import java.util.Arrays;
import java.util.Objects;

public class Cls_5_2_Object {
  public static void main(String[] args) {
    // equals 方法
    Object obj = new Employee("Amy", 300.0);
    Employee e = (Employee) obj;
    int[] a = new int[3];
    int[] arr = Arrays.copyOf(a, a.length * 2);
    // Object, int, long, short, char, byte, boolean, float, double
    Arrays.equals(a, arr);
    Objects.equals(obj, e); // a.equals(b)
//    Arrays arr = new
    // Object:
    //   Class getClass()

    // Class:
    //   String getName()

    // hashCode 方法
    String s = "ok";
    StringBuilder sb = new StringBuilder(s);
    String t = new String("ok");
    StringBuilder tb = new StringBuilder(t);
    System.out.println(s.hashCode() + " " + sb.hashCode());
    System.out.println(t.hashCode() + " " + tb.hashCode());
    // 3548 1595212853
    // 3548 1134712904
    // String 的 hashCode 根据其内容计算出 如下 # 1
    // StringBuilder 没有定义 hashCode 默认使用 super Object 的 hashCode()

    // null 安全
    int hashcode = 2 * Objects.hashCode(obj)
            + 3 * Objects.hashCode(e);
    // better
    int hc2 = Objects.hash(obj, e);

    // toString 方法
    float f = 3.14f; // 3.14 double
    String msg = "the num is " + f; // automatically invokes toString()
    // f 可以是其他任何类型
    // Object 类的 toString() 返回类名和 hashcode
    // 如果这个类没有覆盖 toString()
    // 建议自定义类中增加 toString
  }
}

// 默认 super 是 Object
// equals
// 1 自反性 x!=null, x.equals(x) == true
// 2 对称性 x.equals(y) == y.equals(x)
// 3 传递性 x.equal(y) and y.equals(z) -> x.equals(z)
// 4 一致性 x, y引用对象没有变化, x.equals(y) 结果不变
// 5 x!=null x.equals(null) == false

// # 1
//  public int hashCode() {
//    int h = hash;
//    if (h == 0 && value.length > 0) {
//      char val[] = value;
//
//      for (int i = 0; i < value.length; i++) {
//        h = 31 * h + val[i];
//      }
//      hash = h;
//    }
//    return h;
//  }

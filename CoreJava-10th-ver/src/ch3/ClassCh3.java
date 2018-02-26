package ch3;

import java.io.PrintWriter;
import java.math.BigDecimal;
import java.math.BigInteger;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.Scanner;

public class ClassCh3 {
  public static void main(String[] args) {
    ClassCh3 ch = new ClassCh3();
//    ch._3_1();
//    ch._3_4();
//    ch._3_5();
//    ch._3_6();
//    ch._3_7();
//    ch._3_8();
//    ch._3_9();
    ch._3_10();
  }
  public void _3_1() {
    System.out.println("we will not use 'hello, world!'");
  }
  public void _3_3() {
//    int x;
//    if (Double.isNaN(x)) {// check whether x is "not a number"
//    }
  }
  public void _3_4() {
    int aaa;
//    System.out.println(aaa); // var not initialized
    final int bbb = 4;
//    bbb = 5; // 无法分配
  }
  // 类常量
  public static final double CM_PER_INCH = 2.54;

  enum Size {SMALL, MEDIUM, LARGE, EXTRA_LARGE };
  public void _3_5() {
    double x = 4;
    double y = Math.sqrt(x);
    System.out.println(y); // 2
    double z = Math.pow(y, 3);
    System.out.println(z); // 8

    int n = 123456789;
    float f = n;
    System.out.println(f); // 1.23456792E8

    x = 9.997;
    int nx = (int)x; // 9
    nx = (int)Math.round(x); // 10

    // c++ 注释
    boolean b = false;
    int inta = b? 1 : 0;

//    enum Size{SMALL, MEDIUM, LARGE, EXTRA_LARGE }; // must not be local
    Size sz = Size.MEDIUM;
  }
  public void _3_6() {
    String greeting = "hello";
    String s = greeting.substring(0, 3); // hel
    // 拼接 +
//    System.out.println(s);
    // 字符串不可变
    String stra = "Hello";
    stra.equals(greeting); // false
    stra.equalsIgnoreCase(greeting); // true

    if (stra.length() == 0)
      System.out.println("len 0");
    if (stra != null && stra.length() != 0)
      System.out.println("len != 0");

    // 高效构建字符串
    StringBuilder builder = new StringBuilder();
    builder.append('a');
    builder.append("str");
    String completedStr = builder.toString();
  }
  public void _3_7() {
//    Scanner in = new Scanner(System.in);
//    System.out.println("your name plz");
//    String name = in.nextLine();
//    String firstName = in.next();
//    System.out.println("your age plz");
//    int age = in.nextInt(); // in.nextDouble()
    // all above need jave.util.*, import it

    // 读文件
//    Scanner in2 = new Scanner(Paths.get("ClassCh3.java"));
    // 写文件
//    PrintWriter out = new PrintWriter("myfile.txt");
//    out.print(); out.println(); out.printf();
    // 当前路径
    String dir = System.getProperty("user.dir");
    System.out.println(dir);
  }

  public void _3_8() {
//     break label 替代 goto
    int i = 0;
    read_data:
    while(true) {
      for(; i < 3; ++i) {
        if (i%2 == 0)
          break read_data; // 未定义的标签
      }
    }
//    read_data: // break 往后 未定义的标签
    System.out.println("i = " + i);
  }
  public void _3_9() {
    // 大数值
    BigInteger a = BigInteger.valueOf(100);
    BigInteger b = BigInteger.valueOf(200);
    BigInteger c = a.add(b);
    BigInteger d = c.multiply(a);
    // subtract mod compareTo
//    BigDecimal divide
// valueOf(long x, int scale) x/ 10^scale
    BigDecimal aaa = BigDecimal.valueOf(3, 3);
    System.out.println("aaa = " + aaa);
  }
  public void _3_10() {
    int[] a = new int[4]; // 长度可变
    String[] str = new String[3];
    int lena = a.length;
    System.out.println("lena = " + lena);
    for (int i = 0; i < lena; ++i) {
      a[i] = i;
    }
    for (int i : a) {
      System.out.println("i = " + i);
    }

    // 初始化
    int[] smallPrimes = {2, 3, 5, 7, 11, 13};
    // 数组复制
    int[] newArray = smallPrimes; // 同一数组
    int[] copied = Arrays.copyOf(smallPrimes, smallPrimes.length);
    // 长度 截断 or 补0

    // main 参数 args 从0开始，不包括程序名

    Arrays.sort(smallPrimes);
    System.out.println(Arrays.toString(smallPrimes)); // small -> large

    // 二维数组
    double[][] erwei = new double[2][3];
    System.out.println(Arrays.deepToString(erwei));

    // 交换二维数组的两行
    int i = 0;
    double[] tmp = erwei[i];
    erwei[i] = erwei[i + 1];
    erwei[i + i] = tmp;

  }


}

public class Q11 {
  // 给定一个double类型的浮点数base和int类型的整数exponent。求base的exponent次方。
  public static void main(String[] args) {
    System.out.println(Power(2, -4));
    System.out.println(Power(2, 4));
    System.out.println(Power(2, 3));
//    System.out.println(Power(2, 0));
//    System.out.println(Power(0.00000000000000000000000000001, -1));
//    System.out.println(Power(0.00000000000000000000000000001, 1));
//    System.out.println(Power(0.00000000000000000000000000001, 0));
    // base equals 0
//    System.out.println(Power(0.00000000000000000000000000000, 0));
  }

  public static double Power(double base, int exponent) {
    if (Double.compare(0.0, base) == 0
            && exponent <= 0)
      throw new RuntimeException("Invalid input");

    if (exponent==0)
      return 1;

    // exp 可能小于零
    int absExp = exponent;
    if (exponent<0)
      absExp = -exponent;

    double res = 1;
    for (int i = 0; i < absExp; i++)
      res *= base;

    if (exponent<0)
      res = 1 / res;

    return res;
  }
}

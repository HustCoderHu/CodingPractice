public class Q46 {
  // 求1+2+3+...+n，要求不能使用乘除法、
  // for、while、if、else、switch、case等关键字及条件判断语句（A?B:C）。
  public static void main(String[] args) {
    System.out.println(Sum_Solution(10));
  }
  public static int Sum_Solution(int n) {
    Tmp.reset();
    Tmp[] a = new Tmp[n];
    return Tmp.getSum();
  }
}

class Tmp {
  private static int n;
  private static int sum;

  public Tmp() {
    ++n;
    sum += n;
  }
  public static void reset() {
    n = 0;
    sum = 0;
  }

  public static int getSum() {
    return sum;
  }
}

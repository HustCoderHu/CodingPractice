public class Q10 {
  // 二进制中1的个数
  // https://github.com/Wang-Jun-Chao/coding-interviews/blob/master/src/Test10.java
  public static void main(String[] args) {
    int n = 127;
    String s = Integer.toBinaryString(n);
    System.out.println(s);
    System.out.println(NumberOf1(n));
    System.out.println(NumberOf1Better(n));
  }
  public static int NumberOf1(int n) {
    int cnt = 0;
    for (int i = 0; i < 32; i++) {
      if ((n & 1) != 0)
        ++cnt;
      n >>>= 1;
    }
    return cnt;
  }
  public static int NumberOf1Better(int n) {
    int cnt = 0;
    while (n != 0) {
      ++cnt;
      n = (n - 1) & n; // 每次使最右边的1变成0
    }
    return cnt;
  }
}

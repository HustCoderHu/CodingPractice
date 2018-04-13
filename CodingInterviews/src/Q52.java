import java.util.Arrays;

public class Q52 {
  // 给定一个数组A[0,1,...,n-1],请构建一个数组B[0,1,...,n-1],
  // 其中B中的元素B[i]=A[0]*A[1]*...*A[i-1]*A[i+1]*...*A[n-1]。不能使用除法。
  public static void main(String[] args) {
    int[] a = {1, 2, 3, 4, 5};
    System.out.println(Arrays.toString(multiply(a)));
  }
  public static int[] multiply(int[] A) {
    if (A == null || A.length <= 1)
      return null;

    int[] b = new int[A.length];
    // c[i] = c[i-1] * A[i-1];
    // d[i] = d[i+1] * A[i+1];

    int len = A.length;
    b[len-1] = 1;
    for (int i = len-2; i >= 0; i--)
      b[i] = b[i + 1] * A[i + 1];

    int tmp = 1;
    for (int i = 1; i < len; i++) {
      tmp *= A[i-1];
      b[i] *= tmp;
    }
    return b;
  }
}

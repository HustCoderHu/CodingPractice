package wangyi;

import java.util.Scanner;

public class wangyi {
  public static void main(String[] args) {

  }
}
// Main

class Q1 {
  // 矩形重叠
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);

    int n = 2;

    n = in.nextInt();


  }
}

//class Q2 {
class Q2 {
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);

    int n = 5;
    int k = 2;
//    n = in.nextInt();
//    k = in.nextInt();

    int cnt = 0;
//    for (int x = k; x <= n; x++) {
//      for (int y = k + 1; y <= n; y++) {
//        if (x % y >= k) {
//          cnt++;
////          System.out.println(x + " " + y);
//        }
//      }
//    }

    for (int y = k + 1; y <= n; y++) {
      int a = n / y;
      int left = n - a * y;
      if (left == 0)
        continue;
      cnt += ((a+1)*(y-k));
      if (left >= k)
        cnt += (left-k);
    }

//    for (int y = k + 1; y <= n; y++) {
//      for (int x=k; x <= n; x++) {
//        if (x % y >= k) {
//          cnt++;
//          System.out.println(x + " " + y);
//        }
//      }
//    }

//    int y = k+1;
//    int x = k;
//    while (y <= n) {
//      x = k;
//      while (x <= n) {
//        if (x % y == k) {
//
//        }
//        x++;
//      }
//      y++;
//    }

    System.out.println("cnt = " + cnt);
  }
}

class Q3 {
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);

    int n = 3;
    int m = 3;

    n = in.nextInt();
    m = in.nextInt();

    int[][] work = new int[n][2];

    int[] ai = new int[m];

    for (int i = 0; i < n; i++) {
      work[i][0] = in.nextInt();
      work[i][1] = in.nextInt();
    }
    for (int i = 0; i < m; i++) {
      ai[i] = in.nextInt();
    }

  }
}

import java.util.*;

public class Q2 {
//public class Main {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
//    int n = sc.nextInt();
    int n = 5;

    int[] dp = new int[n+1];

    dp[1] = 0;
    dp[2] = 1;
    dp[3] = 2;

    for (int i = 4; i < n+1; i++) {
      if ((i & 1) == 0) {
        dp[i] = Math.min(dp[i >> 1], dp[i-1]) + 1;
      } else {
        dp[i] = i-1;
      }
    }

    System.out.println(dp[n]);
  }
}
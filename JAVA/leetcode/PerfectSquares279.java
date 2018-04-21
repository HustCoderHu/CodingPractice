package leetcode;

public class PerfectSquares279 {
  public static void main(String[] args) {
    numSquares(20);
  }

  static public int numSquares(int n) {
    int[] dp = new int[n+1];
    dp[0] = 0;

    for(int i = 1; i <= n; ++i) {
      int tmin = Integer.MAX_VALUE;
      for(int j = 1; j*j <= i; ++j) {
        if (dp[i-j*j] < tmin)
          tmin = dp[i - j * j];
      }
      dp[i] = tmin+1;
    }

//    for (int i = 0; i < 20; i++) {
//      System.out.println(i + ": " + dp[i]);
//    }
    return dp[n];
  }
}

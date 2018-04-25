package leetcode;

public class _62UniquePaths {
  public static void main(String[] args) {
    System.out.println(combination(5,2));
  }
  // c(n, m) m<=n
  static long combination(int n, int m) {
    if (m==0 || n==m)
      return 1;

    long[][] c = new long[n+1][m+1];
    for (int i = 1; i <= n; i++) {
      c[i][0] = 1;
      c[i][1] = i;
      if (i<=m)
        c[i][i] = 1;
    }
    for (int i = 2; i <=n; i++)
      for (int j = 1; j < i&&j<=m; j++)
        c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
    return c[n][m];
  }

  static int combinationInt(int n, int m) {
    if (m==0 || n==m)
      return 1;

    int[][] c = new int[n+1][m+1];
    for (int i = 1; i <= n; i++) {
      c[i][0] = 1;
      c[i][1] = i;
      if (i<=m)
        c[i][i] = 1;
    }
    for (int i = 2; i <=n; i++)
      for (int j = 1; j < i&&j<=m; j++)
        c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
    return c[n][m];
  }
  public static int uniquePaths(int m, int n) {
    return combinationInt(m + n - 2, m - 1);
  }
}

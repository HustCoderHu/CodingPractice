package leetcode;

public class _10RegularExpressionMatching {
  public static void main(String[] args) {
    String s = "mississippi";
    String p = "mis*is*p*.";

    boolean a = isMatch(s, p);
    System.out.println("a = " + a);
  }
  static boolean isMatch(String s, String p) {
    boolean[][] dp = new boolean[s.length()+1][p.length()+1];
    dp[s.length()][p.length()] = true;
    for (int i = s.length(); i >= 0; i--) {
      for (int j = p.length()-1; j >= 0 ; j--) {
        // 第一个字符匹配
        boolean _1st_match = i < s.length() &&
                (p.charAt(j) == s.charAt(i) || p.charAt(j) == '.');
        // 接下来是 *
        if (j+1 < p.length() && p.charAt(j+1) == '*')
          // 跳过第一个 后面匹配上 or 第一个匹配上，后面继续匹配
          dp[i][j] = dp[i][j + 2] || _1st_match && dp[i + 1][j];
        else
          // 不是 *的后续匹配
          dp[i][j] = _1st_match && dp[i + 1][j + 1];
      }
    }
    return dp[0][0];
  }
}

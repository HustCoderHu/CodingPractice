package leetcode;

public class _5LongestPalindromicSubstring {
  public static String longestPalindrome(String s) {
    int st = 0, end=0;
    for (int i = 0; i < s.length(); i++) {
      int len1 = expandAroundCenter(s, i, i);
      int len2 = expandAroundCenter(s, i, i + 1);
      int len = Math.max(len1, len2);
      if (len > end - st) {
        st = i - (len - 1) / 2;
        end = i + len / 2; // end = st+len-1;
      }
    }
    return s.substring(st, end + 1);
  }

  static int expandAroundCenter(String s, int L, int R) {
    while (0 <= L && R < s.length()
            && s.charAt(L) == s.charAt(R)) {
      --L;
      ++R;
    }
    return R-L-1;
  }
}

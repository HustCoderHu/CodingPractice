package leetcode;

import java.util.ArrayList;
import java.util.List;

public class _22GenerateParentheses {
  public static void main(String[] args) {
    System.out.println(generateParenthesis(3));
  }

  static int sn;
  static List<String> res;
  static char[] carr;
  static int len;
  public static List<String> generateParenthesis(int n) {
    sn = n;
    res = new ArrayList<>();
    carr = new char[n*2];
    int len = 0;
    helper(0, 0);
    return res;
  }
  static void helper(int open, int close) {
    if (open == sn && close == sn) {
      res.add(String.valueOf(carr));
      return;
    }
    if (open < sn) {
      carr[len++] = '(';
      helper(open + 1, close);
      --len;
    }
    if (close < open) {
      carr[len++] = ')';
      helper(open, close+1);
      --len;
    }
  }
}

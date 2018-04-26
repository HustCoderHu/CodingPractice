package leetcode;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class _139WordBreak {
  public static void main(String[] args) {
    String s = "leetcode";
    List<String> wd = new ArrayList<>(2);
    wd.add("leet");
    wd.add("code");
    System.out.println(wordBreak(s, wd));

    wd.clear();
    s = "applepenapple";
    wd.add("apple");
    wd.add("pen");
    System.out.println(wordBreak(s, wd));

    wd.clear();
    s = "catsandog";
    wd.add("cats");
    wd.add("dog");
    wd.add("sand");
    wd.add("and");
    wd.add("cat");
    System.out.println(wordBreak(s, wd));

    wd.clear();
    s = "a";
    System.out.println(wordBreak(s, wd));

    wd.add("b");
    System.out.println(wordBreak(s, wd));
  }
  public static boolean wordBreak(String s, List<String> wordDict) {
    if (wordDict.size() == 0)
      return false;

    Set<String> set = new HashSet<>(wordDict);
    boolean[] dp = new boolean[s.length()];

    // 最后一个字串 + 前面有效的 str
    // abcd -> abc d
    // -> ab c
    // contained(str)
    // dp[end] = dp[i] && contained(substr(i+1, end+1)]) 0<=i<=end
    for (int end = 0; end <s.length(); ++end) {
      String substr = s.substring(0, end + 1);
      if (set.contains(substr)) {
        dp[end] = true;
        continue;
      }
      for (int st = end -1; st >= 0; --st) {
        if (!dp[st])
          continue;
        substr = s.substring(st+1, end + 1);
        if (set.contains(substr)) {
          dp[end] = true;
          break;
        }
      }
    }
    return dp[s.length() - 1];
  }
}

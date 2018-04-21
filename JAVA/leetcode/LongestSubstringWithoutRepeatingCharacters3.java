package leetcode;

import java.util.HashSet;
import java.util.Set;

public class LongestSubstringWithoutRepeatingCharacters3 {
  public static void main(String[] args) {
    String s = "abcabcbb";
    String s1 = "bbbbb";
    String s2 = "pwwkew";
    String s3 = "abcadae";
    System.out.println(lengthOfLongestSubstring(s));
    System.out.println(lengthOfLongestSubstring(s1));
    System.out.println(lengthOfLongestSubstring(s2));
    System.out.println(lengthOfLongestSubstring(s3));
    System.out.println(useHash(s3));

  }
  public static int lengthOfLongestSubstring(String s) {
    int n = s.length();
    int ans = 0;
    int[] idx = new int[128];// current index of character
    // try to extend the range [i, j]

    for (int j = 0, i=0; j < n; j++) {
      // abcadae

      // idx['a'] = 0 j=0
      // idx['a'] = 1 j=3
      // idx['a'] = 4 j=5
      i = Math.max(idx[s.charAt(j)], i);
      ans = Math.max(ans, j - i + 1);
      idx[s.charAt(j)] = j+1;
      // idx['a'] = 1
      // idx['a'] = 4
      // idx['a'] = 6
    }
    return ans;
  }

  static int useHash(String s) {
    int n = s.length();
    Set<Character> set = new HashSet<>(n);
    int ans = 0, i = 0, j = 0;
    while (i < n && j < n) {
      // try to extend the range [i, j]
      if (!set.contains(s.charAt(j))) {
        set.add(s.charAt(j++));
        ans = Math.max(ans, j-i);
      } else
        set.remove(s.charAt(i++));
    }
    return ans;
  }
}

package leetcode;

import java.util.*;

public class _49GroupAnagrams {
  // abbccc will be #1#2#3#0#0#0...#0
  // 计数 map
  public List<List<String>> groupAnagrams(String[] strs) {
    if (strs.length == 0) return new ArrayList();
    Map<String, List> ans = new HashMap<>();
    int[] count = new int[26];
    StringBuilder sb = new StringBuilder("");
    for (String s : strs) {
      Arrays.fill(count, 0);
      for (char c : s.toCharArray())
        count[c - 'a']++;

      // 针对每个str 计算 key
      sb.setLength(0);
      for (int i = 0; i < 26; i++) {
        sb.append('#');
        sb.append(count[i]);
      }
      String key = sb.toString();
      if (!ans.containsKey(key))
        ans.put(key, new LinkedList());
      ans.get(key).add(s);
    }

    List<List<String>> ll = new ArrayList<>(ans.size());
    for (List<String> l : ans.values())
      ll.add(l);

    return ll;
  }
}

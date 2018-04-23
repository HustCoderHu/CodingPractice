package leetcode;

import java.util.ArrayList;
import java.util.List;

public class _39CombinationSum {
  public static void main(String[] args) {
    int[] a = {2,3,6,7};
    int tgt = 7;
    showLL(combinationSum(a, tgt));

    System.out.println();
    int[] a1 = {2, 3, 5};
    tgt = 8;
    showLL(combinationSum(a1, tgt));
  }

  static List<List<Integer>> ll = new ArrayList<>();
  static List<Integer> tmpl = new ArrayList<>();
  static int[] cand;

  static void showLL(List<List<Integer>> ll) {
    for (List<Integer> l : ll)
      System.out.println(l.toString());
  }
  public static List<List<Integer>> combinationSum(int[] candidates, int target) {
    ll.clear();
    tmpl.clear();

    if (candidates == null || candidates.length==0)
      return ll;
    cand = candidates;
    backtrack(target, 0);
    return ll;
  }

  static void backtrack(int remain, int start) {
    if (remain < 0)
      return;
    else if (remain == 0)
      ll.add(new ArrayList<>(tmpl));
    else {
      for (int i = start; i < cand.length; i++) {
        tmpl.add(cand[i]);
        backtrack(remain-cand[i], i);
        // not i + 1 because we can reuse same elements
        tmpl.remove(tmpl.size() - 1);
      }
    }
  }
}

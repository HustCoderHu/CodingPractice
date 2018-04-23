package leetcode;

import java.time.temporal.Temporal;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class _46Permutations {
  public static void main(String[] args) {
    int[] a = {1, 2, 3};
    showLL(permute(a));
  }
  static List<List<Integer>> ll = new ArrayList<>();
  static List<Integer> tmpl = new ArrayList<>();
  static Set<Integer> set = new HashSet<>();

  static int[] intar;

  public static List<List<Integer>> permute(int[] nums) {
    ll.clear();
    tmpl.clear();

    if (nums == null || nums.length == 0)
      return ll;

    intar = nums;
    backtrack();
    return ll;
  }

  static void backtrack(){
    if(tmpl.size() == intar.length) {
      ll.add(new ArrayList<>(tmpl));
    } else{
      for(int i = 0; i < intar.length; i++){
        if (set.contains(intar[i]))
          continue;
//        if(tmpl.contains(intar[i])) continue; // element already exists, skip
        tmpl.add(intar[i]);
        set.add(intar[i]);
        backtrack();
        tmpl.remove(tmpl.size() - 1);
        set.remove(intar[i]);
      }
    }
  }

  static void showLL(List<List<Integer>> ll) {
    for (List<Integer> l : ll)
      System.out.println(l.toString());
  }
}

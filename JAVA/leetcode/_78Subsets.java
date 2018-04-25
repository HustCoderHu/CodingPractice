package leetcode;

import java.util.ArrayList;
import java.util.List;

public class _78Subsets {
  static List<List<Integer>> ll;
  static List<Integer> tmpl;
  static int[] ar;

  public static void main(String[] args) {
    int[] arr = {1, 2, 3};
    subsets(arr);
    for (List<Integer> l : ll)
      System.out.println(l.toString());
  }
  public static List<List<Integer>> subsets(int[] nums) {
    if (nums == null || nums.length == 0)
      return new ArrayList<>();
    int initCapacity = 1 << nums.length;
//    List<List<Integer>> ll = new ArrayList<>(initCapacity);
    ll = new ArrayList<>(initCapacity);
    tmpl = new ArrayList<>(nums.length);

    for (int i = 0; i < initCapacity; i++) {
      tmpl.clear();
      // 对应 bit 代表是否包含某个元素
      for (int j = 0; j < nums.length; j++) {
        if (testBit(i, j))
          tmpl.add(nums[j]);
      }
      ll.add(new ArrayList<>(tmpl));
    }
    return ll;
  }
//  static void backtrack(int start)

  static boolean testBit(int bitm, int idx) {
    return (bitm & (1<<idx)) != 0;
  }
}

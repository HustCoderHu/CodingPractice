package leetcode;

import java.util.Arrays;

public class _34SearchForaRange {
  public static void main(String[] args) {
    int[] a = {5,7,7,8,8,10};
    int tgt = 8;
    System.out.println(Arrays.toString(searchRange(a, tgt)));
    tgt = 6;
    System.out.println(Arrays.toString(searchRange(a, tgt)));
  }


  public static int[] searchRange(int[] nums, int target) {
    int[] res = {-1, -1};

    if (nums == null || nums.length == 0)
      return res;

    int lo = 0, hi = nums.length-1;

    // Search for the left one
    while (lo < hi) {
      int mid = (lo + hi) >>> 1;
      if (nums[mid] < target)
        lo = mid+1;
      else
        hi = mid;
    }
    if (nums[lo]!=target)
      return res;
    else
      res[0] = lo;

    // Search for the right one
    hi = nums.length-1;  // We don't have to set i to 0 the second time.
    while (lo < hi) {
//      System.out.println("lo = " + lo);
//      System.out.println("hi = " + hi);
      int mid = (lo+hi) >>> 1;
      ++mid;
//      System.out.println("mid = " + mid);
      if (target < nums[mid])
        hi = mid-1;
      else
        lo = mid;
    }
    res[1] = hi;
    return res;
  }
}

package leetcode;

import java.util.Arrays;

public class _33SearchinRotatedSortedArray {
  public static void main(String[] args) {
    int[] ar = {4,5,6,7,0,1,2};
    int target = 0;
    System.out.println();

    System.out.println(search(ar, target));

    target = 3;
    System.out.println(search(ar, target));
  }
  public static int search(int[] nums, int target) {
    if (nums == null || nums.length <= 0)
      return -1;
    int minIdx = findMxIdx(nums);
    int n = nums.length;

    int lo;
    int hi;

    if (target <= nums[n - 1]) {
      lo = minIdx;
      hi = n - 1;
    } else {
      lo = 0;
      hi = (minIdx-1+n)%n;
    }

    while (lo <= hi) {
      int mid = (lo+hi) >>> 1;
      int v = nums[mid];
      if (v < target)
        lo = mid+1;
      else if (target < v)
        hi = mid-1;
      else
        return mid;
    }

    return -1;
  }

  static int findMxIdx(int[] ar) {
    int lo = 0, hi = ar.length-1;
    while (lo < hi) {
      int mid = lo + (hi - lo)/2;
      if (ar[mid] > ar[hi])
        lo=mid+1;
      else
        hi = mid;
    }
    return hi;
  }
}

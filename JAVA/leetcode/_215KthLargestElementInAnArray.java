package leetcode;

public class _215KthLargestElementInAnArray {
  public static void main(String[] args) {
    int[] a = {3, 2, 1, 5, 6, 4};
    System.out.println(findKthLargest(a, 2));
  }
  public static int findKthLargest(int[] nums, int k) {
    int target = nums.length-k;
    int lo = 0;
    int hi = nums.length-1;

    int idx = partition(nums, lo, hi);

    while (idx != target) {
      if (idx < target)
        lo = idx+1;
      else
        hi = idx-1;
      idx = partition(nums, lo, hi);
    }
    return nums[idx];
  }

  static int partition(int[] a, int lo, int hi) {
    int p = a[lo];
    while (lo < hi) {
      while (lo < hi && p <= a[hi])
        --hi;
      a[lo] = a[hi];
      while (lo < hi && a[lo] <= p)
        ++lo;
      a[hi] = a[lo];
    }
    a[lo] = p;
    return lo;
  }
}

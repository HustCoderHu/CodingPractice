package leetcode;

public class _152MaximumProductSubarray {
  public static void main(String[] args) {
//    int[] a = {-2, 0, -1};
    int[] a = {-2,3,-4};
    int res = maxP(a);
    System.out.println(res);
  }

  static int maxProduct(int[] nums) {
    int maxp = 0;
    int pre_p = 1;
    int pre_n = 0;
    for (int i = 0; i < nums.length; ++i) {
      if (nums[i] > 0) {
        pre_p *= nums[i];
        pre_n *= nums[i];
      } else if (nums[i] < 0) {
        int p = pre_p;
        pre_p = pre_n * nums[i];
        pre_n = p * nums[i];
      } else {
        pre_p = 0;
        pre_n = 0;
      }
      System.out.println(i);
      System.out.println(pre_p);
      System.out.println(pre_n);
//      if (pre_p ==)
      maxp = pre_p > maxp ? pre_p : maxp;
      if (pre_p == 0)
        pre_p = 1;
    }
    return maxp;
  }
  static int maxP(int[] nums) {
    int r = nums[0];
    for (int i = 1, imax=r, imin=r; i < nums.length; i++) {
      if (nums[i] < 0) {
        int t = imax;
        imax = imin;
        imin = t;
      }
      imax = Math.max(nums[i], imax * nums[i]);
      imin = Math.min(nums[i], imin * nums[i]);
      r = imax>r? imax:r;
    }
    return r;
  }
}

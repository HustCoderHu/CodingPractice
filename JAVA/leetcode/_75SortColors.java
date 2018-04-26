package leetcode;

import java.lang.reflect.Array;
import java.util.Arrays;

public class _75SortColors {
  // 【算法杂谈 1】 从一道面试题再看三路快排partition
  // https://www.imooc.com/article/16141
  public static void main(String[] args) {
    int[] a = {2, 0, 2, 1, 1, 0};
    int[] a1 = {2, 0, 1};
    sortColors(a);
    System.out.println(Arrays.toString(a));
    sortColors(a1);
    System.out.println(Arrays.toString(a1));
  }
  public static void sortColors(int[] nums) {
    // 三路快排
    if (nums == null || nums.length ==0)
      return;
    int idx0 = 0;
    int idx1 = 0;
    int idx2 = nums.length - 1;

    while (idx1 <= idx2) {
      switch (nums[idx1]) {
        case 1: ++idx1; break;
        case 0:
          int t = nums[idx0];
          nums[idx0++] = nums[idx1];
          nums[idx1++] = t;
          break;
        case 2:
          t = nums[idx2];
          nums[idx2--] = nums[idx1];
          nums[idx1] = t;
          break;
      }
    }
  }
}

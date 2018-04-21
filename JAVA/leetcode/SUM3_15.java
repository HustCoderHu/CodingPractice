package leetcode;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class SUM3_15 {

  public static void main(String[] args) {
    int[] a = {-1, 0, 1, 2, -1, -4};
    int[] a1 = {7, -3, -2, -1, 0, 1, 2, 3};
    int[] a2 = {-2,0,1,1,2};
    int[] a3 = {0,0,0,0,0,0,0,0,0,0};

//    threeSum(a);
//    System.out.println();
//    threeSum(a1);
//    threeSum(a2);
    threeSum(a3);
  }

  static int[] arL;
  static int[] arR;

  public static  List<List<Integer>> threeSum(int[] nums) {
    List<List<Integer>> ll = new ArrayList<>();

    if (nums==null || nums.length <= 2)
      return ll;

    Arrays.sort(nums);
    if (nums[nums.length-1] < 0 || 0 < nums[0])
      return ll;

    arL = new int[nums.length/2];
    arR = new int[nums.length/2];

    // 排序后确定第一个数值 a
    // 后两个数和 为 -a，用首尾双指针靠近
    for (int i = 0; i <= nums.length-3; i++) {
      if (nums[i] > 0)
        break;
      if (i>0 && nums[i] == nums[i-1])
        continue;

      int len = findPair(nums, i+1, 0-nums[i]);
      if (len == 0)
        continue;
      for (int j = 0; j < len; j++) {
        List<Integer> l = new ArrayList<>(3);
        l.add(nums[i]);
        l.add(arL[j]);
        l.add(arR[j]);
        System.out.println(l.toString());
        ll.add(l);
      }
    }

    return ll;
  }

  static int findPair(int nums[], int st, int sum) {
    int end = nums.length-1;
    int len = 0;

    while (st < end) {
      int v = nums[st] + nums[end];

      if (v < sum)
        ++st;
      else if (sum < v)
        --end;
      else {
        arL[len] = nums[st++];
        arR[len++] = nums[end--];
        while (st < end && nums[st] == nums[st-1])
          ++st;
        while (st<end && nums[end] == nums[end+1])
          --end;
      }
    }
    return len;
  }
}

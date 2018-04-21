package leetcode;

public class FindtheDuplicateNumber287 {
  public static int findDuplicate(int[] nums) {
    int slow = nums[0];
    int fast = nums[nums[0]];
    while (slow != fast) {
      slow = nums[slow];
      fast = nums[nums[fast]];
    }
    fast = 0;
    while (slow != fast) {
      slow = nums[slow];
      fast = nums[fast];
    }
    return slow;
  }

}
// leetcode 【287 Find the Duplicate Number】【Python】
// https://blog.csdn.net/u014251967/article/details/52485452
// 环检测
// https://blog.csdn.net/caoxiaohong1005/article/details/71250075
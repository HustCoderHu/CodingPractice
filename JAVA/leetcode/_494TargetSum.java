package leetcode;

import java.util.Arrays;

public class _494TargetSum {
  public static void main(String[] args) {
    int[] a = {1, 1, 1, 1, 1};
    int s = 3;
    System.out.println(findTargetSumWays(a, s));
  }
  public static int findTargetSumWays(int[] nums, int S) {
    int allSum = 0;
    for (int n : nums)
      allSum+=n;

    System.out.println("allSum = " + allSum);
    int[][] dp = new int[nums.length][allSum+1];

    for (int i = 0; i < nums.length; i++) {
      dp[0][nums[0]] = 1;
    }
    for (int i = 1; i < nums.length; i++) {
      for (int curSum = 0; curSum <= allSum; curSum++) {
        int subSum = curSum - nums[i];
        if (subSum<0)
          subSum=0;
        else
          subSum = dp[i - 1][subSum];

        int plusSum = curSum + nums[i];
        if (plusSum>allSum)
          plusSum = 0;
        else
          plusSum = dp[i - 1][plusSum];

        dp[i][curSum] = subSum+plusSum;
      }
    }
    return dp[nums.length-1][S];
  }
}

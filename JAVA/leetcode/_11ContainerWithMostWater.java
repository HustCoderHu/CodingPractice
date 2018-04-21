package leetcode;

public class _11ContainerWithMostWater {
  public static void main(String[] args) {
    int[] he = {10,8,1,1,1,1,1,1,2,1};
    System.out.println(maxArea(he));
  }
  public static int maxArea(int[] height) {
    int maxarea = 0, l = 0, r = height.length - 1;
    while (l < r) {
      maxarea = Math.max(maxarea, Math.min(height[l], height[r]) * (r - l));
      if (height[l] < height[r])
        l++;
      else
        r--;
    }
    return maxarea;
  }
}

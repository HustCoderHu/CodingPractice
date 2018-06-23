package leetcode;

public class _581ShortestUnsortedContinuousSubarray {
  public static void main(String[] args) {
    int[] ar = {2, 6, 4, 8, 10, 9, 15};
    int len = findUnsortedSubarray(ar);
    System.out.println(len);
  }
  static int findUnsortedSubarray(int[] nums) {
    int[] stack = new int[nums.length];
    int sz = 0;
    // 定位起点
    for (int i = 0; i < nums.length; i++) {
      while (sz != 0 && nums[stack[sz - 1]] > nums[i]) {
        // 找到比自己小的
        --sz;
      }
      stack[sz++] = i;
    }
    int l = 0;
    for (int i = 0; i < sz; i++) {
      if (stack[i] != i) {
        l = i;
        break;
      }
    }

    sz = 0;
    // 定位结束
    for (int i = nums.length-1; i >= 0; --i) {
      while (sz != 0 && nums[stack[sz - 1]] < nums[i]) {
        // 找到比自己大的
        --sz;
      }
      stack[sz++] = i;
    }
    int r = -1;
    for (int i = 0; i < sz; i++) {
      if (stack[i] != nums.length-1-i) {
        r = nums.length - 1 - i;
        break;
      }
    }
//    System.out.println("l = " + l);
//    System.out.println("r = " + r);
    
    return r-l+1;
  }
}

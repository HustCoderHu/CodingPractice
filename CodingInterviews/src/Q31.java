public class Q31 {
  // 连续子数组最大和
  public static void main(String[] args) {
    int[] a = {6,-3,-2,7,-15,1,2,2};
    System.out.println(FindGreatestSumOfSubArray(a));
  }

  public static int FindGreatestSumOfSubArray(int[] array) {
    if (array == null || array.length <= 0)
      return 0;

    int greatest = 1<<31; // -2147483648
//    System.out.println("greatest = " + greatest);
    int sum = 0;
    for (int i = 0; i < array.length; i++) {
      if (sum <= 0)
        sum = array[i];
      else
        sum += array[i];

      if (sum > greatest)
        greatest = sum;
    }

    return greatest;
  }
}

public class Q29 {
  // 数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。
  // 例如输入一个长度为9的数组{1,2,3,2,2,2,5,4,2}。由于数字2在数组中出现了5次，
  // 超过数组长度的一半，因此输出2。如果不存在则输出0。
  public static void main(String[] args) {
    int[] a = {1,2,3,2,2,2,5,4,2};
    System.out.println(MoreThanHalfNum_Solution(a));
  }

  public static int MoreThanHalfNum_Solution(int [] array) {
    if (array == null || array.length <= 0)
      return 0;

    int res = array[0];
    int times = 1;
    for (int i = 1; i < array.length; i++) {
      if (times == 0) {
        res = array[i];
        times = 1;
      } else if (array[i] == res)
        times++;
      else
        times--;
    }
    if (!chkMoreThanHalf(array, res))
      res = 0;
    return res;
  }

  static boolean chkMoreThanHalf(int[] a, int res) {
    int cnt = 0;
    for (int i = 0; i < a.length; i++) {
      if (a[i] == res)
        ++cnt;
    }
    boolean isMoreThanHalf = true;
    if (cnt*2 <= a.length)
      isMoreThanHalf = false;
    return isMoreThanHalf;
  }
}

import java.util.ArrayList;

public class Q41_2 {
  // 输入一个递增排序的数组和一个数字S，在数组中查找两个数，
  // 是的他们的和正好是S，如果有多对数字的和等于S，输出两个数的乘积最小的。
  public static void main(String[] args) {
    int[] a = {1, 2, 3, 4, 5, 6, 7, 8};
    int sum = 9;
    System.out.println(FindNumbersWithSum(a, sum).toString());
  }

  public static ArrayList<Integer> FindNumbersWithSum(int[] array, int sum) {
    ArrayList<Integer> l = new ArrayList<>(2);

    if (sum < 3)
      return l;

    int st = 0, end = array.length - 1;
    int small=0, big=0;

    boolean notFound = true;

    while (st < end) {
      int s = array[st] + array[end];
      if (sum < s)
        --end;
      else if (s < sum)
        ++st;
      else {
        if (notFound
                || ((!notFound) && array[st] * array[end] < small * big)) {
          small = array[st];
          big = array[end];
          notFound = false;
        }
        --end;
      }
    }
    if (!notFound) {
      l.add(small);
      l.add(big);
    }
    return l;
  }
}

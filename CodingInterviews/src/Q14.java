import java.util.Arrays;
import java.util.function.IntPredicate;

public class Q14 {
  // 输入一个整数数组，实现一个函数来调整该数组中数字的顺序，
// 使得所有的奇数位于数组的前半部分，所有的偶数位于位于数组的后半部分，
// 并保证奇数和奇数，偶数和偶数之间的相对位置不变。
  public static void main(String[] args) {
    int[] array = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    reOrderArray(array);
    System.out.println(Arrays.toString(array));
  }

  public static void reOrderArray(int[] array) {
    if (array == null || array.length == 0)
      return;

    int left = 0;
    int right = array.length-1;

//    Runnable isEven = (int n)-> (n&1) == 0;
    IntPredicate isEven = (int n)-> (n&1) == 0;
    System.out.println(isEven.test(7));
    System.out.println(isEven.test(8));

    while (left < right) {
      while (left < right && isEven.test(array[right]))
        --right;

      while (left < right && !isEven.test(array[left]))
        ++left;

      int tmp = array[left];
      array[left] = array[right];
      array[right] = tmp;
    }
  }
}

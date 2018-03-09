package BaseAlgorithm;

import java.util.ArrayDeque;
import java.util.Arrays;

// 排序算法之4：快速排序 QuickSort
// https://www.jianshu.com/p/6d0544ac425b

public class QuickSort {
  public static void main(String[] args) {
    int[] arr = {4, 7, 2, 1, 5, 3, 8, 6};

//    partition(arr, 0, arr.length-1);
    qsort(arr);
    System.out.println(Arrays.toString(arr));
  }

  /**
   * 快排 below
   */
  public static void qsort(int[] arr) {
    if (arr == null || arr.length==0)
      return;
//    _qsort(arr, 0, arr.length-1);
    nonRecurseQsort(arr);
  }

  static void _qsort(int[] arr, int left, int right) {
    if (left >= right)
      return;
    int pivotPos = partition(arr, left, right);
//    if (left < pivotPos - 1)
    _qsort(arr, left, pivotPos - 1);
//    if (pivotPos+1 < right)
    _qsort(arr, pivotPos + 1, right);
  }

  public static void nonRecurseQsort(int[] arr) {
    // http://www.cnblogs.com/ljy2013/p/4003412.html
    ArrayDeque<Integer> stack = new ArrayDeque(arr.length);
    int left, right;
    stack.push(arr.length-1); // 先右再左
    stack.push(0);

    while (!stack.isEmpty()) {
      left = stack.pop();
      right = stack.pop();
      if (left >= right)
        continue;

      int k = partition(arr, left, right);
      // 递归是先分左边再右边，所以下面先push右边再右边
      stack.push(right);
      stack.push(k+1);
      stack.push(k - 1);
      stack.push(left);
//      if (k+1 < right) {
//        stack.push(right);
//        stack.push(k+1);
//      }
//      if (left < k-1) {
//        stack.push(k - 1);
//        stack.push(left);
//      }
    }
  }

  static int partition(int[] arr, int left, int right) {
    int pivotKey = arr[left];
    System.out.println("pivotKey = " + pivotKey);

    while (left < right) {
      // 从前后往中间找
      while (left < right && arr[right] >= pivotKey)
        right--;
      arr[left] = arr[right]; // 小的到左边
      System.out.println(Arrays.toString(arr));

      while (left < right && arr[left] <= pivotKey)
        left++;
      arr[right] = arr[left]; // 大的去右边
      System.out.println(Arrays.toString(arr));
    }
    arr[left] = pivotKey; // pivot 放中间
    return left;
  }
}


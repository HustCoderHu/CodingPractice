package BaseAlgorithm;

import java.util.ArrayDeque;
import java.util.Arrays;

// 白话经典算法系列之五 归并排序的实现
// http://blog.csdn.net/morewindows/article/details/6678165/

public class MergeSort {
  public static void main(String[] args) {
//    int[] arr = {4, 7, 2, 1, 5, 3, 8, 6};
    int[] arr = {2, 3, 5, 8, 9, 0, 7, 5, 1, 6, 8, 7};
    msort(arr);
    System.out.println(Arrays.toString(arr));
  }

  public static void msort(int[] arr) {
    int[] tmp = new int[arr.length];
//    _msort(arr, tmp, 0, arr.length - 1);
    nonRecurMsort(arr, tmp);
  }

  static void _msort(int[] arr, int[] tmp, int left, int right) {
    if (left >= right)
      return;

    int mid = (left + right) / 2;
    _msort(arr, tmp, left, mid);
    _msort(arr, tmp, mid + 1, right);
    merge(arr, tmp, left, mid, right);
  }

  public static void nonRecurMsort(int[] arr, int[] tmp) {
    ArrayDeque<Integer> stack = new ArrayDeque(arr.length);
    ArrayDeque<Integer> mergeStack = new ArrayDeque(); // 模仿调用栈
    int left, right;
    stack.push(arr.length-1); // 先右再左
    stack.push(0);
    while (!stack.isEmpty()) {
      left = stack.pop();
      right = stack.pop();
      if (left >= right)
        continue;

      mergeStack.push(right);
      mergeStack.push(left);

      int mid = (left + right) / 2;
      stack.push(right);
      stack.push(mid+1);
      stack.push(mid);
      stack.push(left);
    }
    while (!mergeStack.isEmpty()) {
      // 结果正确，过程左右顺序反了
      // 先归并右边了
      left = mergeStack.pop();
      right = mergeStack.pop();
      merge(arr, tmp, left, (left+right)/2, right);
    }
  }

  static void merge(int[] arr, int[] tmp, int left, int mid, int right) {
    int i = left, j = mid + 1;
    int k = 0;

    while (i <= mid && j <= right) {
      if (arr[i] <= arr[j])
        tmp[k++] = arr[i++];
      else
        tmp[k++] = arr[j++];
    }

    while (i <= mid) // 左边有剩
      tmp[k++] = arr[i++];
    while (j <= right) // 右边有剩
      tmp[k++] = arr[j++];
    // 写回左边界
    for (i = 0; i < k; i++)
      arr[left + i] = tmp[i];

    System.out.printf("left = %2d, mid = %2d, right = %2d\n", left, mid, right);
    //left =  0, mid =  0, right =  1
    //left =  0, mid =  1, right =  2
    //left =  3, mid =  3, right =  4
    //left =  3, mid =  4, right =  5
    //left =  0, mid =  2, right =  5
    //left =  6, mid =  6, right =  7
    //left =  6, mid =  7, right =  8
    //left =  9, mid =  9, right = 10
    //left =  9, mid = 10, right = 11
    //left =  6, mid =  8, right = 11
    //left =  0, mid =  5, right = 11
//    System.out.println(Arrays.toString(arr));
  }
}

package leetcode;

import java.util.Arrays;

public class _48RotateImage {
  public static void main(String[] args) {
    int[][] a = {
            {1,2,3},
            {4,5,6},
            {7,8,9} };
    rotate(a);
    for (int i = 0; i < a.length; i++) {
      System.out.println(Arrays.toString(a[i]));
    }
  }

  public static void rotate(int[][] matrix) {
    if (matrix == null || matrix.length == 0 || matrix[0] == null
            || matrix[0].length == 0)
      return;
    int n = matrix.length;

    int border = n >> 1;
    for (int i = 0; i < border; i++) {
      int[] t = matrix[i];
      matrix[i] = matrix[n - 1 - i];
      matrix[n - 1 - i] = t;
    }
//    for (int i = 0; i < matrix.length; i++) {
//      System.out.println(Arrays.toString(matrix[i]));
//    }
    // 转置
    for (int i = 0; i < n; i++) {
      for (int j = i+1; j < n; j++) {
        int t = matrix[i][j];
        matrix[i][j] = matrix[j][i];
        matrix[j][i] = t;
      }
    }
  }
}

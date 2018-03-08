import java.util.Scanner;

public class Q3 {
  // 二维数组查找
  public static void main(String[] args) {
    int m = 4;
    int n = 4;
//    int[][] arr = new int[m][n];
    int[][] array = {
            {1, 2, 8, 9},
            {2, 4, 9, 12},
            {4, 7, 10, 13},
            {6, 8, 11, 15}
    };

    boolean ret = Solution.Find(7, array);
    System.out.println("ret = " + ret);

  }
}

class Solution {
  public static boolean Find(int target, int [][] array) {
    if(array==null
            ||array.length==0 // {}
            ||(array.length==1&&array[0].length==0)) // {{}}
      return false;

    int m = array.length;
    int n = array[0].length;

    int i = 0;
    int j = n-1;
    // 右上角开始
    boolean ret = false;

    while (true) {
      if (i == m || j == -1)
        break;
      if (array[i][j] == target) {
        ret = true;
        break;
      }
      if (target < array[i][j])
        --j; // 左移
      else
        ++i; // 下
    }

    return ret;
  }
}
// java中判断二维数组是否为空
// http://blog.csdn.net/severusyue/article/details/51694916
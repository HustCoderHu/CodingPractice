package xiaozhao2018spring;
import java.util.*;

public class xiecheng {
}
//public class Main {
//while(cin.hasNextInt())
//        {
//        a = cin.nextInt();
//        b = cin.nextInt();
//        System.out.println(a + b);
//        }
//}
class x1 { // 71%
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    int n = 4;

    int[] ar = {0, 7, 0, 2};

    n = sc.nextInt();

    if (n == 0) {
      System.out.printf("");
      return;
    }

    ar = new int[n];
    for (int i = 0; i < n; i++) {
      ar[i] = sc.nextInt();
    }

    int zeroIdx = 0;
    int i = 0;
    while (i < n) {
      if (ar[i] == 0) {
        i++;
        continue;
      }

      while (zeroIdx < n && ar[zeroIdx] != 0)
        zeroIdx++;
      if (zeroIdx >= n)
        break;

      if (zeroIdx < i) {
        int tmp = ar[i];
        ar[i] = 0;
        ar[zeroIdx] = tmp;
        zeroIdx++;
      }
    }
    for (int num : ar)
      System.out.println(num);
//    System.out.println(Arrays.toString(ar));
  }
}

class x2 {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);

    ArrayList<Integer> ar = new ArrayList<>();

    while (sc.hasNext())
      ar.add(sc.nextInt());

    int n = (int)Math.sqrt(ar.size()+0.5);
//    System.out.println("n = " + n);

    int[][] mat = new int[n][n];

    int k = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        mat[i][j] = ar.get(k);
        k++;
      }
    }

//    for(int i = 0; i < n; i++) {
//      for (int j = 0; j < n; j++) {
//        System.out.print(mat[i][j]);
//      }
//      System.out.println();
//    }

    for(int i = 0; i < n; i++) {
      for (int j = 0; j < i; j++) {
        int tmp = mat[i][j];
        mat[i][j] = mat[j][i];
        mat[j][i] = tmp;
      }
    }

    for(int i = 0; i < n; i++) {
      for (int j = 0; j < n / 2; j++) {
        int tmp = mat[i][j];
        mat[i][j] = mat[i][n - j - 1];
        mat[i][n - j - 1] = tmp;
      }
    }

    for(int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        System.out.printf("%d ", mat[i][j]);
      }
      System.out.println();
    }
  }

  public void rotate(int[][] matrix) {
    for(int i = 0; i < matrix.length; i++) //转置
      for(int j = 0; j < i; j++)
      {
        int temp = matrix[i][j];
        matrix[i][j] = matrix[j][i];
        matrix[j][i] = temp;
      }

    for(int i = 0; i < matrix.length; i++) //翻转列
      for(int j = 0; j < matrix.length/2; j++)
      {
        int temp = matrix[i][j];
        matrix[i][j] = matrix[i][matrix.length - j - 1];
        matrix[i][matrix.length - j - 1] = temp;
      }
  }
}


class x3 {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    int n = 4;

    int[] ar = {0, 7, 0, 2};

    n = sc.nextInt();
    ar = new int[n];
    for (int i = 0; i < n; i++) {
      ar[i] = sc.nextInt();
    }
  }
}
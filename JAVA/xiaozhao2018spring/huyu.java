package xiaozhao2018spring;
import java.util.*;

// Main
public class huyu {
}

class Q1 {
  // 花砖拼接
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);

    int T = 4;
    int n = 3;
    int m = 5;
    char[][] blk;
    ArrayList<char[][]> allExamples = null;

    T = sc.nextInt();
    allExamples = new ArrayList<>(T);
    for (int i = 0; i < T; i++) {
      n = sc.nextInt();
      m = sc.nextInt();
      blk = new char[n][n];
      for (int j = 0; j < n; j++) {
        String line = sc.nextLine();
//          line.toCharArray();
        for (int k = 0; k < n; k++)
          blk[j][k] = line.charAt(k);
      }
      sc.nextLine();
      allExamples.add(blk);
    }


  }

  private static char[][] padding(char[][] blk, int n, int m) {
    char[][] out = new char[m][m];
    for (int i = 0; i < m; i++) {
      Arrays.fill(out[i], '-');
    }

    int totalMargin = (m - n) / 2;

    int nNotSplit = totalMargin / n;
    int cut = totalMargin - nNotSplit * n;

    return out;
  }
  private static void padDst(char[][] out, char[][] blk, int row, int col) {
    int n = blk.length;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {

      }
    }
  }
}

class Q2 {
  // 最强战队
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    int T = 4;
    int n = 3;
    int m = 5;

    int[][] power = {{99, 99},
            {100, 0},
            {0, 100},
            {100, 100},
            {100, 0},
            {100, 0}};
    getit(power, 1, 1);
  }
  private static int getit(int[][] power, int X, int Y) {
    int n = power.length;
    int pivotKey = mv0ahead(power);
    System.out.println("pivotKey = " + pivotKey);

    PriorityQueue<Integer> xq = new PriorityQueue<>(pivotKey/2);
    PriorityQueue<Integer> yq = new PriorityQueue<>(pivotKey/2);

    for (int i = 0; i < pivotKey; i++) {
      if (power[i][0] != 0 && power[i][1] == 0)
        xq.add(power[i][0]);
      if (power[i][0] == 0 && power[i][1] != 0)
        yq.add(power[i][1]);
    }

    if (power[pivotKey][0] == 0 || power[pivotKey][1] == 0)
        pivotKey++;

    int minPower = 0;

    for (int i = pivotKey; i < n; i++) {
      int topx, topy;
      topx = xq.isEmpty()? 0 : xq.peek();
      topy = yq.isEmpty()? 0 : yq.peek();

    }
    System.out.println(xq.remove());


    for (int i = 0; i < n; i++) {
      System.out.println(power[i][0] + " " + power[i][1]);
    }
    return 1;
  }

  private static int mv0ahead(int[][] power) {
    int n = power.length;

    int left = 0;
    int right = n-1;

    while (left < right) {
      while (left < right &&
              (power[left][0] == 0 || power[left][1] == 0))
        left++;
      while (left < right &&
              (power[right][0] != 0 && power[right][1] != 0))
        right--;

      int tmp = power[left][0];
      power[left][0] = power[right][0];
      power[right][0] = tmp;

      tmp = power[left][1];
      power[left][1] = power[right][1];
      power[right][1] = tmp;
    }
    return left;
    //100 0
    //100 0
    //0 100
    //100 0
    //100 100
    //99 99
  }
}

class Q3 {
  // 手势锁
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    int n = 4;

    int[] ar = {0, 7, 0, 2};

    n = sc.nextInt();
  }
}
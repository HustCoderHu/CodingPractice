package xiaozhao2018spring;
import javafx.util.Pair;

import java.util.*;

public class iqiyi {
//  Pair
}

class i1 {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);

    String str = "test";
//    str = sc.next();

    pair[] v = new pair[52];
    for (int i = 0; i < v.length; i++) {
      v[i] = new pair();
    }

    char max = '\0';
    int pos = -1;

    for (int i = str.length()-1; i >=0 ; --i) {
      if (max <= str.charAt(i)) {
        max = str.charAt(i);
        pos = i;
      }
      v[i].max = max;
      v[i].pos = pos;
    }

    pair tmp = new pair();
    tmp.max = 0;
    tmp.pos = -1;

    for (int i = 0; i < str.length(); i++) {
      if (tmp.pos != v[i].pos) {
        System.out.print(v[i].max);
        tmp.pos = v[i].pos;
        tmp.max = v[i].max;
      }
    }

//    str = sc.next();
//
////    char[] s = new char[str.length()];
//    int[] idx = new int[str.length()];
//    int k = 0;
//    for (int i = 0; i < str.length(); i++) {
//
//    }
  }

//  static int getMax(char[] ar, int left) {
//    int max = left;
//    char maxc = ar[left];
//    for (int i = left; i < ar.length; i++) {
//
//    }
//  }
}

class pair {
  public char max = '\0';
  int pos = -1;
//  public pair(){}
}

class i2 {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);

//    int a = 2;
//    int b = 5;
//    int c = 4;
    int a = 3;
    int b = 3;
    int c = 2;

    a = sc.nextInt();
    b = sc.nextInt();
    c = sc.nextInt();

    int tmax = a>b?a:b;
    tmax = tmax>c?tmax:c;

    int pad = tmax*3-a-b-c;
    int res = 0;
    if ((pad&0x1) == 0)
      res = pad/2;
    else
      res = pad/2+2;

    System.out.println(res);
  }
}

class i3 {
  // dp[i][j] = sum(dp[i-1][j-li] ... dp[i-1][j-ri])
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    
    int n = 3;
    int m = 5;
    int[] l = {0, 0, 0};
    int[] r = {3, 3, 3};
    
    n = sc.nextInt();
    m = sc.nextInt();
    l = new int[n];
    r = new int[n];
    for (int i = 0; i < n; i++) {
      l[i] = sc.nextInt();
      r[i] = sc.nextInt();
    }

    int[][] dp =new int[n][m+1];

    for (int i = l[0]; i <= r[0]; i++) {
      dp[0][i] = 1;
    }

    for (int i = 1; i < n; i++) {
      for (int j = 1; j <= m; j++) {
        int sum = 0;
        int left = Math.max(0, j-r[i]);
        int right = Math.max(0, j - l[i]);
        for (int k = left; k <= right; k++) {
           sum += dp[i-1][k];
        }
        dp[i][j] = sum;
      }
    }
    System.out.println(dp[n-1][m]);
  }
}

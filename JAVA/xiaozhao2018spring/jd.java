package xiaozhao2018spring;

import java.util.Scanner;

public class jd {
}

class q1 {
  static char[] str;
  static long[][]dp = new long[54][54];

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);

    str = sc.next().toCharArray();
//    str = new String("ABA").toCharArray();

    for (int i = 0; i < 54; i++) {
      for (int j = 0; j < 54; j++)
        dp[i][j] = -1;
    }

    for (int i = 0; i < str.length; i++) {
        dp[i][i] = 1;
    }
    System.out.println(dfs(0, str.length-1));
  }

  static long dfs(int l, int r) {
    if (dp[l][r] != -1)
      return dp[l][r];
    if (l > r) {
      dp[l][r] = 0;
      return 0;
    }

    dp[l][r] = dfs(l, r-1) + dfs(l+1, r)- dfs(l+1, r-1);
    if (str[l] == str[r])
      dp[l][r] += dfs(l+1, r-1)+1;
    return dp[l][r];
  }
}

class q2 {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);


    long b = 1<<63;
    System.out.println(b);
    b = b - 2;
    System.out.println(b);
    int ccnt = copeit(b);
    System.out.println(b);
    System.out.println("ccnt = " + ccnt);

    b = b >>> ccnt;
    System.out.println(b);
    int t = 2;
    t = sc.nextInt();

//    long[] a = {10, 5};

    long[] a = new long[t];
    for (int i = 0; i < t; i++) {
      a[i] = sc.nextLong();
    }

//    if ((a[0] & 0x1) == 0) {
//      System.out.print(a[0]/2 + " " + 2);
//    } else
//      System.out.println("No");

    for (int i = 0; i < t; i++) {
//      System.out.println();
      int cnt = copeit(a[i]);
      if (cnt!=0) {
        long x = a[i] >>> cnt;
        long y = 1<<cnt;
        System.out.print(x + " " + y);
      } else
        System.out.print("No");
      System.out.println();
    }
  }

  static int copeit(long x) {
    int cnt = 0;
    while ((x & 0x1) == 0) {
      cnt++;
      x >>>= 1;
    }
    return cnt;
  }
}

class q3 {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);

    int t = 3;
    t = sc.nextInt();

    String[] a = new String[t];
    for (int i = 0; i < t; i++) {
      a[i] = sc.next();
    }

    for (int i = 0; i < t; i++) {
      if (swapAndJudge(a[i].toCharArray()))
        System.out.println("YES");
      else
        System.out.println("NO");
    }
  }

  static boolean swapAndJudge(char[] str) {
//    int idx1 = -1, idx2=-1;
//    for (int i = 0; i < str.length; i++) {
//      if (idx1 == -1 && str[i] == ')')
//        idx1 = i;
//      if (str[i] == '(')
//        idx2 = i;
//    }
//    char tmp = str[idx1];
//    str[idx1] = str[idx2];
//    str[idx2] = tmp;
//    return judge(str);

    int sum1 = 0, sum2 = 0;
    for (int i = 0; i < str.length; i++) {
      if (str[i] == '(')
        sum1++;
      else
        sum2++;
    }
    if (sum1!=sum2)
      return false;
    if (str.length==2 && !str.equals("()"))
      return false;

    int flag = 0, fl = 0, sum=0;
    for (int i = 0; i < str.length; i++) {
      if (str[i] == '(') {
        sum++;
      } else {
        if (sum != 0) {
          sum--;
          continue;
        }
        if (fl == 0) {
          fl = 1;
          sum++;
        } else {
          flag = 1;
          break;
        }
      }
    }
    if (flag!=1)
      return true;
    else
      return false;
  }

  static boolean judge(char[] str) {
    char[] a = new char[str.length];
    int k = 0;

    for (int i = 0; i < str.length; i++) {
      if (str[i] == '(') {
        a[k++] = str[i];
      } else {
        if (k>0)
          k--;
        else
          return false;
      }
    }
    if (k>0)
      return false;
    return true;
  }
}
package xiaozhao2017;

import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.Scanner;

public class jd {
}

class jihe_A_plus_B {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);

    int n = 3, m = 4;

//    int[] arrA = {1, 3, 5};
//    int[] arrB = {2, 3, 4, 6};
    n = sc.nextInt();
    m = sc.nextInt();
    int[] arrA = new int[n];
    int[] arrB = new int[m];
    for (int i = 0; i < n; i++) {
      arrA[i] = sc.nextInt();
    }
    for (int i = 0; i < m; i++) {
      arrB[i] = sc.nextInt();
    }

    Arrays.sort(arrA);
    Arrays.sort(arrB);

//    PriorityQueue<Integer> ha = new PriorityQueue<>(n);
//    PriorityQueue<Integer> hb = new PriorityQueue<>(m);
//    for (int i = 0; i < n; i++) {
//      ha.add(arrA[i]);
//    }
//    for (int i = 0; i < m; i++) {
//      hb.add(arrB[i]);
//    }

//    int[] merged = mergeHeap(ha, hb);
    int[] merged = merge(arrA, arrB);
    for (int i = 0; i < merged.length - 1; i++) {
      System.out.print(merged[i]);
      System.out.printf(" ");
    }
    System.out.print(merged[merged.length-1]);
  }

  static int[] mergeHeap(PriorityQueue<Integer> ha,
                         PriorityQueue<Integer> hb) {
    int[] merged = new int[ha.size() + hb.size()];
    return merged;
  }
  static int[] merge(int[] arrA, int[] arrB) {
    int alen = arrA.length, blen = arrB.length;
    int[] merged = new int[alen+blen];

    int ai = 0, bi = 0, k = 0;
    while (ai < alen && bi < blen) {
      if (arrA[ai] < arrB[bi])
        merged[k++] = arrA[ai++];
      else
        merged[k++] = arrB[bi++];
    }

    while (ai < alen)
      merged[k++] = arrA[ai++];
    while (bi < blen)
      merged[k++] = arrB[bi++];

    return merged;
  }
}

class jinzhi_avg {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);

    calsum(5);
    calsum(3);
    gcd(20, 24);

//    int x = 7;
//    int sum = calsum(x);
//    int fenmu = x-2;
//    int gcd = gcd(sum, fenmu);
//    System.out.println(sum/gcd + "/" + fenmu/gcd);
//    return;

    while (sc.hasNext()) {
      int x = sc.nextInt();
      int sum = calsum(x);
      int fenmu = x-2;

      int gcd = gcd(sum, fenmu);
      System.out.println(sum/gcd + "/" + fenmu/gcd);
    }
  }

  static int calsum(int x) {
    int sum = 0;
    for (int i = 2; i <= x-1; i++) {
      int tmp = x;
      while (tmp != 0) {
        sum += (tmp % i);
        tmp /= i;
      }
    }
//    System.out.println("sum = " + sum);
    return sum;
  }

  static int gcd(int a, int b) {
    if (a < b) {
      int tmp = b;
      b = a;
      a = tmp;
    }
    while (b != 0) {
      int r = b;
      b = a % b;
      a = r;
    }
//    System.out.println("a = " + a);
    return a;
  }
}

class luckyNum {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    boolean ret = judge(123);
//    System.out.println("ret = " + ret);

    int n = 123;
//    n = sc.nextInt();

    int cnt = 0;
    for (int i = 1; i <= n; i++) {
      if (judge(i))
        cnt++;
    }
    System.out.println("cnt = " + cnt);
  }
  static boolean judge(int x) {
    int f = 0, g = 0;

    int tmp = x;
    while (tmp != 0) {
      f += (tmp % 10);
      tmp /= 10;
    }
    while (x != 0) {
      x = x & (x-1);
      g++;
    }
    return f==g;
  }
}
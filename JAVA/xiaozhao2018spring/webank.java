package xiaozhao2018spring;

import java.util.*;

public class webank {
}

class webank_q1 {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);

    int a = 3;
    int b = 2;
    int c = 1;

    a = sc.nextInt();
    b = sc.nextInt();
    c = sc.nextInt();

    System.out.println(1+b-c);
  }
}

class webank_q2 {
  static int[] ar = new int[1000];
  static int[] times = new int[1000];

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);

    int n = 1000;
//    n = sc.nextInt();

    int j = 0;
    for (int i = 2; i <= n; i++) {
      if (isPrime(i)) {
        ar[j] = i;
        times[j++] = 1;
      }
    }
//    System.out.println(Arrays.toString(ar));

    int pk;
    for (int i = 0; i < j; i++) {
      pk = ar[i];
      while (ar[i] <= n) {
        ar[i] *= pk;
        if (ar[i] <= n)
          times[i]++;
      }
    }
    int res = 0;
    for (int i = 0; i < j; i++) {
      res += times[i];
    }
    System.out.println(res);
  }

  static boolean isPrime(int x) {
    for (int i = 2; i*i <= x; i++) {
      if (x%i == 0)
        return false;
    }
    return true;
  }

}

class webank_q3 {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);

    long n = 10;

//    n = sc.nextLong();
//    if (n == 1) {
//      System.out.println(1);
//      return;
//    }

    long cnt = 0;
    for (long i = 0; i <= n; ++i) {
      if (isP2(i)) {
        ++cnt;
//        System.out.println("i = " + i);
      }
    }
    System.out.println(cnt);
  }

  static boolean isP2(long x) {
//    long t = x;
    long left = 0;
    System.out.println(Long.toBinaryString(x));

//    while (t!=0) {
//      left = t;
//      t = t & (t-1);
//    }
//    System.out.println(Long.toBinaryString(left));
    left = abovePowerOf2(x)>>1;
//    System.out.println(Long.toBinaryString(left));
//    System.out.println();


    long right = 1;
    while (left > right) {
//      String s = Long.toBinaryString(x);
//      System.out.println(s);

      if ((left&x)==0 && (x&right)!=0)
        return false;
      if ((left&x)!=0 && (x&right)==0)
        return false;

      left >>>= 1;
      right <<= 1;
    }
    return true;
  }

  static long abovePowerOf2(long x) {
    x |= x>>>1;
    x |= x>>>2;
    x |= x>>>4;
    x |= x>>>8;
    x |= x>>>16;
    x |= x>>>32;
//    System.out.println(Long.toBinaryString(x));
    return x+1;
  }
}
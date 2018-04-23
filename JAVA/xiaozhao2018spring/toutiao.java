package xiaozhao2018spring;

import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;
import java.util.TreeSet;

public class toutiao {
}

class t1 {
  //public class Main {
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);


    Set<Integer> intSet = new HashSet<>();

    int n = 5;
    int k = 2;
    intSet.add(1);
    intSet.add(5);
    intSet.add(3);
    intSet.add(4);
    intSet.add(2);
//    int n = in.nextInt();
//    int k = in.nextInt();
//    for (int i = 0; i < n; i++)
//      intSet.add(in.nextInt());
    int cnt = 0;
    for (Integer num : intSet) {
      if (intSet.contains(num + k))
        cnt++;
    }

    Integer a1 = 125;
    int a2 = 125;
    System.out.println(a1 == a2);
    a1 = 127;
    a2 = 127;
    System.out.println(a1 == a2);
    a1 = 129;
    a2 = 129;
    System.out.println(a1 == a2);

    System.out.println(cnt);
  }
}

class t4 {
  //public class Main {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);

//    int n = sc.nextInt();
//    int m = sc.nextInt();
    int n = 3;
    int m = 5;

    Set<Integer> seta = new TreeSet<>();
    Set<Integer> setb = new TreeSet<>();

    seta.add(2);
    seta.add(5);
    seta.add(1);

    setb.add(3);
    setb.add(6);
    setb.add(4);
    setb.add(2);
    setb.add(5);

    int suma = 0;
//    for (int i = 0; i < n; i++) {
//      int val = sc.nextInt();
//      suma += val;
//      seta.add(val);
//    }
    int sumb = 0;
//    for (int i = 0; i < m; i++) {
//      int val = sc.nextInt();
//      sumb += val;
//    }
    suma = 8;
    sumb = 20;

    int cnt = 0;
//    int nSeta = seta.size();
//    int nSetb = setb.size();

//    System.out.println(Arrays.toString(seta.toArray()));

    // a -> b
    if (suma * m >= sumb * n) {
      for (Integer num : seta) {
        System.out.println("num = " + num);
        if (suma*m <= sumb*n || n == 1)
          break;
        if (num*n >= suma || sumb >= num*m)
          continue;

        sumb += num;
        m++;
        suma -= num;
        n--;
        cnt++;
      }
    } else { // b -> a
      for (Integer num : setb) {
        System.out.println("num = " + num);
        if (suma*m >= sumb*n || m == 1)
          break;
        if (num*n <= suma || sumb <= num*m)
          continue;

        sumb -= num;
        m--;
        suma += num;
        n++;
        cnt++;
      }
    }

//    while (suma > sumb && n >= 2) {
//      for (Integer num : seta) {
//        if (num*n < suma && num*m > sumb) {
//          sumb += num;
//          m++;
//          suma -= num;
//          n--;
//          cnt++;
//          break;
//        }
//      }
//    }
    System.out.println(cnt);
  }
}
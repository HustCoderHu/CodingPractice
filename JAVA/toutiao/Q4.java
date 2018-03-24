import java.sql.SQLOutput;
import java.util.*;

public class Q4 {
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

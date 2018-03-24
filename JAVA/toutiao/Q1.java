import java.util.*;

public class Q1 {
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

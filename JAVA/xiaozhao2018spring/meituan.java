package xiaozhao2018spring;
import java.util.*;

public class meituan {
}

class m1 {
  public static void main(String[] args) {
//    ArrayList<String> q = new ArrayList<>();
    Set<Integer> words = new HashSet<>();

    Map<String, Integer> staff = new HashMap<>();
    staff.put("Bob", 1);
    staff.put("Carl", 2);
    staff.put("David", 3);

    String name = null;
    int maxVal = 0;

//    for (Set<Map.Entry> : staff.entrySet())

//    for (Map.Entry<String, Integer> entry : staff.entrySet())

  }

  static void ggg() {
    Scanner scanner = new Scanner(System.in);
    String S = scanner.nextLine();
    String T = scanner.nextLine();

    S = "aaabb";
    T = "bab";


  }
}

class m2 {
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
//    String str = null;
    String str = scanner.next();

//    str = "123456789";
//    str = "1234567890";
//    str = str + str;

    int[] cnt = new int[10];

    int[] strArr = str.chars().toArray();

//    System.out.println(Arrays.toString(strArr));
    for (int i = 0; i < str.length(); i++) {
//      cnt[i] = str.charAt(i) - '0';
      int idx = str.charAt(i) - '0';
      cnt[idx]++;
    }
//    System.out.println(Arrays.toString(cnt));
    // [0, 1, 1, 1, 1, 1, 1, 1, 1, 1]


    int theMin = 1;
    for (int i = 1; i < 10; i++) {
      if (cnt[i] == 0) {
        theMin = i;
        System.out.println(theMin);
        return;
      }
    }
    if (cnt[0] == 0) {
      System.out.println(10);
      return;
    }

    theMin = 10;
    boolean notFound = true;
    while (true) {

    }

//    boolean bb = checkIt(cnt, 111);
//    System.out.println(bb);
//    return;
  }

  static boolean checkIt(int[] cnt, int val) {
    boolean bb = true;
    while (val != 0) {
      int gewei = val%10;
      val /= 10;
      if (cnt[gewei] == 0) {
        bb = false;
        break;
      } else {
        cnt[gewei]--;
      }
    }
    return bb;
  }
}
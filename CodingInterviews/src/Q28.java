import java.util.*;

public class Q28 {
  // 输入一个字符串,按字典序打印出该字符串中字符的所有排列。
  // 例如输入字符串abc,则打印出由字符a,b,c
  // 所能排列出来的所有字符串abc,acb,bac,bca,cab和cba。

  // 输入一个字符串,长度不超过9(可能有字符重复),字符只包括大小写字母。
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    String in = "abcc";
    int len = in.toCharArray().length;
    System.out.println("len = " + len);

    Permutation(in);
  }
  public static ArrayList<String> Permutation(String str) {
    if (str == null || str.length() <= 0)
      return new ArrayList<String>(0);

    Set<Character> alpha = new HashSet<>(52);
    for (int i = 0; i < str.length(); i++)
      alpha.add(str.charAt(i));
    // 去掉重复

    int i = 0;

    int cnt = 1;
    for (int j = 2; j <= alpha.size(); j++) {
      cnt *= j;
    }
    ArrayList<String> list = new ArrayList<>(cnt);
//    System.out.println(Arrays.toString(str.toCharArray()));
    getall(str.toCharArray(), 0, list);

    System.out.println(list.toString());
    return list;
  }

  static void getall(char[] str, int begin, ArrayList<String> list) {
//    System.out.println(str.length);
//    System.out.println("begin = " + begin);
    if (begin >= str.length) {
      list.add(new String(str));
//      System.out.println(list.toString());
    } else {
      for (int i = begin; i < str.length; i++) {
        if (str[begin] == str[i]) {
          getall(str, begin + 1, list);
        } else {
          char tmp = str[i];
          str[i] = str[begin];
          str[begin] = tmp;

          getall(str, begin + 1, list);

          str[begin] = str[i];
          str[i] = tmp;
        }
      }
    }
  }
}

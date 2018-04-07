package xiaozhao2017;

import java.util.Arrays;
import java.util.Scanner;

public class xiaomi {
}

class ReverseSentence {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    String sen = null;
    sen = "hello xiao mi";
//    sen = sc.nextLine();


    char[] s = sen.toCharArray();
    reverseStr(s, 0, s.length-1);

    int len = s.length;
    int left = 0, right;
    while (true) {
      while (left < len && s[left] == ' ')
        ++left;
      if (left >= len)
        break;
      right = left+1;

      while (right < len && s[right] != ' ')
        ++right;
      if (right < len)
        reverseStr(s, left, right-1);
      else
        reverseStr(s, left, len - 1);

      left = right+1;
    }
//    System.out.println(Arrays.toString(s));
    for (int i = 0; i < len; i++) {
      System.out.print(s[i]);
    }
  }

  static void reverseStr(char[] s, int left, int right) {
    while (left < right) {
      char c = s[left];
      s[left++] = s[right];
      s[right--] = c;
    }
  }
}

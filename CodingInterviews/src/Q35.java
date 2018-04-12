import java.util.Arrays;

public class Q35 {
  // 在一个字符串(1<=字符串长度<=10000，
  // 全部由字母组成)中找到第一个只出现一次的字符,并返回它的位置
  public static void main(String[] args) {
    System.out.println(FirstNotRepeatingChar("abaccdeff"));
  }

  public static int FirstNotRepeatingChar(String str) {
    if (str == null || str.length() <= 0)
      return -1;

    int[] countChar = new int[256];
//    System.out.println(Arrays.toString(countChar));

    for (int i = 0; i < str.length(); i++) {
      countChar[str.charAt(i)]++;
    }

    int i = 0;
    for (; i < str.length(); i++) {
      if (countChar[str.charAt(i)] == 1)
        break;
    }

    if (i == str.length())
      i = -1;

    return i;
  }
}

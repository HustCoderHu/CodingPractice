public class Q42_2 {
  // 翻转单词顺序
  public static void main(String[] args) {
    String str = "student. a am I";
    System.out.println(ReverseSentence(str));
  }

  public static String ReverseSentence(String str) {
    if (str == null || str.length() <= 0)
      return "";

    int st = 0, end = str.length() - 1;
    char[] cstr = str.toCharArray();

    while (st < end) {
      char c = cstr[st];
      cstr[st++] = cstr[end];
      cstr[end--] = c;
    }

    st = 0;
    while (st < cstr.length) {
      if (cstr[st] == ' ') {
        ++st;
        continue;
      }
      end = st + 1;
      while (end < cstr.length && cstr[end] != ' ')
        ++end;

      if (end <= cstr.length)
        reverseWord(cstr, st, end-1);

      st = end;
    }
    return String.valueOf(cstr);
  }

  static void reverseWord(char[] word, int st, int end) {
    while (st < end) {
      char c = word[st];
      word[st++] = word[end];
      word[end--] = c;
    }
  }
}

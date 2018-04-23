package leetcode;

public class _20ValidParentheses {
  public static void main(String[] args) {
    String s = "([)]";
    String s1 = "{[]}";
    System.out.println(isValid(s));
    System.out.println(isValid(s1));
  }
  public static boolean isValid(String s) {
    char[] stack = new char[s.length()];
    int len = 0;
    for (int i = 0; i < s.length(); i++) {
      char c = s.charAt(i);
      switch (c) {
        case '(':
          stack[len++] = ')';break;
        case '[':
          stack[len++] = ']';break;
        case '{':
          stack[len++] = '}';break;
        case ')':
        case ']':
        case '}':
          if (len > 0 && stack[len - 1] == c)
            --len;
          else
            return false;
      }
    }
    return len==0;
  }
}

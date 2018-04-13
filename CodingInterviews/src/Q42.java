public class Q42 {
  // 汇编语言中有一种移位指令叫做循环左移（ROL），现在有个简单的任务，
  // 就是用字符串模拟这个指令的运算结果。对于一个给定的字符序列S，
  // 请你把其循环左移K位后的序列输出。例如，字符序列S=”abcXYZdef”,
  // 要求输出循环左移3位后的结果，即“XYZdefabc”。是不是很简单？OK，搞定它！
  public static void main(String[] args) {
    String str = "abcXYZdef";
    int n = 3;

    System.out.println(LeftRotateString(str, n));
  }
  public static String LeftRotateString(String str,int n) {
    if (str == null || str.length()==0 || n < 0)
      return "";
    n %= str.length();

    char[] ca = new char[str.length()];

    int k = 0;
    for (int i = n; i < str.length(); i++)
      ca[k++] = str.charAt(i);

    int i = 0;
    while (k < ca.length)
      ca[k++] = str.charAt(i++);

    return String.valueOf(ca);
  }
}

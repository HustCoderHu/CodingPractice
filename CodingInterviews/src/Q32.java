public class Q32 {
  // 1 ~ n 中 1 出现的次数
  // n = 13
  // 1, 10, 11, 12, 13,  6次
  public static void main(String[] args) {
    System.out.println(NumberOf1Between1AndN_Solution(13));
    System.out.println(NumberOf1Between1AndN_Solution(10000)); // 4001
  }
  public static int NumberOf1Between1AndN_Solution(int n) {
    if (n <= 0)
      return 0;

    char[] str = String.valueOf(n).toCharArray();

    int cnt = numOf1(str, 0);
//    System.out.println("cnt = " + cnt);
    return cnt;
  }

  static int numOf1(char[] str, int idx) {
    if (idx == str.length)
      return 0;
    int first = str[idx] - '0';
    int len = str.length - idx;

    if (len==1 && first ==0)
      return 0;
    if (len==1 && first > 0)
      return 1;

    // 假设 str 是 "21345"
    // num1stDig 是数字 10000 ~ 19999 的第一位中1的数目
    int num1stDig = 0;
    if (first > 1)
      num1stDig = powBase10(len - 1);
    else if (first == 1)
      num1stDig = array2num(str, idx+1) + 1;

    // 1346 ~ 21345 除第一位外数位中1的数目
    int numOtherDig = first * powBase10(len - 2);
    // 1 ~ 1345 中的数目
    int numRecursive = numOf1(str, idx + 1);

    return num1stDig + numOtherDig + numRecursive;
  }
  static int array2num(char[] str, int idx) {
    if (idx >= str.length)
      return 0;
    int val = str[idx] - '0';

    for (int i = idx+1; i < str.length; i++) {
      val *= 10;
      val += str[idx];
    }
    return val;
  }

  static int powBase10(int n) {
    int res = 1;
    for (int i = 0; i < n; i++) {
      res *= 10;
    }
    return res;
  }
}

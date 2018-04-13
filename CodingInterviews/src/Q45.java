public class Q45 {
  // 圆圈中最后剩下的数字
  // 0 ~ n-1 从 0 开始删除第 m 个数字，求剩下的最后一个数字
  // 约瑟夫环
  public int LastRemaining_Solution(int n, int m) {
    if (n < 1 || m < 1)
      return -1;
    int last = 0;
    for (int i = 2; i <= n; i++) {
      last = (last+m)%i;
    }
    return last;
  }
}

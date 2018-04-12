public class Q34 {
  // 把只包含因子2、3和5的数称作丑数（Ugly Number）。
  // 例如6、8都是丑数，但14不是，因为它包含因子7。
  // 习惯上我们把1当做是第一个丑数。求按从小到大的顺序的第N个丑数。
  public static void main(String[] args) {
    System.out.println(GetUglyNumber_Solution(11));
  }

  public static int GetUglyNumber_Solution(int index) {
    if (index <= 0)
      return 0;

    int[] uglyNum = new int[index];
    int nextIdx = 0;

    uglyNum[nextIdx++] = 1;
    int i2 = 0, i3=0, i5=0;

    while (nextIdx < index) {
      int _min = Math.min(uglyNum[i2]*2, uglyNum[i3]*3);
      _min = Math.min(_min, uglyNum[i5]*5);
      uglyNum[nextIdx++] = _min;

      while (uglyNum[i2]*2 <= _min)
        ++i2;
      while (uglyNum[i3]*3 <= _min)
        ++i3;
      while (uglyNum[i5]*5 <= _min)
        ++i5;
    }
    return uglyNum[index-1];
  }
}

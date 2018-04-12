public class Q40 {
  // 一个整型数组里除了两个数字之外，其他的数字都出现了两次。请写程序找出这两个只出现一次的数字。
  //num1,num2分别为长度为1的数组。传出参数
//将num1[0],num2[0]设置为返回结果
  public static void FindNumsAppearOnce(int [] array,int num1[] , int num2[]) {
    if (array==null || array.length <2)
      return;
    int resXor = 0;
    for (int v : array)
      resXor ^= v;

    resXor ^= (resXor & (resXor - 1)); // 只留下最右边的 1
    num1[0] = num2[0] = 0;
    for (int v : array) {
      if ((v & resXor) == 0)
        num1[0] ^= v;
      else
        num2[0] ^= v;
    }
    return;
  }

  static boolean tstBit(int num, int idx) {
    num &= (1 << idx);
    return num != 0;
  }
}

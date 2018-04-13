import java.util.ArrayList;

public class Q41 {
  // 输出所有和为S的连续正数序列。序列内按照从小至大的顺序，序列间按照开始数字从小到大的顺序
  public static void main(String[] args) {
    FindContinuousSequence(5040);
  }

  public static ArrayList<ArrayList<Integer>> FindContinuousSequence(int sum) {
    ArrayList<ArrayList<Integer>> resList = new ArrayList<>();
    if (sum < 3)
      return resList;

    int small = 1;
    int big = 2;
    int curSum = small+big;

    while (small < big) {
      while (sum < curSum && small < big) {
        curSum -= small;
        small++;
      }
      if (small >= big)
        break;
      if (curSum < sum) {
        big++;
        curSum += big;
      }
      if (curSum == sum) {
        ArrayList<Integer> l = genList(small, big);
        System.out.println(l.toString());
        resList.add(l);
        big++;
        curSum += big;
      }
    }
    return resList;
  }

  static ArrayList<Integer> genList(int small, int big) {
    ArrayList<Integer> l = new ArrayList<>(big-small+1);
    for (; small <= big; ++small)
      l.add(small);

    return l;
  }
}

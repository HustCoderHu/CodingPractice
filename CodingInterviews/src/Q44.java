import java.util.Arrays;

public class Q44 {
  // 扑克牌顺子
  // 牛客 4个 王
  public static void main(String[] args) {
    int[] a = {0, 0, 5, 3, 1};
    System.out.println(isContinuous(a));
  }

  public static boolean isContinuous(int [] numbers) {
    if (numbers == null || numbers.length < 5)
      return false;

    Arrays.sort(numbers);
    int nZero = 0;

    for (int i = 0; i < numbers.length && numbers[i] == 0; i++) {
      ++nZero;
    }
    System.out.println("nZero = " + nZero);

    int i = nZero;
    int j = i+1;

    int nGap = 0;
    while (j < numbers.length) {
      if (numbers[i] == numbers[j])
        return false;
      nGap += numbers[j] - numbers[i] - 1;
      i = j++;
    }
    System.out.println("nGap = " + nGap);
    return nZero >= nGap;
  }
}

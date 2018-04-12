public class Q36 {
  // 在数组中的两个数字，如果前面一个数字大于后面的数字，
  // 则这两个数字组成一个逆序对。输入一个数组,求出这个数组中的逆序对的总数P。
  // 并将P对1000000007取模的结果输出。 即输出P%1000000007
  // 题目保证输入的数组中没有的相同的数字
  //
  //数据范围：
  //	对于%50的数据,size<=10^4
  //	对于%75的数据,size<=10^5
  //	对于%100的数据,size<=2*10^5

  static final int MOD = 1000000007;
  public static void main(String[] args) {
//    int[] array = {7, 5, 6, 4};   // 5
    int[] array = {1,2,3,4,5,6,7,0}; // 7

    System.out.println(InversePairs(array));
  }
  public static int InversePairs(int [] array) {
    if (array == null || array.length <= 0)
      return 0;

    int[] copy = new int[array.length];
    for (int i = 0; i < array.length; i++) {
      copy[i] = array[i];
    }

    return InversePairsCore(array, copy, 0, array.length - 1);
  }

  static int InversePairsCore(int[] data, int[] copy,
                              int start, int end) {
    if (start == end) {
      copy[start] = data[start];
      return 0;
    }
    int len = (end-start)/2;
    int left = InversePairsCore(copy, data, start, start + len);
    int right = InversePairsCore(copy, data, start + len + 1, end);

    // i 初始化为前半段最后一个数字的下标
    int i = start + len;
    // 后半段最后一个数字
    int j = end;
    int copyIdx = end;
    int cnt = 0;
    while (start <= i && start + len + 1 <= j) {
      if (data[i] > data[j]) {
        copy[copyIdx--] = data[i--];
        cnt += j - start -len;
      } else
        copy[copyIdx--] = data[j--];
    }

    for (; start <= i; --i)
      copy[copyIdx--] = data[i];
    for (; start+len+1 <= j; --j)
      copy[copyIdx--] = data[j];

    cnt = (cnt+left)%MOD;
    cnt = (cnt+right)%MOD;
    return  cnt;
  }
}

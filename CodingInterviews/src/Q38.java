public class Q38 {
  // 统计一个数字在排序数组中出现的次数。
  public static void main(String[] args) {
    int[] array = {1, 2, 3, 3, 3, 3, 4, 5};
    int k = 3;

    System.out.println(GetNumberOfK(array, k));
  }
  public static int GetNumberOfK(int [] array , int k) {
    if (array== null || array.length <= 0)
      return 0;

    int cnt = 0;
    int first = get1stK(array, k, 0, array.length - 1);
    int last = -1;
    if (first!=-1)
      last = getLastK(array, k, first, array.length-1);
    if (last!=-1)
      cnt = last-first+1;

    System.out.println("first = " + first);
    System.out.println("last = " + last);
    return cnt;
  }

  static int get1stK(int[] a, int k, int st, int end) {
    if (st > end)
      return -1;
    int mid = st + (end -st)/2;
    int midVal = a[mid];

    if (midVal == k) {
      if ((mid > 0 && a[mid-1]!=k)
              || mid == 0)
        return mid;
      else
        end = mid-1;
    } else if (k < midVal)
      end = mid - 1;
    else
      st = mid+1;
    return get1stK(a, k, st, end);
  }

  static int getLastK(int[] a, int k, int st, int end) {
    if (st > end)
      return -1;

    int mid = st + (end - st) / 2;
    int midVal = a[mid];

    if (midVal == k) {
      if ((mid+1 < a.length && a[mid+1]!=k)
              || mid+1 == a.length)
        return mid;
      else
        st = mid+1;
    } else if (k < midVal)
      end = mid-1;
    else
      st = mid+1;

    return getLastK(a, k, st, end);
  }
}

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.PriorityQueue;

public class Q30 {
  // 输入n个整数，找出其中最小的K个数。例如输入4,5,1,6,2,7,3,8这8个数字，
  // 则最小的4个数字是1,2,3,4,。
  public static void main(String[] args) {
    int[] in = {4, 5, 1, 6, 2, 7, 3, 8};
    int k = 4;
    ArrayList<Integer> arrayList = GetLeastNumbers_Solution(in, k);
//    System.out.println(arrayList.toString());
  }

  public static ArrayList<Integer> GetLeastNumbers_Solution(int [] input, int k) {
    if (input == null || k <= 0 || input.length <= 0
            || input.length < k)
      return new ArrayList<Integer>();

    return On(input, k);
//    return nlogk(input, k);
  }

  static ArrayList<Integer> On(int[] input, int k) {
    int st = 0, end = input.length - 1;
    int idx = partition(input, st, end);
//    System.out.println("idx = " + idx);
//    System.out.println(Arrays.toString(input));

    while (idx != k - 1) {
      if (idx < k - 1)
        st = idx+1;
      else
        end = idx-1;

//      System.out.println("st = " + st);
//      System.out.println("end = " + end);
      idx = partition(input, st, end);
//      System.out.println("idx = " + idx);
//      System.out.println(Arrays.toString(input));
    }
    ArrayList<Integer> arrayList = new ArrayList<>(k);
    for (int i = 0; i < k; i++) {
      arrayList.add(input[i]);
    }
    return arrayList;
  }

  static int partition(int[] in, int st, int end) {
    int p = in[st];

    while (st < end) {
      while (st < end && p <= in[end])
        --end;
      in[st] = in[end];

      while (st < end && in[st] <= p)
        ++st;
      in[end] = in[st];
    }
    in[st] = p;
    return p;
  }

  static ArrayList<Integer> nlogk(int[] input, int k) {

//    Comparator<Integer> comp = new Comparator<>() {
//      @Override
//      public int compare(Integer o1, Integer o2) {
//        return o1 - o2;
//      }
//    };
//    PriorityQueue<Integer> bigheap = new PriorityQueue<>(k, comp);
    PriorityQueue<Integer> bigheap = new PriorityQueue<>(k, (o1, o2) -> o2-o1);

    for (int i = 0; i < input.length; i++) {
      if (bigheap.size() < k) {
        bigheap.add(input[i]);

      } else if (input[i] < bigheap.peek()) {
        bigheap.poll();
        bigheap.add(input[i]);
      }
    }
    ArrayList<Integer> arrayList = new ArrayList<>(k);
    for (Integer v : bigheap)
      arrayList.add(v);

    return arrayList;
  }
}

import java.util.ArrayList;
import java.util.PriorityQueue;

public class Q65 {
  // 滑动窗口的最大值
  public static void main(String[] args) {
    int[] a = {2,3,4,2,6,2,5,1};
    int size = 3;
    // 4, 4, 6, 6, 6, 5
    System.out.println(maxInWindows(a, size).toString());
  }
  static public ArrayList<Integer> maxInWindows(int [] num, int size)
  {
//    ArrayDeque deq = new ArrayDeque(num.length);
    return heapSolve(num, size);
  }

  static ArrayList<Integer> heapSolve(int [] num, int size) {
    ArrayList<Integer> ar = new ArrayList<>();
    if (num==null || num.length <= 0
            || size <= 0 || size>num.length)
      return ar;

    PriorityQueue<Integer> heap = new PriorityQueue<>(size, (o1, o2) -> o2-o1);
    for (int i = 0; i < size; i++) {
      heap.add(num[i]);
    }
    ar.add(heap.peek());

    for (int i = 1; i+size-1 < num.length; i++) {
      heap.remove(num[i-1]);
      heap.add(num[i+size-1]);
      ar.add(heap.peek());
    }
    return ar;
  }
}

// <https://github.com/CyC2018/Interview-Notebook/blob/master/notes/%E5%89%91%E6%8C%87%20offer%20%E9%A2%98%E8%A7%A3.md#59-%E6%BB%91%E5%8A%A8%E7%AA%97%E5%8F%A3%E7%9A%84%E6%9C%80%E5%A4%A7%E5%80%BC>
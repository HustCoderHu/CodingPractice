import java.util.PriorityQueue;

public class Q64 {
  // 数据流中的中位数

  PriorityQueue<Integer> left = new PriorityQueue<>((o1, o2) -> o2 - o1);
  PriorityQueue<Integer> right = new PriorityQueue<>();
  int n = 0;

  public void Insert(Integer num) {
    if ((n & 0x1) == 0) {
      // 偶数个去右边
      // 右边比左边大
      if (left.isEmpty())
        right.add(num);
      else if (num >= left.peek())
        right.add(num);
      else {
        right.add(left.poll());
        left.add(num);
      }
    } else {
      if (num < right.peek())
        left.add(num);
      else {
        left.add(right.poll());
        right.add(num);
      }
    }
    ++n;
  }

  public Double GetMedian() {
    if (left.size() == right.size()) {
      return (left.peek().doubleValue()+right.peek().doubleValue()) / 2;
    } else
      return right.peek().doubleValue();
  }
}

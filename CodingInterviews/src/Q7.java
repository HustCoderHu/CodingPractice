import java.util.ArrayDeque;
import java.util.Stack;

public class Q7 {
  // 两个栈实现队列
  public static void main(String[] args) {
    Q7 q = new Q7();
    q.push(4);
    q.push(3);
    q.push(2);
    q.push(1);

    int val;
    val = q.pop();
    System.out.println("val = " + val);
    val = q.pop();
    System.out.println("val = " + val);
    val = q.pop();
    System.out.println("val = " + val);
    val = q.pop();
    System.out.println("val = " + val);

  }
  Stack<Integer> stack1 = new Stack<Integer>();
  Stack<Integer> stack2 = new Stack<Integer>();
//  ArrayDeque<Integer> stack1 = new ArrayDeque<>();
//  ArrayDeque<Integer> stack2 = new ArrayDeque<>();

  public void push(int node) {
    stack1.push(node);
  }

  public int pop() {
    int retVal = -1;
//    if (stack1.empty() && stack2.empty()) {
    if (stack1.isEmpty() && stack2.isEmpty()) {
      try {
        throw new Exception("queue is empty");
      } catch (Exception e) {
        e.printStackTrace();
      }
    } else {
//      if (!stack2.empty()) {
      if (!stack2.isEmpty()) {
        retVal = stack2.pop();
      } else {
//        while (!stack1.empty())
        while (!stack1.isEmpty())
          stack2.push(stack1.pop());
        retVal = stack2.pop();
      }
    }
    return retVal;
  }
}

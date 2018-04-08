import java.util.Stack;

public class Q21 {
}

class MyStack {
  private Stack<Integer> stack = new Stack<>();
  private Stack<Integer> helper = new Stack<>();


  public void push(int node) {
    if (stack.isEmpty()) {
      stack.push(node);
      helper.push(node);
      return;
    }
    stack.push(node);
    int curMin = helper.peek();
    if (node < curMin)
      helper.push(node);
    else
      helper.push(curMin);
  }

  public void pop() {
    if (!stack.isEmpty()) {
      stack.pop();
      helper.pop();
    }
  }

  public int top() {
    if (!stack.isEmpty()) {
      helper.pop();
      return stack.pop();
    }
    return 0;
  }

  public int min() {
    if (!stack.isEmpty()) {
      return helper.peek();
    }
    return 0;
  }
}
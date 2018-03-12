import java.util.ArrayDeque;

public class Q22 {
  // 输入两个整数序列，第一个序列表示栈的压入顺序，
  // 请判断第二个序列是否为该栈的弹出顺序。假设压入栈的所有数字均不相等。
  // 例如序列1,2,3,4,5是某栈的压入顺序，序列4，5,3,2,1是该压栈序列对应的一个弹出序列，
  // 但4,3,5,1,2就不可能是该压栈序列的弹出序列。（注意：这两个序列的长度是相等的）

  public static void main(String[] args) {
    int[] push = {1, 2, 3, 4, 5};
    int[] pop = {4, 5, 3, 2, 1};
    int[] pop2 = {4, 3, 5, 1, 2};

    System.out.println(IsPopOrder(null, null));
    System.out.println(IsPopOrder(null, new int[0]));
    System.out.println(IsPopOrder(new int[0], null));
    System.out.println(IsPopOrder(push, pop));
    System.out.println(IsPopOrder(push, pop2));
  }

  public static boolean IsPopOrder(int [] pushA,int [] popA) {
    if ((pushA == null && popA == null)
            ||(pushA == null && popA != null)
            || (pushA != null && popA == null)
            || pushA.length != popA.length)
      return false;

    int len = pushA.length;
    if (len == 0)
      return true;

    boolean retVal = false;
    ArrayDeque<Integer> stack = new ArrayDeque<>(len);

    int i = 0;
    int j = 0;

    while (j < len) {
      // 压栈序列里找，找不到就一直push
      while (i < len && pushA[i] != popA[j]) {
        stack.push(pushA[i]); // add first
        ++i;
      }
      if (i == len) // 没找到，失败
        break;
      else {// 找到，再找下一个
        ++i;
        ++j;
      }
      // 栈顶正好是
      while (!stack.isEmpty() && stack.peekFirst() == popA[j]) {
        stack.pop();
        ++j;
      }
    }
    if (j == len)
      retVal = true;

    return retVal;
  }
}

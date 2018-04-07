package leetcode;
import java.util.*;

public class ReversePolishNotation {
  public static void main(String[] args) {
    String[] tokes = {"2", "1", "+", "3", "*"};
    String[] tokes1 = {"4", "13", "5", "/", "+"};
    String[] tokes2 = {"0","3","/"};

//    evalRPN(tokes);
//    evalRPN(tokes1);
    evalRPN(tokes2);
  }
  public static int evalRPN(String[] tokens) {
    int[] stack = new int[tokens.length];
    int stackLen = 0;

    for (int i = 0; i < tokens.length; i++) {
      int op0;
      int op1;
      if (tokens[i].equals("+")) {
        op1 = stack[--stackLen];
//        if (stackLen == 0) {
//          throw new Exception("error");
//        }
        op0 = stack[stackLen-1];
        stack[stackLen-1] = op0 + op1;

      } else if (tokens[i].equals("-")) {
        op1 = stack[--stackLen];
        op0 = stack[stackLen-1];
        stack[stackLen-1] = op0 - op1;

      } else if (tokens[i].equals("*")) {
        op1 = stack[--stackLen];
        op0 = stack[stackLen-1];
        stack[stackLen-1] = op0 * op1;

      } else if (tokens[i].equals("/")) {
        op1 = stack[--stackLen];
        op0 = stack[stackLen - 1];
        stack[stackLen - 1] = op0 / op1;

      } else {
        stack[stackLen++] = Integer.valueOf(tokens[i]);
      }
    }
    System.out.println(Arrays.toString(stack));
    return stack[0];
  }
}

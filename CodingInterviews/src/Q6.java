
import java.util.*;
import BaseAlgorithm.TreeNode;

public class Q6 {
  // 重构二叉树
  // 输入先序和中序
  public static void main(String[] args) {
//    int[] pre = new int[0];
//    System.out.println(pre.length);
//    System.out.println(pre);

    int[] pre = {1, 2, 4, 7, 3, 5, 6, 8};
    int[] in = {4, 7, 2, 1, 5, 3, 8, 6};

    TreeNode root = reConstructBinaryTree(pre, in);
//    System.out.println("root = " + root);
//    System.out.println(root.left);
//    System.out.println(root.right);
//    System.out.println(root.getDepth());
//    displayTree(root, pre.length);
    TreeNode.displayTree(root);
  }

  public static TreeNode reConstructBinaryTree(int[] pre, int[] in) {
    TreeNode root = null;
    try {
      root = constructCore(pre, in, 0, pre.length - 1,
              0, in.length - 1);
    } catch (Exception e) {
      System.out.println(e.getMessage());
    }
    return root;
  }

  public static TreeNode nonRecurseReConstructBTree(int[] pre, int[] in) {
    if (pre == null || in == null
            || pre.length == 0 || in.length == 0
            || pre.length != in.length)
      return null;

//    in.
    // 构建左右关系
    Map<Integer, Integer> val2idx = new HashMap<>();
    int len = in.length;
    for (int i = 0; i < len; i++)
      val2idx.put(in[i], i);

//    TreeNode root = new TreeNode(pre[0]);
//    root.left = null;
//    root.right = null;


    return null;
  }

  public static TreeNode constructCore(int[] pre, int[] in,
                                       int preLeft, int preRight,
                                       int inLeft, int inRight)
          throws Exception {
    int rootVal = pre[preLeft];
    TreeNode node = new TreeNode(rootVal);

    if (preLeft == preRight) {
      if (inLeft == inRight
              && pre[preLeft] == in[inLeft])
        return node;
      else
        throw new Exception("Invalid input");
    }
    int rootInorder = inLeft;
    while (rootInorder <= inRight && in[rootInorder] != rootVal)
      ++rootInorder;
    if (rootInorder == inRight + 1) {
      throw new Exception("Invalid input 2");
    }

    int leftLen = rootInorder - inLeft;
    int leftPreEnd = preLeft + leftLen;
    if (leftLen > 0) {
      // 构建左子树
      node.setLeft(constructCore(pre, in, preLeft + 1, leftPreEnd,
              inLeft, rootInorder - 1));
    }
    if (leftLen < preRight - preLeft) {
      // 构建右子树
      node.setRight(constructCore(pre, in, leftPreEnd + 1, preRight,
              rootInorder + 1, inRight));
    }
    return node;
  }
}


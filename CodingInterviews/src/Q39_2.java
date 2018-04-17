import BaseAlgorithm.TreeNode;

public class Q39_2 {
  // 输入一棵二叉树，判断该二叉树是否是平衡二叉树
  public boolean IsBalanced_Solution(TreeNode root) {
    Depth d = new Depth();
    return isBalanced(root, d);
  }

  static boolean isBalanced(TreeNode root, Depth d) {
    if (root == null) {
      d.depth = 0;
      return true;
    }
    Depth left = new Depth();
    Depth right = new Depth();
    if (isBalanced(root.left, left)
            && isBalanced(root.right, right)) {
      int diff = left.depth - right.depth;
      if (-1 <= diff && diff <= 1) {
        d.depth = 1 + (left.depth > right.depth? left.depth : right.depth);
        return true;
      }
    }
    return false;
  }
}

class Depth {
  public int depth = 0;
}


import BaseAlgorithm.*;

import java.util.ArrayDeque;
import java.util.ArrayList;

public class Q23 {
  // 从上往下打印出二叉树的每个节点，同层节点从左至右打印。
  public static void main(String[] args) {
    ArrayList<TreeNode> q = new ArrayList<>();
  }

  public static ArrayList<Integer> PrintFromTopToBottom(TreeNode root) {
    if (root == null)
      return new ArrayList<Integer>();
    ArrayDeque<TreeNode> q = new ArrayDeque<>();
    ArrayList<Integer> res = new ArrayList<>();

    q.addLast(root);
//    res.add(root.val);
    while (!q.isEmpty()) {
      TreeNode tmp = q.pollFirst();
      res.add(tmp.val);
      if (tmp.left != null)
        q.addLast(tmp.left);
      if (tmp.right != null)
        q.addLast(tmp.right);
    }
    return res;
  }
}

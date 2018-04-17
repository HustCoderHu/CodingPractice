import BaseAlgorithm.TreeNode;

import java.util.ArrayList;

public class Q60 {
  // 从上到下按层打印二叉树，同一层结点从左至右输出。每一层输出一行。

  ArrayList<ArrayList<Integer>> Print(TreeNode pRoot) {
    ArrayList<ArrayList<Integer>> res = new ArrayList<>();

    if (pRoot == null)
      return res;

    ArrayList<TreeNode> upper = new ArrayList<>();
    ArrayList<TreeNode> lower = new ArrayList<>();
    ArrayList<TreeNode> tmp = null;
    upper.add(pRoot);

    while (!upper.isEmpty()) {
      ArrayList<Integer> t = new ArrayList<>(upper.size());
      for (TreeNode nod : upper) {
        t.add(nod.val);
        if (nod.left != null)
          lower.add(nod.left);
        if (nod.right != null)
          lower.add(nod.right);
      }
      res.add(t);

      tmp = upper;
      upper = lower;
      lower = tmp;

      lower.clear();
    }
    return res;
  }
}

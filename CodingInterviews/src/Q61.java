import BaseAlgorithm.TreeNode;

import java.util.ArrayList;
import java.util.Collections;

public class Q61 {
  // 请实现一个函数按照之字形打印二叉树，即第一行按照从左到右的顺序打印，
  // 第二层按照从右至左的顺序打印，第三行按照从左到右的顺序打印，其他行以此类推。
  public ArrayList<ArrayList<Integer>> Print(TreeNode pRoot) {
    ArrayList<ArrayList<Integer>> res = new ArrayList<>();

    if (pRoot == null)
      return res;

    ArrayList<TreeNode> upper = new ArrayList<>();
    ArrayList<TreeNode> lower = new ArrayList<>();
    ArrayList<TreeNode> tmp = null;
    upper.add(pRoot);
    boolean right2left = false;

    while (!upper.isEmpty()) {
      ArrayList<Integer> t = new ArrayList<>(upper.size());
      for (TreeNode nod : upper) {
        t.add(nod.val);
        if (nod.left != null)
          lower.add(nod.left);
        if (nod.right != null)
          lower.add(nod.right);
      }
      if (right2left)
        Collections.reverse(t);
      res.add(t);
      right2left = !right2left;

      tmp = upper;
      upper = lower;
      lower = tmp;

      lower.clear();
    }
    return res;
  }
}

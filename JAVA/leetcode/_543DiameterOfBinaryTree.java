package leetcode;

import java.util.LinkedList;
import java.util.List;

public class _543DiameterOfBinaryTree {
  static List<Integer> nodeDepth;
  public int diameterOfBinaryTree(TreeNode root) {
    nodeDepth = new LinkedList<>();
    if (root == null)
      return 0;
    getAndSet(root);

    Integer max = 0;
    for (Integer v : nodeDepth)
      max = v>max? v : max;
    return max.intValue();
  }

  static int getAndSet(TreeNode root) {
    if (root == null)
      return 0;
    int ldep = getAndSet(root.left);
    int rdep = getAndSet(root.right);
    nodeDepth.add(ldep + rdep);
    return Math.max(ldep, rdep)+1;
  }
}

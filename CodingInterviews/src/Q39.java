import BaseAlgorithm.Tree;

public class Q39 {
  // 输入一棵二叉树，求该树的深度。从根结点到叶结点依次经过的结点
  // （含根、叶结点）形成树的一条路径，最长路径的长度为树的深度。
  public static int TreeDepth(Tree root) {
    if (root==null)
      return 0;
    int nL = TreeDepth(root.left);
    int nR = TreeDepth(root.right);
    return (nL > nR) ? (nL + 1) : (nR + 1);
  }
}

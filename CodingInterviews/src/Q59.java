import BaseAlgorithm.TreeNode;

public class Q59 {
  // 请实现一个函数，用来判断一颗二叉树是不是对称的。
  // 注意，如果一个二叉树同此二叉树的镜像是同样的，定义其为对称的。
  public static void main(String[] args) {

  }
  boolean isSymmetrical(TreeNode pRoot)
  {
    if (pRoot == null)
      return true;
    return isSym(pRoot.left, pRoot.right);
  }

  static boolean isSym(TreeNode r1, TreeNode r2) {
    if (r1 == null && r2 == null)
      return true;
    if (r1 == null || r2 == null)
      return false;

    if (r1.val != r2.val)
      return false;

    return isSym(r1.left, r2.right) && isSym(r1.right, r2.left);
  }
}

package leetcode;

public class _98ValidateBinarySearchTree {
  static int bstmin;
  static int bstmax;

  public static boolean isValidBST(TreeNode root) {
    if (root == null)
      return true;

    int tmin;
    if (root.left != null) {
      if (isValidBST(root.left)==false || root.val<=bstmax)
        return false;
      tmin = bstmin;
    } else
      tmin = root.val;

    int tmax;
    if (root.right != null) {
      if (isValidBST(root.right)==false || bstmin <= root.val)
        return false;
      tmax = bstmax;
    } else
      tmax = root.val;

    bstmin = tmin;
    bstmax = tmax;
    return true;
  }
}

import BaseAlgorithm.*;

public class Q27 {
  // 输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的双向链表。
  // 要求不能创建任何新的结点，只能调整树中结点指针的指向。
  public static void main(String[] args) {
    TreeNode root = new TreeNode(10);
    root.setLeft(new TreeNode(6));
    root.setRight(new TreeNode(14));

    TreeNode left = root.left;
    left.setLeft(new TreeNode(4));
//    left.setRight(new TreeNode(8));
    TreeNode right = root.right;
    right.setLeft(new TreeNode(12));
//    right.setRight(new TreeNode(16));

    root.show();

//    Convert(root);
  }
//  static TreeNode Convert(TreeNode pRootOfTreeNode) {
  static TreeNode Convert(TreeNode pRootOfTreeNode) {
    TreeNode lastNod = null;
    cvtNode(pRootOfTreeNode, lastNod);
    lastNod = pRootOfTreeNode;
    while (lastNod!=null && lastNod.left!=null)
      lastNod = lastNod.left;

    while (lastNod != null) {
      System.out.print(lastNod.val + " ");
    }
    return lastNod;
  }

  static TreeNode cvtNode(TreeNode nod, TreeNode lastNod) {
    if (nod == null) {
      return null;
    }
    TreeNode cur = nod;
    if (cur.left !=null)
      lastNod = cvtNode(cur.left, lastNod);
    cur.left = lastNod;

    if (lastNod != null)
      lastNod.right = cur;

    lastNod = cur;
    if (cur.right != null)
      lastNod = cvtNode(cur.right, null);

    return lastNod;
  }
}

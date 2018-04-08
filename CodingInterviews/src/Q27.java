import BaseAlgorithm.*;

public class Q27 {
  // 输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的双向链表。
  // 要求不能创建任何新的结点，只能调整树中结点指针的指向。
  public static void main(String[] args) {
    Tree root = new Tree(10);
    root.setLeft(new Tree(6));
    root.setRight(new Tree(14));

    Tree left = root.left;
    left.setLeft(new Tree(4));
    left.setRight(new Tree(8));
    Tree right = root.right;
    right.setLeft(new Tree(12));
    right.setRight(new Tree(16));

    root.show();

    Convert(root);
  }
//  static TreeNode Convert(TreeNode pRootOfTree) {
  static Tree Convert(Tree pRootOfTree) {
    Tree lastNod = null;
    cvtNode(pRootOfTree, lastNod);
    lastNod = pRootOfTree;
    while (lastNod!=null && lastNod.left!=null)
      lastNod = lastNod.left;

    while (lastNod != null) {
      System.out.print(lastNod.val + " ");
    }
    return lastNod;
  }

  static Tree cvtNode(Tree nod, Tree lastNod) {
    if (nod == null) {
      return null;
    }
    Tree cur = nod;
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

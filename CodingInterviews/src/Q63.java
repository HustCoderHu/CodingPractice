import BaseAlgorithm.TreeNode;

public class Q63 {
  // 给定一颗二叉搜索树，请找出其中的第k大的结点。
  // 例如， 5 / \ 3 7 /\ /\ 2 4 6 8 中，
  // 按结点数值大小顺序第三个结点的值为4。

  public static void main(String[] args) {
    TreeNode root = new TreeNode(8);
    root.setLeft(new TreeNode(6));
    root.setRight(new TreeNode(10));

    TreeNode left = root.left;
    left.setLeft(new TreeNode(5));
    left.setRight(new TreeNode(7));
    TreeNode right = root.right;
    right.setLeft(new TreeNode(9));
    right.setRight(new TreeNode(11));
    root.show();

    TreeNode.flipTree(root);

    System.out.println(KthNode(root, 1).val);
  }

  // 牛客要去掉 static 才能通过
  static int cnt = 0;
  static int sk = 0;
  static TreeNode ret = null;

  static TreeNode KthNode(TreeNode pRoot, int k)
  {
    sk = k;
    inOrder(pRoot);
//    if (pRoot == null)
//      return null;
//    if (cnt >= k)
//      return null;
//    KthNode(pRoot.left, k);
//    ++cnt;
//    if (cnt == k) {
//      ret = pRoot;
//      return pRoot;
//    }
//    KthNode(pRoot.right, k);
    return ret;
  }
  static void inOrder(TreeNode root) {
    if (root == null)
      return;
    if (cnt >= sk)
      return;
    inOrder(root.left);
    ++cnt;
    if (cnt == sk) {
      ret = root;
      return;
    }
    inOrder(root.right);
  }
}

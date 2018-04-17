import BaseAlgorithm.TreeLinkNode;

public class Q58 {
  // 给定一个二叉树和其中的一个结点，
  // 请找出中序遍历顺序的下一个结点并且返回。
  // 注意，树中的结点不仅包含左右子结点，同时包含指向父结点的指针。
  public TreeLinkNode GetNext(TreeLinkNode pNode)
  {
    if (pNode == null ||
            (pNode.right==null && pNode.next==null))
      // 没有右子树的根
      return null;

    // 右子树的最左结点
    if (pNode.right != null) {
      TreeLinkNode leftest = pNode.right;
      while (leftest.left != null) {
        leftest = leftest.left;
      }
      return leftest;
    }
    // 没有右子树 而且本身是某个结点X的左子树
    // X就是所求
    if (pNode.next!=null && pNode==pNode.next.left)
      return pNode.next;

    // 本身是 X 的右子树
    TreeLinkNode next = pNode.next;
    while (next != null) {
      if (pNode == next.left)
        return next;
      pNode = next;
      next = next.next;
    }
    return null;
  }
}

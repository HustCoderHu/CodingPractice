import jdk.nashorn.api.tree.Tree;

import java.util.*;

public class Q6 {
  // 重构二叉树
  // 输入先序和中序
  public static void main(String[] args) {
//    int[] pre = new int[0];
//    System.out.println(pre.length);
//    System.out.println(pre);

    int[] pre = {1, 2, 4, 7, 3, 5, 6, 8};
    int[] in = {4, 7, 2, 1, 5, 3, 8, 6};

    TreeNode root = reConstructBinaryTree(pre, in);
//    System.out.println("root = " + root);
//    System.out.println(root.left);
//    System.out.println(root.right);
//    System.out.println(root.getDepth());
//    displayTree(root, pre.length);
    TreeNode.flipTree(root);
    TreeNode.displayTree(root);
  }

  public static TreeNode reConstructBinaryTree(int[] pre, int[] in) {
    TreeNode root = null;
    try {
      root = constructCore(pre, in, 0, pre.length - 1,
              0, in.length - 1);
    } catch (Exception e) {
      System.out.println(e.getMessage());
    }
    return root;
  }

  public static TreeNode nonRecurseReConstructBTree(int[] pre, int[] in) {
    if (pre == null || in == null
            || pre.length == 0 || in.length == 0
            || pre.length != in.length)
      return null;

//    in.
    // 构建左右关系
    Map<Integer, Integer> val2idx = new HashMap<>();
    int len = in.length;
    for (int i = 0; i < len; i++)
      val2idx.put(in[i], i);

    TreeNode root = new TreeNode(pre[0]);
    root.left = null;
    root.right = null;


    return null;
  }

  public static TreeNode constructCore(int[] pre, int[] in,
                                       int preLeft, int preRight,
                                       int inLeft, int inRight)
          throws Exception {
    int rootVal = pre[preLeft];
    TreeNode node = new TreeNode(rootVal);

    if (preLeft == preRight) {
      if (inLeft == inRight
              && pre[preLeft] == in[inLeft])
        return node;
      else
        throw new Exception("Invalid input");
    }
    int rootInorder = inLeft;
    while (rootInorder <= inRight && in[rootInorder] != rootVal)
      ++rootInorder;
    if (rootInorder == inRight + 1) {
      throw new Exception("Invalid input 2");
    }

    int leftLen = rootInorder - inLeft;
    int leftPreEnd = preLeft + leftLen;
    if (leftLen > 0) {
      // 构建左子树
      node.left = constructCore(pre, in, preLeft + 1, leftPreEnd,
              inLeft, rootInorder - 1);
    }
    if (leftLen < preRight - preLeft) {
      // 构建右子树
      node.right = constructCore(pre, in, leftPreEnd + 1, preRight,
              rootInorder + 1, inRight);
    }
    return node;
  }

  static void displayTree(TreeNode root, int capacity) {
    Queue<TreeNode> q = new LinkedList<>();
    List<String> outStr = new ArrayList<>(capacity);

    q.offer(root);
    int bound = 1;
    int cnt = 0;
    while (!q.isEmpty()) {
      TreeNode tmp = q.poll();

//      if (tmp == null)
//        outStr.add(String.valueOf(0));
//      else
//        outStr.add(String.valueOf(tmp.val));
//      q.offer(tmp.left);
//      q.offer(tmp.right);

      outStr.add(String.valueOf(tmp.val));
      if (tmp.val == 0) {
        // 根节点为 null 左右都null
        q.offer(new TreeNode(0));
        q.offer(new TreeNode(0));
      } else {
        if (tmp.left == null)
          q.offer(new TreeNode(0));
        else
          q.offer(tmp.left);

        if (tmp.right == null)
          q.offer(new TreeNode(0));
        else
          q.offer(tmp.right);
      }

//      if (tmp.left != null)
//        q.offer(tmp.left);
//      else {
//        q.offer(tmp.left);
//      }
//        outStr.add(String.valueOf(0));
//
//      if (tmp.right != null)
//        q.offer(tmp.right);
//      else
//        outStr.add(String.valueOf(0));

      ++cnt;
      if (cnt == bound) {
        outStr.add("\n");
        System.out.println();
        bound = bound * 2 + 1; // 等比数列递推 1 3 7
      }
    }
    System.out.println(outStr);
  }

  static int idxByVal(int[] arr, int begin, int end, int val) {
    int len = arr.length;
//    for (int i = 0; i < len)
    for (int i = begin; i < end; i++) {
      if (arr[i] == val) {
        return i;
      }
    }
    return -1;
  }
}

/**
 * Definition for binary tree
 */
class TreeNode {
  int val;
  TreeNode left;
  TreeNode right;

  int depth;

  TreeNode(int x) {
    val = x;
//    depth = getDepth();
  }

  public int getDepth() {
    int nLeft = _getDepth(left);
    int nRight = _getDepth(right);
    return nLeft > nRight ? nLeft + 1 : nRight + 1;
  }

  public static int _getDepth(TreeNode node) {
    if (node == null)
      return 0;
    int nLeft = _getDepth(node.left);
    int nRight = _getDepth(node.right);
    return nLeft > nRight ? nLeft + 1 : nRight + 1;
  }

  static TreeNode flipTree(TreeNode node) {
    if (node == null)
      return null;
    TreeNode flippedLeft = flipTree(node.left);
    TreeNode flippedRight = flipTree(node.right);
    node.left = flippedRight;
    node.right = flippedLeft;
    return node;
  }

  static void displayTree(TreeNode node) {
    final int markVal = 0;

    node.depth = node.getDepth();


    int maxNnode = (int) Math.pow(2, node.depth) - 1;
    int bottomN = (int) Math.pow(2, node.depth - 1);
    // 分层存储
    ArrayList<String> outStr = new ArrayList<>(maxNnode);
    ArrayList<TreeNode> nodeArrSrc = new ArrayList<>(bottomN);
    ArrayList<TreeNode> nodeArrDst = new ArrayList<>(bottomN);
//    ArrayList<TreeNode> nodeArrTmp = null;
//    nodeArrSrc.ensureCapacity(bottomN);
//    nodeArrDst.ensureCapacity(bottomN);

    nodeArrSrc.add(node);

    for (int i = 0; i < node.depth; i++) {
      // 第 i 层
      for (TreeNode nod : nodeArrSrc) {
        // 记录当前层内容
        if (nod.val != markVal) {
          outStr.add(String.valueOf(nod.val));
          // 保存下一层结点
          if (nod.left == null)
            nodeArrDst.add(new TreeNode(markVal));
          else
            nodeArrDst.add(nod.left);

          if (nod.right == null)
            nodeArrDst.add(new TreeNode(markVal));
          else
            nodeArrDst.add(nod.right);
        }
        else {
          outStr.add("*");
          nodeArrDst.add(new TreeNode(markVal));
          nodeArrDst.add(new TreeNode(markVal));
        }
      }
      // 更新当前层为下层
      nodeArrSrc.clear();
      nodeArrSrc.addAll(nodeArrDst);
      nodeArrDst.clear();
    }

    int bound = 1;
    int cnt = 1;

    int depth = node.depth;
    Collections.reverse(outStr);

    ArrayList<String> finalStr = new ArrayList<>(maxNnode);

    boolean layerStart = true;
    StringBuilder lineBeginPadSpace = new StringBuilder();
    StringBuilder interPadSpace = new StringBuilder();
    lineBeginPadSpace.append(' ');
    interPadSpace.append(' ');
    
    int nLayerNode = 0;
    int nodIdx = 0;
    for (String str : outStr) {
      if (layerStart) {
        // 0 + 1 + 2 + 4
        // pow(2, n) - 1
//        int nSpace = (int) Math.pow(2, node.depth - depth) - 1;
        System.out.print(lineBeginPadSpace);
        lineBeginPadSpace.append(lineBeginPadSpace);
        lineBeginPadSpace.append(' ');

        interPadSpace.append(interPadSpace);
        interPadSpace.append(' ');

        layerStart = false;
        nLayerNode = (int) Math.pow(2, depth - 1);
        nodIdx = 1;
      }

      System.out.print(str);
      System.out.print(interPadSpace);


      if (nodIdx == nLayerNode) {
        // 层最后一个node 也输出了
        System.out.println();
        --depth;
        layerStart = true;
        continue;
      }
      nodIdx++;
    }


//    for (String str : outStr) {
//      System.out.print(str);
//      if (cnt == bound) {
//        System.out.println();
//        bound = bound * 2 + 1; // 等比数列递推 1 3 7
//      }
//      ++cnt;
//    }
  }
}

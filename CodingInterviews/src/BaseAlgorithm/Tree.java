package BaseAlgorithm;

import java.util.ArrayList;
import java.util.Collections;

public class Tree {
  private int val;
  private Tree left;
  private Tree right;

  int depth;

  public Tree(int x) {
    val = x;
//    depth = getDepth();
  }

  public void setLeft(Tree left) {
    this.left = left;
  }

  public void setRight(Tree right) {
    this.right = right;
  }

  public int getDepth() {
    int nLeft = _getDepth(left);
    int nRight = _getDepth(right);
    return nLeft > nRight ? nLeft + 1 : nRight + 1;
  }

  static int _getDepth(Tree node) {
    if (node == null)
      return 0;
    int nLeft = _getDepth(node.left);
    int nRight = _getDepth(node.right);
    return nLeft > nRight ? nLeft + 1 : nRight + 1;
  }

  public static Tree flipTree(Tree node) {
    if (node == null)
      return null;
    Tree flippedLeft = flipTree(node.left);
    node.left = flipTree(node.right);
    node.right = flippedLeft;
    return node;
  }

  public static ArrayList<String> displayTree(Tree node) {
    final int markVal = 0;
    node.depth = node.getDepth();
    int maxNnode = (int) Math.pow(2, node.depth) - 1;
    int bottomN = (int) Math.pow(2, node.depth - 1);
    // 分层存储
    // 保存节点内容
    ArrayList<String> outStr = new ArrayList<>(maxNnode);
    // 当前处理的层
    ArrayList<Tree> nodeArrSrc = new ArrayList<>(bottomN);
    // 记录下层的节点
    ArrayList<Tree> nodeArrDst = new ArrayList<>(bottomN);

//    nodeArrSrc.ensureCapacity(bottomN);
//    nodeArrDst.ensureCapacity(bottomN);

    // 左右交换，否则最终显示的就是反的
    flipTree(node);
    nodeArrSrc.add(node);

    // 用 markVal 填补null节点的位置以形成完全二叉树，
    // 然后用 * 替代 markVal便于人眼观察
    for (int i = 0; i < node.depth; i++) {
      // 第 i 层
      for (Tree nod : nodeArrSrc) {
        // 记录当前层内容
        if (nod.val != markVal) {
          outStr.add(String.valueOf(nod.val));
          // 保存下一层结点
          if (nod.left == null)
            nodeArrDst.add(new Tree(markVal));
          else
            nodeArrDst.add(nod.left);

          if (nod.right == null)
            nodeArrDst.add(new Tree(markVal));
          else
            nodeArrDst.add(nod.right);
        }
        else {
          outStr.add("*");
          nodeArrDst.add(new Tree(markVal));
          nodeArrDst.add(new Tree(markVal));
        }
      }
      // 更新当前层为下层
      ArrayList<Tree> nodeArrTmp = nodeArrSrc;
      nodeArrSrc = nodeArrDst;
      nodeArrDst = nodeArrTmp;
//      nodeArrSrc.clear();
//      nodeArrSrc.addAll(nodeArrDst);
      nodeArrDst.clear();
    }

    int bound = 1;
    int cnt = 1;

    // 从最下层开始处理 行缩进和节点间隔
    int depth = node.depth;
    Collections.reverse(outStr);

    ArrayList<String> finalStr = new ArrayList<>(maxNnode);

    boolean levelStart = true;
    StringBuilder lineBeginPadSpace = new StringBuilder();
    StringBuilder intraPadSpace = new StringBuilder();
    lineBeginPadSpace.append(' ');
    intraPadSpace.append(' ');

    int nLevelNode = 0;
    int nodIdx = 0;
    for (String str : outStr) {
      if (levelStart) {
        // 0 + 1 + 2 + 4
        // pow(2, n) - 1
//        int nSpace = (int) Math.pow(2, node.depth - depth) - 1;
        finalStr.add(lineBeginPadSpace.toString());
//        System.out.print(lineBeginPadSpace);
        lineBeginPadSpace.append(lineBeginPadSpace);
        lineBeginPadSpace.append(' ');
        intraPadSpace.append(intraPadSpace);
        intraPadSpace.append(' ');

        levelStart = false;
        nLevelNode = (int) Math.pow(2, depth - 1);
        nodIdx = 1;
      }

      finalStr.add(str);
      finalStr.add(intraPadSpace.toString());
//      System.out.print(str);
//      System.out.print(intraPadSpace);

      if (nodIdx == nLevelNode) {
        // 层最后一个node 也输出了
        finalStr.add("\n");
//        System.out.println();
        --depth;
        levelStart = true;
        continue;
      }
      nodIdx++;
    } // end for (String str : outStr)

    for (String str : finalStr)
      System.out.print(str);

    return finalStr;
  }
}

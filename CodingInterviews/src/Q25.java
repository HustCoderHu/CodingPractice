import java.util.ArrayList;
import java.util.Collections;

import BaseAlgorithm.Tree;

public class Q25 {
  // 输入一颗二叉树和一个整数，打印出二叉树中结点值的和为输入整数的所有路径。
  // 路径定义为从树的根结点开始往下一直到叶结点所经过的结点形成一条路径。
  private static ArrayList<ArrayList<Integer>> pathList;

  public static void main(String[] args) {
  }
  public static ArrayList<ArrayList<Integer>> FindPath(Tree root, int target) {
    if (pathList == null)
      pathList = new ArrayList<>();
    else
      pathList.clear();

    if (root == null) {
      return pathList;
    }
    ArrayList<Integer> path = new ArrayList<>();
    findPath(root, target, path, 0);
    return pathList;
  }

  static void findPath(Tree root, int target,
                       ArrayList<Integer> path,
                       int curSum) {
    curSum += root.val;
    path.add(root.val);

    // 如果是叶结点， 并且路径上结点的和等于输入的值
    boolean isLeaf = root.left == null && root.right == null;
    if (curSum == target && isLeaf) {
      ArrayList<Integer> newOne = new ArrayList<>();
      Collections.copy(newOne, path);
      pathList.add(newOne);
    }
    // 遍历子结点
    if (root.left != null)
      findPath(root.left, target, path, curSum);
    if (root.right != null)
      findPath(root.right, target, path, curSum);

    // 删除当前结点
    path.remove(path.size() - 1);
  }
}

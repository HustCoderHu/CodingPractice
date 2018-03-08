import java.util.HashMap;
import java.util.Map;

public class Q6 {
  // 重构二叉树
  // 输入先序和中序
  public static void main(String[] args) {
//    int[] pre = new int[0];
//    System.out.println(pre.length);
//    System.out.println(pre);

    int[] pre = {1,2,4,7,3,5,6,8};
    int[] in = {4,7,2,1,5,3,8,6};

  }
  public static TreeNode reConstructBinaryTree(int [] pre,int [] in) {
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

  TreeNode(int x) {
    val = x;
  }
}

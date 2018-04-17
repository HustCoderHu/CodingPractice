import BaseAlgorithm.TreeNode;

public class Q62 {
  // 请实现两个函数，分别用来序列化和反序列化二叉树

  public static void main(String[] args) {
//    int a =Integer.valueOf("-3");
//    System.out.println("a = " + a);

    TreeNode root = new TreeNode(10);
    root.setLeft(new TreeNode(6));
    root.setRight(new TreeNode(14));

    TreeNode left = root.left;
    left.setLeft(new TreeNode(4));
//    left.setRight(new TreeNode(8));
    TreeNode right = root.right;
    right.setLeft(new TreeNode(12));

    String str = Serialize(root);
    System.out.println("str = " + str);
    root.show();
    root = Deserialize(str);
    root.show();
  }
  
  static StringBuilder strbder = new StringBuilder();
  static int num;
  static String gStr = null;
  static int idx = 0;

  static void _serialize(TreeNode root) {
    if (root == null) {
      strbder.append("$,");
      return;
    }
//    System.out.println(root.val + ',');
    strbder.append(root.val);
    strbder.append(',');
    _serialize(root.left);
    _serialize(root.right);
  }

  static boolean readStr() {
    num = 0;
    if (idx >= gStr.length() || gStr.charAt(idx) == '$') {
      idx += 2;
      return false;
    }

    int end = idx+1;
    while (end < gStr.length() && gStr.charAt(end) != ',') {
      ++end;
    }

//    System.out.println(gStr.substring(idx, end));
    num = Integer.valueOf(gStr.substring(idx, end));
    idx = end+1;

    return true;
  }

  static TreeNode _deserial() {
    TreeNode nod = null;
    if (readStr()) {
      nod = new TreeNode(num);
      nod.left = _deserial();
      nod.right = _deserial();
    }
    return nod;
  }

  static String Serialize(TreeNode root) {
    strbder.setLength(0);
    _serialize(root);
    return strbder.toString();
  }
  static TreeNode Deserialize(String str) {
    gStr = str;
    idx = 0;
    return _deserial();
  }
}

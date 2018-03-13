public class Q24 {
  // 输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。
  // 如果是则输出Yes,否则输出No。假设输入的数组的任意两个数字都互不相同。
  public static void main(String[] args) {

    int[] seq0 = null;
    int[] seq1 = new int[0];
    int[] seq2 = {5, 7, 6, 9, 11, 10, 8};
    int[] seq3 = {7, 4, 6, 5};

    System.out.println(VerifySquenceOfBST(seq0));
    System.out.println(VerifySquenceOfBST(seq1));
    System.out.println(VerifySquenceOfBST(seq2));
    System.out.println(VerifySquenceOfBST(seq3));
  }

  public static boolean VerifySquenceOfBST(int [] sequence) {
    if (sequence == null || sequence.length == 0)
      return false;
    return verify(sequence, 0, sequence.length - 1);
  }

  public static boolean verify(int[] seq, int left, int right) {
    if (left == right || left+1 == right)
      return true;

    int root = seq[right];
    // 左子树小于根
    int i = left;
    for(; i < right; ++i)
      if (seq[i] > root)
        break;

    // 右子树大于根
    int j = i;
    for (; j < right; ++j)
      if (seq[j] < root)
        return false;

    return verify(seq, left, i-1) && verify(seq, i, right - 1);
  }
}

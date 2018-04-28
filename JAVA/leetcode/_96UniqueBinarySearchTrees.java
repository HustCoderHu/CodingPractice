package leetcode;

public class _96UniqueBinarySearchTrees {
  public static void main(String[] args) {
    System.out.println(numTrees(4)); // 4 -> 14
  }
  public static int numTrees(int n) {
    int[] cnt = new int[n + 1];
    System.out.println(cnt[4]);

    cnt[0] = 1;
    cnt[1] = 1;
    for (int i = 2; i <= n; i++) {
      for (int j = 0; j <= i-1; j++)
        cnt[i] += (cnt[j] * cnt[i - 1 - j]);
    }
    return cnt[n];
  }
}

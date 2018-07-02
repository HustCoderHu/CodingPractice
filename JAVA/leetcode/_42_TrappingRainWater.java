package leetcode;

import java.util.Arrays;

public class _42_TrappingRainWater {
  // 效率低
  public static void main(String[] args) {
    int[] a = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    int res = trap(a);
    System.out.println(res);

  }
  static int trap(int[] height) {
    if (height.length <= 2)
      return 0;
    Pair[] pa = new Pair[height.length];
    for (int i = 0; i < height.length; i++)
      pa[i] = new Pair(i, height[i]);
    int[] newh = Arrays.copyOf(height, height.length);
//    System.out.println(Arrays.toString(newh));

    Arrays.sort(pa, (o1, o2)->o2.v-o1.v);
    int left = pa[0].idx;
    int right = pa[1].idx;

    if (right < left) {
      setv(newh, right, left-1, pa[1].v);
      int t = left;
      left = right;
      right = t;
    } else
      setv(newh, left + 1, right, pa[1].v);
    for (int i = 2; i < height.length; i++) {
      int idx = pa[i].idx;
      if (idx < left) {
        setv(newh, idx, left-1, pa[i].v);
        left = idx;
      } else if (right < idx) {
        setv(newh, right+1, idx, pa[i].v);
        right = idx;
      }
    }
//    System.out.println(Arrays.toString(newh));
    int sumv = 0;
    for (int i = 0; i < newh.length; i++) {
      sumv += newh[i] - height[i];
    }
    return sumv;
  }
  static void setv(int[] h, int from, int to, int v) {
    for (int i = from; i <= to; i++)
      h[i] = v;
  }
}

class Pair {
  int idx;
  int v;

  Pair(int i, int v) {
    idx = i;
    this.v = v;
  }
}
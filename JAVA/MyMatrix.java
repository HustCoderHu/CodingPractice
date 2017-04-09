package mypkg.practice.javacore;

/**
 * Created by Path on 2017/3/25.
 */
public class MyMatrix {
//    private int nr_row;

//    private int nr_col;
//    private int[][] matrix;


//    public MyMatrix(int[][] m, int row, int col) {
//        nr_row = row;
//        nr_col = col;
//        matrix = new int[row][col];
//        for (int i = 0; i < row; i++) {
//            System.arraycopy(m[i], 0, matrix[i], 0, col);
//        }
//    }

    public static void showIt(int[][] m, int row, int col) {
        int i, j;
        for (i = 0; i < row; i++) {
            for (j = 0; j < col; j++) {
                System.out.printf("%2d ", m[i][j]);
            }
            System.out.println();
        }
    }

    public static void roundPrint(int[][] m, int row, int col) {
        int left = 0;
        int right = col - 1;
        int top = 0;
        int bottom = row - 1;

        int total = col * row;

        int[] OutestLayer;
        int[] arrayMatrix = new int[total];

        int cnt = 0;
        int LayerLen;

        while (cnt < total) {
            if (right == left)
                LayerLen = bottom - top + 1;
            else if (bottom == top)
                LayerLen = right - left + 1;
            else
                LayerLen = (right - left + bottom - top) * 2;

//            System.out.printf("left = %d\n", left);
//            System.out.printf("top = %d\n", top);
//            System.out.printf("LayerLen = %d\n", LayerLen);

            OutestLayer = getOutestLayer(m, left, right, top, bottom, LayerLen);

            System.arraycopy(OutestLayer, 0, arrayMatrix, cnt, LayerLen);
            cnt += LayerLen;

            left++;
            right--;
            top++;
            bottom--;
        }
        for (int e : arrayMatrix) {
            System.out.printf("%d ", e);
        }
    }

    private static int[] getOutestLayer(int[][] m, int left, int right, int top, int bottom,
                                        int LayerLen) {
        int[] OutestLayer;
        int cur_row;
        int cur_col;

        int cnt;

        OutestLayer = new int[LayerLen];

        if (right < left || bottom < top)
            return OutestLayer;

        cnt = 0;
        OutestLayer[cnt++] = m[top][left];

        for (cur_col = left + 1; cur_col <= right; cur_col++)
            OutestLayer[cnt++] = m[top][cur_col];

        for (cur_row = top + 1; cur_row <= bottom; cur_row++)
            OutestLayer[cnt++] = m[cur_row][right];

        if (cnt >= LayerLen)
            return OutestLayer;

        for (cur_col = right - 1; cur_col >= left; cur_col--)
            OutestLayer[cnt++] = m[bottom][cur_col];

        for (cur_row = bottom - 1; cur_row > top; cur_row--)
            OutestLayer[cnt++] = m[cur_row][left];

        return OutestLayer;
    }

    public static void main(String[] args) {
        int row;
        int col;

        row = 5;
        col = 7;

        int[][] m = new int[row][col];
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                m[i][j] = i * col + j + 1;
            }
        }

        showIt(m, row, col);
        System.out.println();
        roundPrint(m, row, col);
    }
}

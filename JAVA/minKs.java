import java.awt.*;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.ListIterator;

/**
 * Created by Path on 2017/4/8.
 * find min k numbers among a array
 */
public class minKs {
    public static void main(String[] args) {
        int arrayLen = 100;
        int[] array = new int[arrayLen];

        int K = 10;
        int[] result = new int[K];

        int i;
        for (i = 0; i < arrayLen; i++)
            array[i] = i;

        getMinKs(K, array, result);

        System.out.println(Arrays.toString(result));
    }

    private static int getMinKs(int K, int[] array, int[] result) {
        if (K > array.length)
            return -1;

        LinkedList<Integer> minks = new LinkedList<Integer>();
        ListIterator iter;
        int i = 0;
        int val;

        // the fist K
        minks.add(array[i]);
        for (i = 1; i < K; i++) {
            // find inserting location
            val = array[i];
            iter = minks.listIterator();
            while (iter.hasNext()) {
                if ((Integer) iter.next() <= val)
                    break;
            }
            iter.previous();
            iter.add(val);
        }
        // remaining n - K
        int arrayLen = array.length;
        for (i = K; i < arrayLen; i++) {
            val = array[i];
            if (val >= (Integer) minks.getFirst())
                continue;

            // find inserting location
            iter = minks.listIterator();
            while (iter.hasNext()) {
                if ((Integer) iter.next() <= val)
                    break;
            }
            iter.previous();
            iter.add(val);
            minks.removeFirst();
        }

        iter = minks.listIterator();
        for (i = 0; i < K; i++)
            result[i] = (Integer)iter.next();

        return 0;
    }
}

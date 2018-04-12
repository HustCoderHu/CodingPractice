import java.util.Arrays;
import java.util.Comparator;

public class Q33 {
//  final int INT_MAXLEN = 10;
//  char[] str1 = new char[INT_MAXLEN * 2 + 1];
//  char[] str2 = new char[INT_MAXLEN * 2 + 1];

  public static void main(String[] args) {
    int[] numbers = {3, 32, 321};
    System.out.println(PrintMinNumber(numbers));
  }

  public static String PrintMinNumber(int [] numbers) {
    final int nNum = numbers.length;
    String[] strNums = new String[nNum];

    for (int i = 0; i < nNum; i++) {
      strNums[i] = String.valueOf(numbers[i]);
    }

    Comparator<String> comp = new MyComp();

    Arrays.sort(strNums, comp);

    StringBuilder str = new StringBuilder();
    for (String s : strNums)
      str.append(s);

    return str.toString();
  }
}

class MyComp implements Comparator<String> {
  static final int INT_MAXLEN = 10;
  static StringBuilder stra = new StringBuilder(INT_MAXLEN * 2 + 1);
  static StringBuilder strb = new StringBuilder(INT_MAXLEN * 2 + 1);

  @Override
  public int compare(java.lang.String o1, java.lang.String o2) {
    stra.delete(0, stra.length());
    strb.delete(0, strb.length());

    stra.append(o1);
    stra.append(o2);
    strb.append(o2);
    strb.append(o1);

//    System.out.println(o1 + " " + o2);
//    System.out.println(stra.toString() + " " + strb.toString() + ": " +
//            stra.toString().compareTo(strb.toString()));
    return stra.toString().compareTo(strb.toString());
  }
}
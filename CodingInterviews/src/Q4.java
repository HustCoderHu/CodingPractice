import java.util.ArrayList;
import java.util.List;

public class Q4 {
  // 替换空格
  public static void main(String[] args) {
    StringBuffer str = new StringBuffer("a a  aaaa a ");
//    replaceSpace(str);
    System.out.println(replaceSpace(str));
  }
  public static String replaceSpace(StringBuffer str) {
    if (str == null)
      return null;

    int oldLen = str.length();
    if (oldLen == 0)
      return "";

    StringBuilder strb = new StringBuilder(oldLen * 3);
    for (int i = 0; i < oldLen; ++i) {
      if (str.charAt(i) == ' ')
        strb.append("%20");
      else
        strb.append(str.charAt(i));
    }
    return strb.toString();
  }
}

// http://blog.csdn.net/google19890102/article/details/40264699
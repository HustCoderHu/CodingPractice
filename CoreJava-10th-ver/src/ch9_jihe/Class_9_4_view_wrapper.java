package ch9_jihe;

import com.sun.jdi.ShortValue;

import java.util.*;

public class Class_9_4_view_wrapper {
  public static void main(String[] args) {

  }

  public static void views_and_wrapper() {
    String[] strDeck = new String[3];
    List<String> strList = Arrays.asList(strDeck);
    List<String> names = Arrays.asList("Amy", "Bob", "Carl"); // 参数num可变
    List<String> settings = Collections.nCopies(10, "DEFAULT");

//    List group2 = staff.subList(10, 20); // 10 ~ 19 个元素 类似 substring
//    group2.clear();
    // 多线程访问
    Map<String, Integer> map = Collections.synchronizedMap(new HashMap<>());
  }
}

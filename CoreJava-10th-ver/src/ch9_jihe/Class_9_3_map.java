package ch9_jihe;

import java.util.HashMap;
import java.util.Map;

public class Class_9_3_map {
  public static void main(String[] args) {
    Class_9_3_map cont = new Class_9_3_map();
    cont.basic();
  }
  public void basic() {
    Map<String, Integer> staff = new HashMap<>();
//    Map<int, String> staff = new HashMap<>();
    String name = "Harry";
    staff.put(name, 0);
    staff.put("Bob", 1);
    staff.put("Carl", 2);
    staff.put("David", 3);
    name = "Carl";
    int e = staff.get(name);
    System.out.println(e);
    name = "Alice";
//    e = staff.get(name, 10);
    e = staff.getOrDefault(name, 10);
    System.out.println("e = " + e); // 10

    staff.forEach((k, v) -> System.out.println("key= " + k + ", val=" + v));

  }
}

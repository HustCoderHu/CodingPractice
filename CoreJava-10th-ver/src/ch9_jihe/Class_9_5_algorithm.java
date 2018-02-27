package ch9_jihe;

//import ch4_obj_class.Employee;

import java.util.*;

public class Class_9_5_algorithm {
  public static void main(String[] args) {

  }
  public static void sort_and() {
    List<String> staff = new LinkedList<>();
    Collections.sort(staff); // 假定 元素实现了 Comparable 接口
//    staff.sort(Comparator.comparingDouble(Employee::getSalary));
//    staff.sort(Comparator.comparingDouble(Employee::getSalary).reversed());
    staff.sort(Comparator.reverseOrder()); // 降序

    // 列表支持 set ，可修改
    // 支持 add remove， 大小可变

//    ArrayList<String> cards = ;
//    Collections.shuffle(cards);
  }
  public static void simpleAlgorithm() {
    List<String> staff = new LinkedList<>();
    List<String> staff2 = new LinkedList<>();
    Collections.min(staff); // Collection
    Collections.max(staff);
    Collections.copy(staff, staff2); // List  to, from
    Collections.fill(staff, "WTF"); // List

    Set<String> set = new HashSet<>();
    Set<String> set2 = new HashSet<>();
    Collections.addAll(set, "a", "b", "c");
//    Collections.replaceAll(staff, oldVal, newVal);
  }
}

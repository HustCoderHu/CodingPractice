package ch9_jihe;

//import ch4_obj_class.Employee;

import com.sun.jdi.ShortValue;

import java.util.*;

public class Class_9_5_algorithm {
  public static void main(String[] args) {
//    oldApi2jihe();
    EratosthenesPrimes();
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

  public static void batchop() {
    Set<String> coll1 = new HashSet<>();
    Set<String> coll2 = new HashSet<>();
    coll1.removeAll(coll2); // 从1中 删除 2包含的所有elements
    coll1.retainAll(coll2); // 反之

    Set<String> result = new HashSet<>(coll1); // 复制构造
    result.retainAll(coll2); // 求交集

    // 视图
    Map<String, Integer> staffMap = new HashMap<>();
    Set<String> terminatedIDs = new HashSet<>();
    staffMap.keySet().removeAll(terminatedIDs);
    // 键集是视图，所以key和相关联的员工名会自动从map中删除
  }
  public static void oldApi2jihe() {
//    String[] val = new String[3];
    String[] val = {"aa", "bb", "cc"};
    HashSet<String> staff = new HashSet<>(Arrays.asList(val));
    System.out.println(staff);
    System.out.println(Arrays.asList(val).getClass()); // java.util.Arrays$ArrayList

    // 集合转数组
    String[] val2 = new String[3];
    staff.toArray(val2);
    System.out.println(Arrays.asList(val2));
  }
  public static void remainJihe() {
    BitSet bucketOfBits = new BitSet(64); // nbits
    bucketOfBits.get(3);
    bucketOfBits.set(4); // set to true
    bucketOfBits.clear(4); // set to false
    bucketOfBits.length();

    BitSet set2 = new BitSet(64);
    set2.and(bucketOfBits);
    set2.or(bucketOfBits);
    set2.xor(bucketOfBits);
    set2.andNot(bucketOfBits);
  }
  public static void EratosthenesPrimes() {
    int n = 2000000;
    long start = System.currentTimeMillis();
    BitSet b = new BitSet(n + 1);
    int cnt = 0;
    int i ;
    for (i=2; i<=n; ++i)
      b.set(i);
    i = 2;
    while (i * i <= n) {
      if (b.get(i)) {
        ++cnt;
        int k = 2*i;
        while (k <= n) {
          b.clear(k);
          k += i;
        }
      }
      ++i;
    }
    while (i <= n) {
      if (b.get(i))
        ++cnt;
      ++i;
    }
    long end = System.currentTimeMillis();
    System.out.println(cnt + " primes");
    System.out.println((end - start) + " milliseconds");
  }
}

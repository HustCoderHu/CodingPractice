package ch9_jihe;

import java.util.*;

// map method
/*
V get(key)
default V getOrDefault(key, defaultVal)
V put(key, val)
void putAll( Map<? extends K, ? extends V> entries)
  map 合并 好象是
boolean containsKey(key)
boolean containsValue(val)
default void forEach(BiConsumer<? super K, ? super V> action)
 */


public class Class_9_3_map {
  public static void main(String[] args) {
    Class_9_3_map cont = new Class_9_3_map();
    cont.basic();
  }
  public void basic() {
    Map<String, Integer> staff = new HashMap<>();
//    Map<int, String> staff = new HashMap<>();
    // 与set一样，Hash稍微快一点，如果不需要排序，最好用 HashMap
    // 否则就是TreeMap
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

    System.out.println(staff);

    Map<String, Integer> counts = new TreeMap<>();

    String word = "and";
    counts.merge(word, 1, Integer::sum);
  }
  public static void mapview() {
    /*
    Set<K> keySet()
    Collection<V> values()
    Set<Map.Entry<K, V>> entrySet()
     */

    Map<String, Integer> counts = new TreeMap<>();
    Set<String> keys = counts.keySet();
    for (String k : keys)
      System.out.println(k);

    for (Map.Entry<String, Integer> entry : counts.entrySet()) {
      String k = entry.getKey();
      Integer v = entry.getValue();
    }
    // 更高效的
    counts.forEach((k, v) -> {
      // do something
    });
  }
  public static void LinkedHashSet_Map() {
    Map<String, Integer> staff = new LinkedHashMap<>();
    // put
    // keySet().iterator() 枚举顺序和 put 一致
    // values().iterator() 也是
  }
  enum Weekday {MON, TUE, WED, THU, FRI, SAT, SUN};
  public static void test_enumSet_Map() {
    EnumSet<Weekday> always = EnumSet.allOf(Weekday.class);
    EnumSet<Weekday> never = EnumSet.noneOf(Weekday.class);
    EnumSet<Weekday> workday = EnumSet.range(Weekday.MON, Weekday.FRI);
    EnumSet<Weekday> mwf = EnumSet.of(Weekday.MON, Weekday.WED, Weekday.FRI);
    // Map, key 为 enum类型
  }
}

package ch6_if_lambda_interclass;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Date;
import java.util.function.BiFunction;
import java.util.function.IntConsumer;
import java.util.stream.Collectors;
import java.util.stream.Stream;
import javax.sound.midi.Soundbank;
import javax.swing.Timer;
import javax.xml.crypto.Data;

public class Class_6_3_lambda {
  public static void main(String[] args) {
    // 排序为例
    // first.length() - second.length()
    Comparator<String> comp
            = (first, second) -> first.length() - second.length();
    Timer t = new Timer(2000, event ->
            System.out.println("The time is " + new Date()));
    t.start();

    // 函数式接口
    String[] words = {"Bob", "Alice", "Carl", "Amy"};
    Arrays.sort(words, (_1st, _2nd) -> _1st.length() - _2nd.length());
    System.out.println(Arrays.toString(words));

    BiFunction<String, String, Integer> comp2
            = (st1, nd2) -> st1.length() - nd2.length();
    // java.util.function 有个接口 Predicate
//    public interface Predicate<T> {
//      boolean test(T t);
//      // additional default and static methods
//    }
//    ArrayList l;
//    l.removeIf(e -> e == null); 参数是 Predicate
    Arrays.sort(words, String::compareToIgnoreCase);
    System.out.println(Arrays.toString(words));

    ArrayList<String> names = new ArrayList<>();
    for (String s : words)
      names.add(s);
//    Stream<Person> strm = names.stream().map(Person::new);
//    List<Person> people = strm.collect(Collectors.toList());
//    Object[] people = strm.toArray();
//    Person[] people = strm.toArray(Person[]::new);
    repeat(3, ()-> System.out.println("hello, world!"));
    repeat2(3, i -> System.out.println("countdown: " + (2 - i)));
    String aaa = "abc";
    aaa += 3;
    System.out.println("aaa = " + aaa);


  }
  public static void repeat(int n , Runnable action) {
    for (int i=0; i<n; ++i)
      action.run();
  }
  public static void repeat2(int n , IntConsumer action) {
    for (int i=0; i<n; ++i)
      action.accept(i);
  }

  private class Person {
    public String name;
    String getName() {
      return name;
    }
  }
}

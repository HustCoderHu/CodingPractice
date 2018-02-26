package ch6_if_lambda_interclass;

import java.util.Comparator;
import java.util.Date;
import javax.sound.midi.Soundbank;
import javax.swing.Timer;
import javax.xml.crypto.Data;

public class Class_6_3_lambda {
  public static void main(String[] args) {
    // 排序为例
    // first.length() - second.length()
    Comparator<String> comp
            = (first, second) -> first.length() - second.length();
    Timer t = new Timer(1000, event ->
            System.out.println("The time is " + new Date()));
    t.start();
  }
}

package ch4_obj_class;

import java.time.DayOfWeek;
import java.time.LocalDate;
import java.util.Date;

public class Cls_4_2 {
  public static void main(String[] args) {
    Date today = new Date();
    System.out.println(today.toString());

    LocalDate newYearEve = LocalDate.of(1999, 12, 31);
    int year = newYearEve.getYear();
    int month = newYearEve.getMonthValue();
    int day = newYearEve.getDayOfMonth();

    LocalDate a1000daysLater = newYearEve.plusDays(1000);
    // 原对象不变, 返回的变
//    plusWeeks(long);
//    plusMonths(long);
//    plusYears(long);
    showCalendar();
  }

  public static void showCalendar() {
    LocalDate date = LocalDate.now();
    int month = date.getMonthValue();
    int today = date.getDayOfMonth();

    date = date.minusDays(today - 1); // set to start of month
    DayOfWeek weekday = date.getDayOfWeek();
    int val = weekday.getValue(); // 1 = Mon, ... 7 = Sun

    System.out.println("Mon Tue Web Thu Fri Sat Sun");
    for (int i=1; i<val; ++i)
      System.out.print("    ");
    while (date.getMonthValue() == month) {
      int cur = date.getDayOfMonth();
      System.out.printf("%3d", cur);
      if (date.getDayOfMonth() == today)
        System.out.print("*");
      else
        System.out.print(" ");
      date = date.plusDays(1);
      if (date.getDayOfWeek().getValue() == 1)
        System.out.println();
    }
    if (date.getDayOfWeek().getValue() != 1)
      System.out.println();
  }
}

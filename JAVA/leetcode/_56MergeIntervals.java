package leetcode;

import java.util.*;

public class _56MergeIntervals {
  public static void main(String[] args) {
    List<Interval> intv = new ArrayList<>();
    intv.add(new Interval(1, 9));
    intv.add(new Interval(2, 5));
    intv.add(new Interval(19, 20));
    intv.add(new Interval(10, 11));
    intv.add(new Interval(12, 20));
    intv.add(new Interval(0, 3));
    intv.add(new Interval(0, 1));
    intv.add(new Interval(0, 2));
    System.out.println(merge(intv).toString());
  }
  public static List<Interval> merge(List<Interval> intervals) {
    Collections.sort(intervals, (o1, o2) -> o1.start-o2.start);
    LinkedList<Interval> merged = new LinkedList<Interval>();
    for (Interval interval : intervals) {
      // if the list of merged intervals is empty or if the current
      // interval does not overlap with the previous, simply append it.
      if (merged.isEmpty() || merged.getLast().end < interval.start) {
        merged.add(interval);
      } else {
        // otherwise, there is overlap, so we merge the current and previous
        // intervals.
        merged.getLast().end = Math.max(merged.getLast().end, interval.end);
      }
    }
    return merged;
  }
}

/**
 * Definition for an interval.
 */
class Interval {
    public int start;
    public int end;
    Interval() { start = 0; end = 0; }
    Interval(int s, int e) { start = s; end = e; }

  @Override
  public String toString() {
    return "["+start+","+end+"]";
  }
}



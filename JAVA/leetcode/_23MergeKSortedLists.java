package leetcode;

import java.util.Arrays;
import java.util.List;
import java.util.PriorityQueue;

public class _23MergeKSortedLists {

  public static void main(String[] args) {
    int[] l1 = {1,4,5};
    int[] l2 = {1,3,4};
    int[] l3 = {2,6};
    ListNode merged;
//    merged = mergeTwoLists(new ListNode(l1), new ListNode(l2));
//    merged.show();

    ListNode h1 = new ListNode(l1);
    ListNode h2 = new ListNode(l2);
    ListNode h3 = new ListNode(l3);

    ListNode[] hh = {h1, h2, h3};
    merged = mergek(hh);
    merged.show();
  }

  public static ListNode mergeKLists(ListNode[] lists) {
    if (lists == null || lists.length==0)
      return null;
    int heapSize = lists.length;
    PriorityQueue<_23item> h = new PriorityQueue<>(heapSize, (o1, o2) -> {
      return o1.node.val-o2.node.val; });

    _23item[] nodearray = new _23item[heapSize];
    for (int i = 0; i < heapSize; i++) {
      ListNode node = lists[i];
      nodearray[i] = new _23item(node, i);
      h.add(nodearray[i]);
      lists[i] = node.next;
    }

    _23item tmp;
    ListNode head, cur;
    // 取最小值
    tmp = h.poll();
    cur = head = tmp.node;
    int nextIdx = tmp.idx;
    lists[nextIdx] = lists[nextIdx].next;

//    while (true) {
//      tmp.node =
//    }
    return lists[0];
  }
  static ListNode mergek(ListNode[] lists) {
    if (lists == null || lists.length==0)
      return null;

    int end = lists.length-1;
    while (end != 0) {
//      System.out.println("end = " + end);
      int mid = (end-1) >>> 1;
      for (int i = 0; i <= mid; i++)
        lists[i] = mergeTwoLists(lists[i], lists[end - i]);
      end >>>= 1;
    }
    return lists[0];
  }

  static ListNode mergeTwoLists(ListNode l1, ListNode l2) {
    ListNode h = null;

    if (l1 != null && l2 != null) {
      if (l1.val <= l2.val) {
        h = l1;
        l1 = l1.next;
      } else {
        h = l2;
        l2 = l2.next;
      }
    } else if (l1 != null) {
      h = l1;
      l1 = l1.next;
    } else if (l2 != null) {
      h = l2;
      l2 = l2.next;
    }

    ListNode nxt = h;
    while (l1 != null && l2 != null) {
      if (l1.val <= l2.val) {
        nxt.next = l1;
        l1 = l1.next;
      } else {
        nxt.next = l2;
        l2 = l2.next;
      }
      nxt = nxt.next;
    }
    while (l1 != null) {
      nxt.next = l1;
      l1 = l1.next;
      nxt = nxt.next;
    }
    while (l2 != null) {
      nxt.next = l2;
      l2 = l2.next;
      nxt = nxt.next;
    }
    return h;
  }
}

class _23item {
  public ListNode node;
  public int idx;
  public _23item(ListNode n, int i) {
    node = n;
    idx = i;
  }
}

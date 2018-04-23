package leetcode;

public class _21MergeTwoSortedLists {
  public static void main(String[] args) {

  }

  public static ListNode mergeTwoLists(ListNode l1, ListNode l2) {
    ListNode h = null;

    if (l1 != null && l2 != null) {
      if (l1.val <= l2.val) {
        h = new ListNode(l1.val);
        l1 = l1.next;
      } else {
        h = new ListNode(l2.val);
        l2 = l2.next;
      }
    } else if (l1 != null) {
      h = new ListNode(l1.val);
      l1 = l1.next;
    } else if (l2 != null) {
      h = new ListNode(l2.val);
      l2 = l2.next;
    }

    ListNode nxt = h;
    while (l1 != null && l2 != null) {
      if (l1.val <= l2.val) {
        nxt.next = new ListNode(l1.val);
        nxt = nxt.next;
        l1 = l1.next;
      } else {
        nxt.next = new ListNode(l2.val);
        nxt = nxt.next;
        l2 = l2.next;
      }
    }
    while (l1 != null) {
      nxt.next = new ListNode(l1.val);
      nxt = nxt.next;
      l1 = l1.next;
    }
    while (l2 != null) {
      nxt.next = new ListNode(l2.val);
      nxt = nxt.next;
      l2 = l2.next;
    }
    return h;
  }
}

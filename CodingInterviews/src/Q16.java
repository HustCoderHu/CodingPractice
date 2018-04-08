import BaseAlgorithm.ListNode;
public class Q16 {
  // 反转链表
  public static void main(String[] args) {
    ListNode list1 = new ListNode(1);
    ListNode next = list1;
    next.append(new ListNode(2));
    next = next.next;
    next.append(new ListNode(3));
    next = next.next;
    next.append(new ListNode(4));
    next = next.next;
    next.append(new ListNode(5));

    list1.show();
    System.out.println();
    reverseList(list1).show();
  }

  static ListNode reverseList(ListNode head) {
    if (head == null)
      return null;

    ListNode newhead = null;
    ListNode next = null;
    while (head != null) {
      next = head.next;
      head.next = newhead;
      newhead = head;
      head = next;
    }

    return newhead;
  }
}

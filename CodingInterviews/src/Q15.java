import BaseAlgorithm.ListNode;

public class Q15 {
  // 输入一个链表，输出该链表中倒数第k个结点。

  static ListNode FindKthToTail(ListNode head,int k) {
    if (head == null || k == 0)
      return null;

    ListNode stepK = head;
    for (int i = 0; i < k-1; i++) {
      if (stepK.next == null)
        return null;
      stepK = stepK.next;
    }

    ListNode reverseK = head;
    while (stepK.next != null) {
      stepK = stepK.next;
      reverseK = reverseK.next;
    }
    return reverseK;
  }
}
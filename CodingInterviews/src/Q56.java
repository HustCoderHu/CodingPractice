import BaseAlgorithm.ListNode;

public class Q56 {
  // 一个链表中包含环，请找出该链表的环的入口结点。
  public static ListNode EntryNodeOfLoop(ListNode pHead)
  {
    if (pHead == null)
      return null;

    ListNode meetNode = meetingNod(pHead);
    if (meetNode == null)
      return null;

    ListNode tmp = meetNode;
    int circleLen = 0;
    // 计算环长
    while (tmp != meetNode) {
      tmp = tmp.next;
      ++circleLen;
    }
    // 一前一后
    ListNode nod1 = pHead;
    for (int i = 0; i < circleLen; i++) {
      nod1 = nod1.next;
    }
    ListNode nod2 = pHead;
    while (nod1 != nod2) {
      nod1 = nod1.next;
      nod2 = nod2.next;
    }
    return nod1;
  }

  // 快慢指针进环
  static ListNode meetingNod(ListNode h) {
    if (h == null)
      return null;

    ListNode slow = h.next;
    if (slow == null)
      return null;
    ListNode fast = slow.next;

    while (slow != null && fast != null) {
      if (slow == fast)
        return fast;
      slow = slow.next;
      fast = fast.next;
      if (fast!=null)
        fast = fast.next;
    }
    return null;
  }
}

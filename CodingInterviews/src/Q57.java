import BaseAlgorithm.HeapSort;
import BaseAlgorithm.ListNode;

import java.awt.desktop.AppHiddenEvent;

public class Q57 {
  // 在一个排序的链表中，存在重复的结点，请删除该链表中重复的结点，
  // 重复的结点不保留，返回链表头指针。
  // 例如，链表1->2->3->3->4->4->5 处理后为 1->2->5
  public static void main(String[] args) {
    ListNode anode = new ListNode(1);

    ListNode tmp;
    tmp = anode;
    tmp.append(new ListNode(1));
    tmp = tmp.next;
//    tmp.append(new ListNode(2));
//    tmp = tmp.next;
    tmp.append(new ListNode(2));
    tmp = tmp.next;
//    tmp.append(new ListNode(3));
//    tmp = tmp.next;
//    tmp.append(new ListNode(3));
//    tmp = tmp.next;
//    tmp.append(new ListNode(4));
//    tmp = tmp.next;
//    tmp.append(new ListNode(4));
//    tmp = tmp.next;
    tmp.append(new ListNode(5));
    tmp = tmp.next;
    tmp.append(new ListNode(6));

    anode.show();
    System.out.println();
    deleteDuplication(anode).show();
  }
  public static ListNode deleteDuplication(ListNode pHead)
  {
    ListNode prev=null, cur;

    if (pHead == null)
      return null;

    // 头结点
    cur = pHead;
    while (cur != null) {
      if (cur.val!=pHead.val)
        break;
      else if (cur != pHead) {// 不是同一结点
        pHead = cur.next;
        cur = pHead;
      } else { // 同一结点
        cur = cur.next;
      }
    }
    cur = prev = pHead;

//    cur = prev.next;
    while (cur != null) {
      ListNode next = cur.next;
      if (next == null) {
        prev.next = cur;
        break;
      } else if (cur.val == next.val) {
        cur = next.next;
      } else {
        prev.next = cur;
        prev = cur;
        cur = next;
      }
    }

//    while (cur != null) {
//      ListNode next = cur.next;
//      if (next == null) {
//        prev.next = cur;
//        break;
//      } else if (cur.val == next.val)
//        cur = next.next;
//      else {
//        prev.next = cur;
//      }
//
//        if (cur.val == prev.val)
//          cur = cur.next;
//        else {
//          prev.next = cur;
//          prev = cur;
//          cur = cur.next;
//        }
//    }
    return pHead;
  }
}

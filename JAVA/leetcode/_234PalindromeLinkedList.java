package leetcode;

public class _234PalindromeLinkedList {
  public boolean isPalindrome(ListNode head) {
    ListNode fast = head, slow = head;
    while (fast != null && fast.next != null) {
      fast = fast.next.next;
      slow = slow.next;
    }
    // 奇数个结点
    if (fast != null)
      slow = slow.next; // 跳过中间结点

//    slow = slow.reverse();
    slow = reverse(slow);
    fast = head;
    while (slow != null) {
      if (fast.val!=slow.val)
        return false;
      fast = fast.next;
      slow = slow.next;
    }
    return true;
  }

  static ListNode reverse(ListNode h) {
    ListNode prev = null;
    while (h != null) {
      ListNode nxt = h.next;
      h.next = prev;
      prev = h;
      h = nxt;
    }
    return prev;
  }
}

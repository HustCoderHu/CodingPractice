package leetcode;

public class Add2num {
  public static void main(String[] args) {
    ListNode tmp;
    ListNode nod = new ListNode(2);
    tmp = nod;
    tmp.next = new ListNode(4);
    tmp = tmp.next;
    tmp.next = new ListNode(3);
//    nod.show();

    ListNode nod1 = new ListNode(5);
    tmp = nod1;
    tmp.next = new ListNode(6);
    tmp = tmp.next;
    tmp.next = new ListNode(4);
//    nod1.show();

//    addTwoNumbers(nod, nod1).show();
    addTwoNumbers(new ListNode(5), new ListNode(5)).show();
  }

  public static ListNode addTwoNumbers(ListNode l1, ListNode l2) {
    int sum = l1.val + l2.val;
    int carry = sum/10;
    sum %= 10;

    ListNode h = new ListNode(sum);
    ListNode tmp = h;

    l1 = l1.next;
    l2 = l2.next;
    while (l1 != null && l2 != null) {
      sum = carry + l1.val + l2.val;
      carry = sum/10;
      sum = sum-carry*10;

      tmp.next = new ListNode(sum);
      tmp = tmp.next;
      l1 = l1.next;
      l2 = l2.next;
    }
    while (l1 != null) {
      sum = carry + l1.val;
      carry = sum/10;
      sum = sum-carry*10;
      tmp.next = new ListNode(sum);
      tmp = tmp.next;
      l1 = l1.next;
    }
    while (l2 != null) {
      sum = carry + l2.val;
      carry = sum/10;
      sum = sum-carry*10;
      tmp.next = new ListNode(sum);
      tmp = tmp.next;
      l2 = l2.next;
    }
    if (carry != 0)
      tmp.next = new ListNode(carry);
    return h;
  }
}

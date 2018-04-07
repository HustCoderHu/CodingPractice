public class Q17 {
  // 输入两个单调递增的链表，输出两个链表合成后的链表，
  // 当然我们需要合成后的链表满足单调不减规则
  public static void main(String[] args) {
    ListNode list1 = new ListNode(1);
    ListNode next = list1;
    next.append(new ListNode(3));
    next = next.next;
    next.append(new ListNode(5));

    ListNode list2 = new ListNode(2);
    next = list2;
    next.append(new ListNode(4));
    next = next.next;
    next.append(new ListNode(6));

    list1.show();
    System.out.println();
    list2.show();
    System.out.println();

    next = nonRecurs(list1, list2);
    next.show();
  }

  public ListNode Merge(ListNode list1,ListNode list2) {
    if (list1 == null)
      return list2;
    else if (list2 == null)
      return list1;

    ListNode merged = null;
    if (list1.val < list2.val) {
      merged = list1;
      list1 = list1.next;
    } else {
      merged = list2;
      list2 = list2.next;
    }
//    merged.next = Merge(list1, list2);
    merged.next = nonRecurs(list1, list2);
    return merged;

    // 运行时间：15ms
    //占用内存：9684k
  }
  static ListNode nonRecurs(ListNode list1,ListNode list2) {
    if (list1 == null)
      return list2;
    else if (list2 == null)
      return list1;

    ListNode merged = null;
    if (list1.val < list2.val) {
      merged = list1;
      list1 = list1.next;
    } else {
      merged = list2;
      list2 = list2.next;
    }

    ListNode tmp = merged;
    while (list1 != null && list2 != null) {
      if (list1.val < list2.val) {
        tmp.next = list1;
        list1 = list1.next;
      } else {
        tmp.next = list2;
        list2 = list2.next;
      }
      tmp = tmp.next;
    }
    if (list1 != null) {
      tmp.next = list1;
    }
    if (list2 != null) {
      tmp.next = list2;
    }
    return merged;
  }
}


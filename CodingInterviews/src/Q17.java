public class Q17 {
  public static void main(String[] args) {
    ListNode list1 = new ListNode(1);
    list1.append(new ListNode(3));
    list1.append(new ListNode(5));

    ListNode list2 = new ListNode(2);
    list2.append(new ListNode(4));
    list2.append(new ListNode(6));
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
    merged.next = Merge(list1, list2);
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

    while (list1 != null && list2 != null) {
      if (list1.val < list2.val) {
        merged.next = list1;
        list1 = list1.next;
      } else {
        merged.next = list2;
        list2 = list2.next;
      }
    }
    if (list1 != null) {
      merged.next = list1;
    }
    if (list2 != null) {
      merged.next = list2;
    }
    return merged;
  }
}


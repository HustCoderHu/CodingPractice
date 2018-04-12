import BaseAlgorithm.ListNode;

public class Q37 {
  // 输入两个链表，找出它们的第一个公共结点。
  public static void main(String[] args) {

  }
  public ListNode FindFirstCommonNode(ListNode pHead1, ListNode pHead2) {
    int len1 = getLen(pHead1);
    int len2 = getLen(pHead2);

    ListNode listLong = pHead1;
    ListNode listShort = pHead2;
    int lenDif = len1 - len2;
    if (len1 < len2) {
      listShort = pHead1;
      listLong = pHead2;
      lenDif = len2 - len1;
    }
    // 长链表走几步，再同时在两链表上遍历
    for (int i = 0; i < lenDif; i++) {
      listLong = listLong.next;
    }

    while (listLong != null && listShort != null
            && listLong != listShort) {
      listLong = listLong.next;
      listShort = listShort.next;
    }
    return listLong;
  }

  static int getLen(ListNode h) {
    int len = 0;
    ListNode nod = h;
    while (nod != null) {
      ++len;
      nod = nod.next;
    }
    return len;
  }
}

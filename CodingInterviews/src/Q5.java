import java.util.ArrayList;
import java.util.Collections;

public class Q5 {
  // 从尾到头打印链表
  public static void main(String[] args) {
    ArrayList<Integer> arr = new ArrayList<>();
    arr.add(67);
    arr.add(0);
    arr.add(24);
    arr.add(58);
    System.out.println(arr.size());

    //    ListNode anode = null;
    ListNode tmp = null;


    ListNode anode = new ListNode(67);

    tmp = anode;
    tmp.append(new ListNode(0));
    tmp = tmp.next;
    tmp.append(new ListNode(24));
    tmp = tmp.next;
    tmp.append(new ListNode(58));
    tmp = tmp.next;
    System.out.println(printListFromTailToHead(anode).toString());
  }

  public static ArrayList<Integer> printListFromTailToHead(ListNode listNode) {
    if (listNode == null)
      return new ArrayList<Integer>();
//      return null;

    ArrayList<Integer> arr = new ArrayList<>();
    while (listNode != null) {
      arr.add(listNode.val); // 从头到尾
      listNode = listNode.next;
    }
    arr.trimToSize();
    Collections.reverse(arr);

//    int arrSize = arr.size();
//    int bound = arr.size()/2;
//    for (int i = 0; i < bound; ++i) { // 交换
//      Integer tmp = arr.get(i);
//      arr.set(i, arr.get(arrSize-i));
//      arr.set(arrSize-i, tmp);
//    }
    return arr;
  }
}

class ListNode {
  int val;
  ListNode next = null;

  ListNode(int val) {
    this.val = val;
  }

  public void append(ListNode node) {
    next = node;
  }
  public void show() {
    ListNode tmp = this;
    while (tmp != null) {
      System.out.printf("%d ", tmp.val);
      tmp = tmp.next;
    }
  }
}
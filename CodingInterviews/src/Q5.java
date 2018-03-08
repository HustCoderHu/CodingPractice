import javax.print.attribute.standard.PrinterLocation;
import java.util.ArrayList;

public class Q5 {
  // 从尾到头打印链表
  public static void main(String[] args) {
    ArrayList<Integer> arr = new ArrayList<>();
    arr.add(3);
    arr.add(3);
    arr.add(3);
    arr.add(3);
    System.out.println(arr.size());

//    ListNode anode = new ListNode(3);
    ListNode anode = null;
    System.out.println(printListFromTailToHead(anode));
  }

  public static ArrayList<Integer> printListFromTailToHead(ListNode listNode) {
    if (listNode == null)
      return null;

    ArrayList<Integer> arr = new ArrayList<>();
    while (listNode != null) {
      arr.add(listNode.val); // 从头到尾
      listNode = listNode.next;
    }
    arr.trimToSize();
    int arrSize = arr.size();
    int bound = arr.size()/2;
    for (int i = 0; i < bound; ++i) { // 交换
      Integer tmp = arr.get(i);
      arr.set(i, arr.get(arrSize-i));
      arr.set(arrSize-i, tmp);
    }
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
}
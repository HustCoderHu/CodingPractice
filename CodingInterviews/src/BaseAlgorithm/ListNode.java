package BaseAlgorithm;

public class ListNode {
  public int val;
  public ListNode next = null;

  public ListNode(int val) {
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
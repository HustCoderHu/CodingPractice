import BaseAlgorithm.RandomListNode;
import javafx.scene.media.VideoTrack;

public class Q26 {
  // 输入一个复杂链表（每个节点中有节点值，以及两个指针，一个指向下一个节点，
  // 另一个特殊指针指向任意一个节点），返回结果为复制后复杂链表的head。
  // （注意，输出结果中请不要返回参数中的节点引用，否则判题程序会直接返回空）


  public static RandomListNode Clone(RandomListNode pHead) {
    // 2: 哈希表存 <N, N`>
    // 通过 N.random 就可以找到 N.random`
    // 空间 O(n) 换 时间 O(n)

    // 3 类似于栈 实现 O(1) min的做法
    // 新建结点 交叉在原始链表中间
    // A-A`-B-B`-C-C`
    cloneNodes(pHead);
    // S == N.random 那么 S` == N`.random == S.next = N.random.next
    connectRandom(pHead);
    // 拆分链表
    return divideList(pHead);
  }
  static void cloneNodes(RandomListNode pHead) {
    RandomListNode node = pHead;
    while (node != null) {
      RandomListNode cloned = new RandomListNode(node.label);
      cloned.next = node.next;
      cloned.random = null;
      node.next = cloned;
      node = cloned.next;
    }
  }
  static void connectRandom(RandomListNode pHead) {
    RandomListNode node = pHead;
    while (node != null) {
      RandomListNode cloned = node.next;
      if (node.random != null)
        cloned.random = node.random.next;
      node = cloned.next;
    }
  }
  static RandomListNode divideList(RandomListNode pHead) {
    RandomListNode node = pHead;
    RandomListNode clonedHead = null;
    RandomListNode clonedNode = null;

    if (node != null) {
      clonedHead = clonedNode = node.next;
      node.next = clonedNode.next;
      node = node.next;
    }
    while (node != null) {
      clonedNode.next = node.next;
      clonedNode = clonedNode.next;
      node.next = clonedNode.next;
      node = node.next;
    }
    return clonedHead;
  }
}

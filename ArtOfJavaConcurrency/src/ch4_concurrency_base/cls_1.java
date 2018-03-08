package ch4_concurrency_base;

import java.lang.management.ManagementFactory;
import java.lang.management.ThreadInfo;
import java.lang.management.ThreadMXBean;

public class cls_1 {
  public static void main(String[] args) {
    multiThread();
  }
  public static void multiThread() {
    // 获取Java线程管理MXBean
    ThreadMXBean threadMXBean = ManagementFactory.getThreadMXBean();
    // 不需要获取同步的monitor和 synchronizer信息，仅获取线程和线程堆栈信息
    ThreadInfo[] thdInfos = threadMXBean.dumpAllThreads(
            false, false);
    // 遍历线程信息，仅打印线程ID和名称
    for (ThreadInfo thdInfo : thdInfos)
      System.out.println("[" + thdInfo.getThreadId() + "]"
        + thdInfo.getThreadName());
    // [11]Monitor Ctrl-Break
    // [10]Common-Cleaner
    // [5]Attach Listener
    // [4]Signal Dispatcher
    // [3]Finalizer
    // [2]Reference Handler
    // [1]main
  }
}

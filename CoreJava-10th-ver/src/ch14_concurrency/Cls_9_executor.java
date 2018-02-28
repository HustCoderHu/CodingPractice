package ch14_concurrency;

import java.io.File;
import java.util.ArrayList;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;
import java.util.concurrent.FutureTask;

public class Cls_9_executor {
  public static void main(String[] args) {
  }
  
}

class Callaable_Future {
//  interface Callable<V> { V call() }
  // 与 Runnable 类似，但有返回值

  // Future 保存计算结果
  public static void test() throws InterruptedException, ExecutionException {
//    Callable<Integer> mycomput = ;
    MatchCounter mycomput = new MatchCounter(new File("/etc"),
            "host");
    FutureTask<Integer> task = new FutureTask<>(mycomput);
    Thread t = new Thread(task);
    t.start();
//    ...
//    Integer res = task.get(); // 阻塞
    long count = 0;
    ArrayList<Future<Integer>> results = new ArrayList<>();
    for (Future<Integer> res : results)
      count += res.get();
  }
}
class MatchCounter implements Callable<Integer> {
  public MatchCounter(File dir, String keyword) {
  }

  @Override
  public Integer call() {
    return null;
  }
}
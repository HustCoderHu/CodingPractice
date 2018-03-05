package ch14_concurrency;

import javax.lang.model.type.NullType;
import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.*;

import static java.util.concurrent.Executors.newFixedThreadPool;

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
  private File dir;
  private String keyword;
  private ExecutorService pool;
  public MatchCounter(File _dir, String _keyword, ExecutorService _pool) {
    dir = _dir;
    keyword = _keyword;
    pool = _pool;
  }

  @Override
  public Integer call() {
    // 使用相同的递归机制
    return null;
  }
}

class ThreadPool {
  public static void test() {
//    dir.listFiles();
    int nTasks = 20;
    ExecutorService tp = Executors.newFixedThreadPool(4);
    List<Future<Integer>> results = new ArrayList<>(nTasks);
    final MAX_FILES = 3000;
    List<File> fileQueue = new ArrayList<>(MAX_FILES);

    File dir = new File("/etc");
    MatchCounter counter = new MatchCounter(dir, "host", tp);

    for (int i = 0; i < 20; ++i) {
      results.add(tp.submit(counter));
    }

    tp.shutdown();
    int cnt = 0;
    for (Future<Integer> res : results) {
      try {
        cnt += res.get();
      } catch (ExecutionException e) {
        e.printStackTrace();
      } catch (InterruptedException e) {
        e.getMessage();
      }

    }

//    try {
//      for (int i = 0; i < 20; ++i)
//        cnt = results.get(i).get().intValue();
//    } catch (ExecutionException e)
//      e.printStack
  }
}
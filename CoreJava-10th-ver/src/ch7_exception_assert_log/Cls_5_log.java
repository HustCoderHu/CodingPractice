package ch7_exception_assert_log;

import com.sun.javafx.tools.packager.Log;

import java.util.logging.FileHandler;
import java.util.logging.Level;
import java.util.logging.Logger;

public class Cls_5_log {
  public static void main(String[] args) {
    Logger.getGlobal().setLevel(Level.OFF);
    Logger.getGlobal().info("File->open menu item selected");

    test1();
  }

  private static final Logger mylger = Logger.getLogger("com.mycompany.myapp");
  // SEVERE
  // WARNING
  // INFO
  // CONFIG
  // FINE
  // FINER
  // FINEST
  // 默认记录前三个级别
  private static void test1() {
    mylger.setLevel(Level.FINE); // FINE 往上(不包括FINE)级别都可以记录
    mylger.warning("msg warning");
    mylger.fine("msg fine"); // 不记录
    mylger.info("msg info");
    mylger.log(Level.FINER, ":msg finer"); // 不记录
  }
  // 日志管理器在VM启动过程中初始化，这在main执行之前完成

  private static void test2() {
//    FileHandler handler = new FileHandler();
//    mylger.addHandler(handler);
  }
}

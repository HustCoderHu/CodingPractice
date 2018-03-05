package ch6_if_lambda_interclass;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Date;

public class Cls_interclass {
  public static void main(String[] args) {
  }
}

// 内部类
// 可以访问该类定义所在的作用域中的数据，包括private
// 对同一个包中其他类不可见
// 定义回调函数 又不想写大量代码，使用匿名内部类便捷 或者 lambda

class TalkingClock {
  private int interval;
  private boolean beep;

  public TalkingClock(int intvl, boolean _beep) {
  }
  public void start() {
    // 局部内部类
    // class xxx
    // 不能用 public ，private
    // 可以访问 final 局部 var
  }
  public class TimePrinter implements ActionListener {
    // 所有 static 域 都必须是 final
    @Override
    public void actionPerformed(ActionEvent e) {
      System.out.println("At the tone, the time is " + new Date());
      if (beep) // 引用了 TalkingClock 的 beep
        // outer.beep
        Toolkit.getDefaultToolkit().beep();
    }
  }
}
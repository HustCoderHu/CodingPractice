package ch1_stream_file;

import java.io.*;
import java.nio.charset.Charset;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Scanner;

// http://hw1287789687.iteye.com/blog/2304745

public class St1 {
  public static void main(String[] args) {
    try {
      fileStream();
    } catch (IOException e) {
//      e.printStackTrace();
    }
  }
  static void fileStream() throws IOException {
    System.out.println(File.separator);
    File f = new File("f:/postGraduate/Resume.md");
    BufferedInputStream ifstream = null;
    byte[] dat = null;

    Charset charset = Charset.forName("UTF-8");

    try {
      ifstream = new BufferedInputStream(new FileInputStream(f));
    } catch (IOException e) {
      e.printStackTrace();
      throw e;
    }
//    System.out.printf("ifstream == null ? %b \n", ifstream==null);

    try {
      int bytesAvail = ifstream.available(); // file size
      System.out.println("bytesAvail = " + bytesAvail);
      if (bytesAvail > 0) {
        dat = new byte[bytesAvail];
        ifstream.read(dat);
        String str = new String(dat, charset);

        System.out.println(str);
      }
    } finally {
      System.out.println("close it");
      ifstream.close();
    }
  }

  static void fileIn() {
    String fstr = "f:/postGraduate/Resume.md";
    Scanner scanner = new Scanner(fstr);
//    scanner.useDelimiter(","); // 默认空格分隔
    scanner.useDelimiter(" |,|.");
  }
}

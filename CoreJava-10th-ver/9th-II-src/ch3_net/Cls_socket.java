package ch3_net;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.HashSet;
import java.util.Scanner;

public class Cls_socket {
  public static void main(String[] args) {
    skt();
  }

  static void skt(){
    Socket s = new Socket();
    String host = "www.baidu.com";
    int port = 80;
//    try (Socket s = new Socket("www.baidu.com", 80)) {
//    try (Socket s = new Socket("61.135.169.121", 443)) {
    int timeout = 3000;
    try {
      s.connect(new InetSocketAddress(host, port), timeout);
      System.out.println(s.isConnected());
//      s.setSoTimeout(10000); // time out after 10 seconds
      InputStream instream = s.getInputStream();
      Scanner in = new Scanner(instream);
      while (in.hasNextLine()) {
        String line = in.nextLine();
        System.out.println(line);
      }
      s.close();
    } catch (IOException e) {
      System.out.println(e.getLocalizedMessage());
//      e.printStackTrace();
    } finally {

    }
  }

  static void customizedServer() throws IOException {
    try (ServerSocket s = new ServerSocket(8189)) {
      // wait for client connection
      try (Socket incoming = s.accept()) {

      }
    }

  }
}

class ThreadedEchoServer {
  public static void mainLoop() {
    try {
      int i = 1;
      ServerSocket s = new ServerSocket(8189);
      while (true) {
        Socket incoming = s.accept();
        System.out.println("spawning " + i);
        Runnable r = new ThreadedEchoHandler(incoming);
        Thread t = new Thread(r);
        t.start();
        ++i;
      }
    } catch (IOException e) {
      e.printStackTrace();
    }
  }
}

class ThreadedEchoHandler implements Runnable {
  private Socket incoming;

  public ThreadedEchoHandler(Socket incoming) {
    this.incoming = incoming;
  }

  @Override
  public void run() {
    try {
      InputStream instream = incoming.getInputStream();
      OutputStream outstream = incoming.getOutputStream();
      try (Scanner scanner = new Scanner(instream)) {
        PrintWriter out = new PrintWriter(outstream, true);
        // autoFlush: true
        out.println("hello ! enter bye to exit.");

        // echo client input
        boolean done = false;
        while (!done && scanner.hasNextLine()) {
          String line = scanner.nextLine();
          out.println("Echo: " + line);
          if (line.trim().equals("bye"))
            done = true;
        }
      }
      incoming.close();
    } catch (IOException e) {
    }
  }
}
package ch1_stream_file;

import java.io.*;
//import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.MappedByteBuffer;
import java.nio.channels.FileChannel;
import java.nio.charset.Charset;
import java.nio.file.*;
import java.util.List;
import java.util.zip.CRC32;

public class Cls_1_6_fileop {
  public static void main(String[] args) throws IOException {
//    rwFile();
    try {
//      cp_mv_del_file();
      file_mmap();
    } catch (IOException e) {
      System.out.println(e.getCause());
      System.out.println(e.getMessage());
    }
  }

  static void rwFile() throws IOException {
    //    Path absolute = Paths.get()
    Path relative = Paths.get("f:", "postGraduate");
    Path mdPath = relative.resolve("Resume.md"); // f:/postGraduate/Resume.md
    // f:/postGraduate/aaa.md
//    Path siblingPath = mdPath.resolveSibling("aaa.md");
//    System.out.println(mdPath.toString());
    // f:\postGraduate\Resume.md
//    System.out.println(mdPath.getFileSystem().toString());
//    System.out.println(mdPath.getRoot()); // f:\
//    System.out.println(mdPath.getFileName()); // Resume.md

    byte[] bytes = Files.readAllBytes(mdPath);
    Charset charset = Charset.forName("UTF-8");
    String content = new String(bytes, charset);
//    new String(bytes, "UTF-8");
//    System.out.println(content);
    List<String> lines = Files.readAllLines(mdPath, charset);
    System.out.println(lines.size());
    System.out.println(lines.listIterator().next());

//    Files.write(dstPath, content.getBytes(charset));
    // 追加
//    Files.write(dstPath, content.getBytes(charset), StandardOpenOption.APPEND);
    // 写 集合
//    Files.write(dstPath, lines, StandardOpenOption.APPEND);
    // 以上 适合中等长度的文本

    // 长度大 则用流 或者 reader writer
    InputStream in = Files.newInputStream(mdPath);
//    OutputStream out = Files.newOutputStream(dstPath);

    InputStream in1 = new BufferedInputStream(in);

    Reader in2 = Files.newBufferedReader(mdPath, charset);
//    Reader out2 = Files.newBufferedWriter(dstPath, charset);
  }

  static void cp_mv_del_file() throws IOException{
    Path fromPath = Paths.get("f:", "postGraduate");
    String fname = "222Resume.md";
    Path dstPath = Paths.get("f:", "postGraduate222");
    Files.copy(fromPath.resolve(fname), dstPath.resolve(fname),
            StandardCopyOption.REPLACE_EXISTING, // 覆盖目标文件
            StandardCopyOption.COPY_ATTRIBUTES); // 复制所有属性

    Files.move(fromPath.resolve(fname), dstPath.resolve(fname));

    // 删除
    boolean deleted = Files.deleteIfExists(dstPath); // 可以移除空目录

    Files.createDirectories(dstPath); // mkdir -p
    Files.createFile(dstPath.resolve(fname)); // touch fname
    // exception if exist

    Files.exists(dstPath);
    Files.isDirectory(dstPath);
    Files.size(dstPath); // 文件字节大小
  }

  static void file_mmap() throws IOException{
    Path dir = Paths.get("D:\\VMware_Instances\\ISOsLinux");
    String fname = "debian-live-8.4.0-amd64-gnome-desktop.iso";

    long start = System.currentTimeMillis();

    FileChannel channel = FileChannel.open(dir.resolve(fname));
    long fsize = Files.size(dir.resolve(fname));
    long mappedSize = fsize; // 500 * 1024 * 1024;

    // map 大文件更值得
    MappedByteBuffer buf = channel.map(FileChannel.MapMode.READ_ONLY, 0, mappedSize); // pos =0
//    FileChannel.MapMode.READ_WRITE;
//    FileChannel.MapMode.PRIVATE; //修改不会反映到文件
    // 二进制 高位在前，转换到低位在前
//    buf.getInt();
//    buf.getLong();
    buf.order(ByteOrder.LITTLE_ENDIAN);

    CRC32 crc = new CRC32();
    for (int p = 0; p < fsize; p++) {
      int c = buf.get(p);
      crc.update(c);
    }
    long crcVal = crc.getValue();

    long end = System.currentTimeMillis();
    System.out.println(Long.toHexString(crcVal));
    System.out.println("mapped file:");
    System.out.println((end - start) + " milliseconds");
  }
}

import java.sql.*;
import java.util.List;

public class FirstSqlite {
  static String dbname = "firstSqlite.db";

//  enum Gender {
//    FEMAIL, MALE
//  }

  public static void main(String[] args) {
    Connection conn = null;
    try {
      Class.forName("org.sqlite.JDBC");// 加载类
      // Class.forName()用法详解
      // https://blog.csdn.net/kaiwii/article/details/7405761
      conn = DriverManager.getConnection("jdbc:sqlite:"+dbname);
//      createTable(conn);
//      addItem(conn);
      showTable(conn, "employees", 6);
      conn.close();
    } catch ( SQLException e ) {
      System.err.println( e.getClass().getName() + ": " + e.getMessage() );
      System.exit(0);
    } catch ( Exception e ) {
      System.err.println( e.getClass().getName() + ": " + e.getMessage() );
      System.exit(0);
    }
  }

  public static void createTable(Connection conn) {
    Statement stmt = null;
    try {
      stmt = conn.createStatement();
      // JDBC 之: Statement 接口和 ResultSet(三)
      // http://www.matrix42.cn/index.php/archives/15/
      String sql = "CREATE TABLE IF NOT EXISTS `employees` (\n" +
              "`emp_no` int(11) NOT NULL,\n" +
              "`birth_date` date NOT NULL,\n" +
              "`first_name` varchar(14) NOT NULL,\n" +
              "`last_name` varchar(16) NOT NULL,\n" +
              "`gender` char(1) NOT NULL,\n" +
              "`hire_date` date NOT NULL,\n" +
              "PRIMARY KEY (`emp_no`));";
      // https://www.nowcoder.com/ta/sql
      stmt.executeUpdate(sql);
      stmt.close();
//      conn.commit();
    } catch ( SQLException e ) {
      System.err.println( e.getClass().getName() + ": " + e.getMessage() );
      System.exit(0);
    } catch ( Exception e ) {
      System.err.println( e.getClass().getName() + ": " + e.getMessage() );
      System.exit(0);
    }
    System.out.println("Table created successfully");
  }

  static void addItem(Connection conn) {
    try {
      ins2Table_employees(conn, 10008, "1958-02-19",
              "Saniya", "Kalloufi", 'M', "1994-09-15");
      ins2Table_employees(conn, 10010, "1958-02-19",
              "Saniya", "Kalloufi", 'F', "1995-09-15");
      ins2Table_employees(conn, 10020, "1958-02-19",
              "Saniya", "Kalloufi", 'F', "1996-09-15");
      ins2Table_employees(conn, 10030, "1958-02-19",
              "HH", "aa", 'F', "1996-09-15");
    } catch ( SQLException e ) {
      System.err.println( e.getClass().getName() + ": " + e.getMessage() );
      System.exit(0);
    } catch ( Exception e ) {
      System.err.println( e.getClass().getName() + ": " + e.getMessage() );
      System.exit(0);
    }
  }
  static void ins2Table_employees(Connection conn,
          int emp_no, String birth_date, String first_name,
          String last_name, char gender, String hire_date) throws SQLException {
    PreparedStatement stmt = null;
    try {
      String sql = "INSERT INTO employees\n" +
              "(emp_no, birth_date, first_name, last_name, gender, hire_date)\n" +
              "VALUES(?,?,?,?,?,?)";
      stmt = conn.prepareStatement(sql);
      stmt.setInt(1, emp_no);
      stmt.setObject(2, birth_date);
      stmt.setObject(3, first_name);
      stmt.setObject(4, last_name);
      stmt.setObject(5, gender);
      stmt.setObject(6, hire_date);
      stmt.execute();
      stmt.close();
    } catch (SQLException e) {
      System.err.println( e.getClass().getName() + ": " + e.getMessage() );
      System.exit(0);
      throw e;
    }
  }

  static void showTable(Connection conn, String tname, int col) {
    Statement stmt = null;
    try {
      String sql = "SELECT * FROM " + tname;
      stmt = conn.createStatement();
      ResultSet rs = stmt.executeQuery(sql);
      while (rs.next()) {
//        int emp_no = rs.getInt("emp_no");
//        String hire_date = rs.getString("hire_date");
//        String row = rs.toString()
        for (int i = 1; i <=col; i++) {
          String s = rs.getString(i);
          System.out.print(s);
          System.out.print(" ");
        }
        System.out.println();
      }
    } catch (SQLException e) {
      System.err.println( e.getClass().getName() + ": " + e.getMessage() );
      System.exit(0);
    }

  }
  public static void runSql(Connection conn, String sql)
          throws SQLException {
  }
  public static void runSql(Connection conn, String[] sqls)
          throws SQLException {
    for (String s : sqls)
      runSql(conn, s);
  }
  public static void runSql(Connection conn, List<String> sqls)
          throws SQLException {
    for (String s : sqls)
      runSql(conn, s);
  }
}
// http://www.runoob.com/sqlite/sqlite-java.html
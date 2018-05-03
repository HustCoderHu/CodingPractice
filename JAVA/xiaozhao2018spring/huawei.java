package xiaozhao2018spring;
import java.util.*;

public class huawei {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    String str = "98766730";
//    str = "100123400";
    str = sc.next();
    boolean[] exist = new boolean[10];
    int[] num = new int[str.length()];
//    StringBuilder sb = new StringBuilder(str.length());

    int j = 0;
    for (int i = 0; i < str.length(); i++) {
      if (exist[str.charAt(i) - '0'] == false) {
        num[j++] = str.charAt(i) - '0';
        exist[str.charAt(i) - '0'] = true;
      }
    }
    if (num[j-1]!=0)
      System.out.print(num[j-1]);
    for (j = j-2; j >= 0; --j)
      System.out.print(num[j]);
  }
}

class H2 {
  static int[] tt = {-170,0,40,300,550};
  static int[] ff = {-1000,700,940,2500,7500};
  public static void main(String[] args)
  {
    Scanner sc = new Scanner(System.in);
    int temp = 100;
//    temp = sc.nextInt();
    int f = -1;
    for(int i = 0;i < 5;++i)
      if(temp >= tt[i])f = i;

    int res = 0;
    if (temp == tt[f])
      res = ff[f];
    else if (temp <= -400)
      res = -1000;
    else if (temp >= 1000)
      res = 7500;
    else {
      int x0 = (f+5)%5;
      int x1 = (f+1)%5;
      int y0 = ff[x0];

      int k = (temp - tt[x0])*(ff[x1] - ff[x0]);
      k /= (tt[x1] - tt[x0]);
      res = k + y0;
//      res = (int)((float)(ff[f + 1] - ff[f])/(float)(tt[f + 1] - tt[f]) * (temp - tt[f])) + ff[f];
    }
    System.out.println(res);
  }
}

class H3 {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    Map<String, Map<String, String>> all = new TreeMap<>();

    Map<String, String> m = null;
    int i = 0;
    while (sc.hasNext()) {
      String s = sc.next();
      s.trim();
      if (s.charAt(0) == '[') {
        i = 1;
        while (s.charAt(i) != ']')
          ++i;
        String sec = s.substring(1, i);
        m = all.get(sec);
        if (m == null) {
          m = new TreeMap<>();
          all.put(sec, m);
        }
      } else {
        s.split(" |=");
      }
    }
  }
}

class yishuai2 {
  static int[] tt = {-170,0,40,300,550};
  static int[] ff = {-1000,700,940,2500,7500};
  public static void main(String[] args)
  {
    Scanner sc = new Scanner(System.in);
    int temp = 100;
//    int temp = sc.nextInt();
    int f = -1;
    for(int i = 0;i < 5;++i)
    {
      if(temp >= tt[i])f = i;
    }
    int res = 0;
    if(f == 4)f = 3;
    else if(f == -1)f = 0;
    else
    {
      if(temp > 1000)temp = 1000;
      if(temp < -400)temp = -400;
      res = (int)(((float)temp - tt[f + 1])/(tt[f] - tt[f + 1])*ff[f] + ((float)temp - tt[f])/(tt[f + 1] - tt[f])*ff[f + 1]);
    }

    //System.out.println(f);
    System.out.println(res);
  }
}

class out {
  String outsection;
  String outkey;
  String outvalue;

  @Override
  public String toString() {
    String s = "{" + outsection + "}" +
            "{" + outkey + "}" +
            "{" + outvalue + "}";
    return s;
  }
}

class yishuai3 {
  public static void main(String[] args)
  {
    Scanner sc = new Scanner(System.in);
    String input = "";
    String[] inputArray;
    String outsection = "";
    ArrayList<out> o = new ArrayList<>();
    while(sc.hasNext()) {
      input = sc.nextLine();
      input.trim();
      //if(input.compareTo("EOF") == 0)break;
      if(input.length() == 0 || input.charAt(0) == ';')continue;
      input = input.split(";")[0];
      inputArray = input.split("[=]");

      if(inputArray.length == 1)
        outsection = inputArray[0].substring(1, inputArray[0].length() - 1);
      else {
        out oo = new out();
        oo.outsection = outsection;
        oo.outkey = inputArray[0].trim();
        oo.outvalue = inputArray[1].trim();
        o.add(oo);
      }
    }
    Collections.sort(o,(x,y)->{
      if(x.outsection.compareTo(y.outsection)==0)
        return x.outkey.compareTo(y.outkey);
      else
        return x.outsection.compareTo(y.outsection);
    });
    for(out oo : o)
      System.out.println(oo.toString());
  }
}
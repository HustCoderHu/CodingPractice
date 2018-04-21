package leetcode;

import java.util.LinkedList;
import java.util.List;

public class _17LetterCombinationsofAPhoneNumber {
  public List<String> letterCombinations(String digits) {
    LinkedList<String> ans = new LinkedList<String>();
//    LinkedList<StringBuilder> res = new LinkedList<StringBuilder>();
    if(digits == null || digits.isEmpty()) return ans;

    String[] mapping = new String[] {"0", "1", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    ans.add("");
    for(int i =0; i<digits.length();i++) {
      int x = digits.charAt(i) - '0';
//      int x = Character.getNumericValue(digits.charAt(i));
      // Integer.parseInt(String.valueOf("3");
      while(ans.peek().length()==i) {
        String t = ans.remove();
        for(char s : mapping[x].toCharArray())
          ans.add(t+s);
      }
    }
    return ans;
  }
}

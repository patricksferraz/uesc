/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package utils;

/**
 *
 * @author eeeeeeeeeeeeeeeeeeee
 */
public class StringUtils {
    
    public static int findSpecialChar(String string) 
    {
        char[] chars = string.toCharArray();
        for (int i = 0; i < chars.length; i++) {
            if(!Character.isLetter(chars[i]) && !Character.isWhitespace(chars[i])) {
                return i;
            }
        }
        return -1;
    }
    
    public static boolean isStringInteger(String input)
    {
       try
       {
          Integer.parseInt( input );
          return true;
       }
       catch(NumberFormatException ex)
       {
          return false;
       }
    }
}

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
public class DoubleUtils {

    public static String formatDoubleToString(double number)
    {
        String num = String.valueOf(number);
        num = num.replace(".", ",");
        
        
        int decimal = (int) number;
        double fractional = number - decimal;
        
        if(fractional == 0)
            num = num.substring(0, num.indexOf(","));

        return num;
    }
}

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package utils;

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;

/**
 *
 * @author eeeeeeeeeeeeeeeeeeee
 */
public class StringUtilsTest {
    
    public StringUtilsTest() {
    }
    
    @BeforeClass
    public static void setUpClass() {
    }
    
    @AfterClass
    public static void tearDownClass() {
    }
    
    @Before
    public void setUp() {
    }
    
    @After
    public void tearDown() {
    }

     @Test
     public void testStringUtils() {
         //Test Encontrar Char especiais na String
         assertEquals(0, StringUtils.findSpecialChar("#Arara"));
         assertEquals(2, StringUtils.findSpecialChar("Ar@ra"));
         assertEquals(-1, StringUtils.findSpecialChar("Arara"));
         
         //Test Verificar se String é um Numero
         assertEquals(true, StringUtils.isStringInteger("123"));
         assertEquals(false, StringUtils.isStringInteger("Arara"));
     }
}

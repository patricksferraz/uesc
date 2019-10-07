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
public class DoubleUtilsTest {
    
    public DoubleUtilsTest() {
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
     public void testDoubleUtils() {
         //Test Format
         Double db = 123.34;
         assertEquals("123,34", DoubleUtils.formatDoubleToString(db));
         db = 123.00;
         assertEquals("123", DoubleUtils.formatDoubleToString(db));
     }
}

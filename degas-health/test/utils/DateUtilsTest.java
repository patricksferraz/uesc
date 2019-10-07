/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package utils;

import java.util.logging.Level;
import java.util.logging.Logger;
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
public class DateUtilsTest {
    
    public DateUtilsTest() {
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
     public void testDateUtils() {
        //Validando Data
        assertEquals(true, DateUtils.validateDate("20/12/1996"));
        assertEquals(true, DateUtils.validateDate("20/10/2012"));
        assertEquals(false, DateUtils.validateDate("32/12/1996"));

        //Criando data a partir de String
        assertNotEquals(null, DateUtils.createDateFromString("20/12/1996"));
        assertNotEquals(null, DateUtils.createDateFromString("20/10/2012"));
        assertEquals(null, DateUtils.createDateFromString("32/12/1996"));

        //Formatando Data Para String
        assertEquals("20/12/1996", DateUtils.formatDateBR(DateUtils.createDateFromString("20/12/1996")));
        assertEquals("20/10/2012", DateUtils.formatDateBR(DateUtils.createDateFromString("20/10/2012")));
        
     }
}

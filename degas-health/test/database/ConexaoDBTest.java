/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package database;

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
public class ConexaoDBTest {
    
    public ConexaoDBTest() {
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
     public void testConexaoDB() 
     {   
         assertEquals(ConexaoDB.statusConection(), "Não conectou...");
         ConexaoDB.getConexaoMySQL();
         assertEquals(ConexaoDB.statusConection(), "STATUS--->Conectado com sucesso!");
         ConexaoDB.ReiniciarConexao();
         assertEquals(ConexaoDB.statusConection(), "STATUS--->Conectado com sucesso!");
         assertEquals(ConexaoDB.FecharConexao(), true);
     }
}

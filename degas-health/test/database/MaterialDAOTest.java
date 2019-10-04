/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package database;

import java.sql.Connection;
import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;
import tipos.Material;

/**
 *
 * @author eeeeeeeeeeeeeeeeeeee
 */
public class MaterialDAOTest {
    
    public MaterialDAOTest() {
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
     public void testMaterialDAO() {
         //Teste inserção
        Connection conn = ConexaoDB.getConexaoMySQL();
        Material m = new Material("1231234", "Material Test", "1234.50");
        try {
            MaterialDAO.InserirMaterial(m, conn);
        } catch (Exception ex) {
            //NÂO DEVE TER EXCEPTION
        }
        //TENTANDO ADICIONAR O MESMO Material
        try {
            MaterialDAO.InserirMaterial(m, conn);
        } catch (Exception ex) {
            assertEquals(ex.getMessage(), "Material já cadastrado");
        }
        
        //Recuperando Material do BD
        Material mExistente;
        try {
            mExistente = MaterialDAO.consultarMaterialPorCodigo(m.getCodigo(), conn);
            assertEquals(mExistente.toString(), m.toString());
        } catch (Exception ex) {
            //NÂO DEVE TER EXCEPTION
        }
        //Recuperando Especialidade inexistente deve retornar null
        try {
            mExistente = MaterialDAO.consultarMaterialPorCodigo(666666, conn);
            assertEquals(mExistente, null);
        } catch (Exception ex) {
            //NÂO DEVE TER EXCEPTION
        }
        
     }
}

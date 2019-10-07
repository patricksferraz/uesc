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
import tipos.Especialidade;

/**
 *
 * @author eeeeeeeeeeeeeeeeeeee
 */
public class EspecialidadeDAOTest {
    
    public EspecialidadeDAOTest() {
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
     public void testEspecialidadeDAO() {
        //Teste inserção
        Connection conn = ConexaoDB.getConexaoMySQL();
        Especialidade e = new Especialidade("123123", "Especialidade Codigo");
        try {
            EspecialidadeDAO.InserirEspecialidade(e, conn);
        } catch (Exception ex) {
            //NÂO DEVE TER EXCEPTION
        }
        //TENTANDO ADICIONAR A MESMA Especialidade
        try {
            EspecialidadeDAO.InserirEspecialidade(e, conn);
        } catch (Exception ex) {
            assertEquals(ex.getMessage(), "Especialidade já cadastrada");
        }
        
        //Recuperando Especialidade do BD
        Especialidade eExistente;
        try {
            eExistente = EspecialidadeDAO.consultarEspecialidadePorCodigo(e.getCodigo(), conn);
            assertEquals(eExistente.toString(), e.toString());
            eExistente = EspecialidadeDAO.consultarEspecialidadePorDescricao(e.getDescricao(), conn);
            assertEquals(eExistente.toString(), e.toString());
        } catch (Exception ex) {
            //NÂO DEVE TER EXCEPTION
        }
        //Recuperando Especialidade inexistente deve retornar null
        try {
            eExistente = EspecialidadeDAO.consultarEspecialidadePorCodigo(666666, conn);
            assertEquals(eExistente, null);
            eExistente = EspecialidadeDAO.consultarEspecialidadePorDescricao("INEXISTENTE", conn);
            assertEquals(eExistente.toString(), null);
        } catch (Exception ex) {
            //NÂO DEVE TER EXCEPTION
        }
        
     }
}

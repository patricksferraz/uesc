/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package database;

import java.sql.Connection;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;
import tipos.Auxiliar;
import tipos.Enfermeiro;
import tipos.Medico;

/**
 *
 * @author eeeeeeeeeeeeeeeeeeee
 */
public class FuncionarioDAOTest {
    
    public FuncionarioDAOTest() {
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
     public void testFuncionarioDAO() {
        Connection conn = ConexaoDB.getConexaoMySQL();
        Medico m = null;
        Enfermeiro e = null;
        Auxiliar ax = null;
        //ADICIONANDO FUNCIONARIOS
        try {
            m = new Medico("Gabriel do Teste", "M", "1231234", "Brasileiro", "20/12/1996", "01/12/2019", "31/12/2018");
            e = new Enfermeiro("Gabriel do Teste", "M", "1231234", "Brasileiro", "20/12/1996", "01/12/2019", "31/12/2018");
            ax = new Auxiliar("Gabriel do Teste", "M", "1231234", "Brasileiro", "20/12/1996", "01/12/2019", "31/12/2018");
            FuncionarioDAO.InserirFuncionario(m, conn);
            FuncionarioDAO.InserirFuncionario(e, conn);
            FuncionarioDAO.InserirFuncionario(ax, conn);
        } catch (Exception ex) {
            //NÂO DEVE TER EXCEPTION
        }
        
        //ADICIONANDO EXISTENTE
        try {
            FuncionarioDAO.InserirFuncionario(m, conn);
        } catch (Exception ex) {
            assertEquals(ex.getMessage(), "ERRO! CRM Já existente!");
        }
        try {
            FuncionarioDAO.InserirFuncionario(e, conn);
        } catch (Exception ex) {
            assertEquals(ex.getMessage(), "ERRO! COREN Já existente!");
        }
        try {
            FuncionarioDAO.InserirFuncionario(ax, conn);
        } catch (Exception ex) {
            assertEquals(ex.getMessage(), "ERRO! COREN Já existente!");
        }
        
        
        //RECUPERANDO FUNCIONARIO
        Medico mExistente;
        Enfermeiro eExistente;
        Auxiliar axExistente;
        
        try {
            mExistente = (Medico) FuncionarioDAO.consultarFuncionarioPorCodigo(m.getCodigo(), conn, "Medico");
            assertEquals(m.toString(), mExistente.toString());
            mExistente = (Medico) FuncionarioDAO.consultarFuncionarioPorNome(m.getNome(), conn, "Medico");
            assertEquals(m.toString(), mExistente.toString());
            eExistente = (Enfermeiro) FuncionarioDAO.consultarFuncionarioPorCodigo(e.getCodigo(), conn, "Enfermeiro");
            assertEquals(e.toString(), eExistente.toString());
            eExistente = (Enfermeiro) FuncionarioDAO.consultarFuncionarioPorNome(e.getNome(), conn, "Enfermeiro");
            assertEquals(e.toString(), eExistente.toString());
            axExistente = (Auxiliar) FuncionarioDAO.consultarFuncionarioPorCodigo(ax.getCodigo(), conn, "Auxiliar");
            assertEquals(ax.toString(), axExistente.toString());
            axExistente = (Auxiliar) FuncionarioDAO.consultarFuncionarioPorNome(ax.getNome(), conn, "Auxiliar");
            assertEquals(ax.toString(), axExistente.toString());
        } catch (Exception ex) {
            //NÂO DEVE TER EXCEPTION
        }
        
        //Recuperando Funcionario Inexistente
        try {
            mExistente = (Medico) FuncionarioDAO.consultarFuncionarioPorCodigo(123, conn, "Medico");
            assertEquals(mExistente, null);
            mExistente = (Medico) FuncionarioDAO.consultarFuncionarioPorNome(m.getNacionalidade(), conn, "Medico");
            assertEquals(mExistente, null);
            eExistente = (Enfermeiro) FuncionarioDAO.consultarFuncionarioPorCodigo(123, conn, "Enfermeiro");
            assertEquals(eExistente, null);
            eExistente = (Enfermeiro) FuncionarioDAO.consultarFuncionarioPorNome(e.getNacionalidade(), conn, "Enfermeiro");
            assertEquals(eExistente, null);
            axExistente = (Auxiliar) FuncionarioDAO.consultarFuncionarioPorCodigo(123, conn, "Auxiliar");
            assertEquals(axExistente, null);
            axExistente = (Auxiliar) FuncionarioDAO.consultarFuncionarioPorNome(ax.getNacionalidade(), conn, "Auxiliar");
            assertEquals(axExistente, null);
        } catch (Exception ex) {
            //NÂO DEVE TER EXCEPTION
        }
        
     }
}

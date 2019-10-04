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
import tipos.Procedimento;

/**
 *
 * @author eeeeeeeeeeeeeeeeeeee
 */
public class ProcedimentoDAOTest {
    
    public ProcedimentoDAOTest() {
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
     public void testProcedimentoDAO() {
        //Teste inserção
        Connection conn = ConexaoDB.getConexaoMySQL();
        Procedimento p = null;
        try {
            p = new Procedimento("1231234", "Procedimento Test", "1234");
            ProcedimentoDAO.InserirProcedimento(p, conn);
        } catch (Exception ex) {
            //NÂO DEVE TER EXCEPTION
        }
        //TENTANDO ADICIONAR O MESMO Material
        try {
            ProcedimentoDAO.InserirProcedimento(p, conn);
        } catch (Exception ex) {
            assertEquals(ex.getMessage(), "Código de Procedimento Ja Cadastrado");
        }
        
        try {
            p.setCodigo("123");
            ProcedimentoDAO.InserirProcedimento(p, conn);
        } catch (Exception ex) {
            assertEquals(ex.getMessage(), "Descrição de Procedimento Ja Cadastrado");
            p.setCodigo("1231234");
        }
        
        //Recuperando Material do BD
        Procedimento pExistente;
        try {
            pExistente = ProcedimentoDAO.consultarProcedimento("codigo", String.valueOf(p.getCodigo()), conn);
            assertEquals(pExistente.toString(), p.toString());
            pExistente = ProcedimentoDAO.consultarProcedimento("descricao", p.getDescricao(), conn);
            assertEquals(pExistente.toString(), p.toString());
        } catch (Exception ex) {
            //NÂO DEVE TER EXCEPTION
        }
        //Recuperando Especialidade inexistente deve retornar null
        try {
            pExistente = ProcedimentoDAO.consultarProcedimento("codigo", "123", conn);
            assertEquals(pExistente, null);
            pExistente = ProcedimentoDAO.consultarProcedimento("descricao", "1123", conn);
            assertEquals(pExistente, null);
        } catch (Exception ex) {
            //NÂO DEVE TER EXCEPTION
        }
        
        //Alterando Procedimento
        try {
            String res = ProcedimentoDAO.alterarProcedimentoPorCodigo(p.getCodigo(), "descricao", "Procedimento Test Editado", conn);
            assertEquals(res, "Procedimento alterado com sucesso");
        } catch (Exception ex) {
            //NÂO DEVE TER EXCEPTION
        }
     }
}

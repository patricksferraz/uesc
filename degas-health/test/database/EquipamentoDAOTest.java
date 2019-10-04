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
import tipos.Equipamento;
import tipos.Tombo;

/**
 *
 * @author eeeeeeeeeeeeeeeeeeee
 */
public class EquipamentoDAOTest {
    
    public EquipamentoDAOTest() {
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
     public void testEquipamentoDAO() {
        //Teste inserção
        Connection conn = ConexaoDB.getConexaoMySQL();
        Equipamento e = new Equipamento("66675", "Equipamento de Teste", "1234");
        try {
            EquipamentoDAO.InserirEquipamento(e, conn);
        } catch (Exception ex) {
            //NÂO DEVE TER EXCEPTION
        }
        //TENTANDO ADICIONAR MESMO EQUIPAMENTO
        try {
            EquipamentoDAO.InserirEquipamento(e, conn);
        } catch (Exception ex) {
            assertEquals(ex.getMessage(), "Equipamento já cadastrado");
        }
        
        //Recuperando equipamento do BD
        Equipamento eExistente;
        try {
            eExistente = EquipamentoDAO.consultarEquipamentoPorCodigo(e.getCodigo(), conn);
            assertEquals(eExistente.toString(), e.toString());
        } catch (Exception ex) {
            //NÂO DEVE TER EXCEPTION
        }
        //Recuperando Equipamento inexistente deve retornar null
        try {
            eExistente = EquipamentoDAO.consultarEquipamentoPorCodigo(666666, conn);
            assertEquals(eExistente, null);
        } catch (Exception ex) {
            //NÂO DEVE TER EXCEPTION
        }
        
        //Adicionando Tombo
        //Inserindo tombo com equipamento inexistente
        Tombo t = new Tombo("66676", "GA123");
        try {
            EquipamentoDAO.inserirTombo(t, conn);
        } catch (Exception ex) {
            assertEquals(ex.getMessage(), "Erro: Equipamento não existe");
        }
        //Inserindo normal
        t.setCodigoEquipamento(String.valueOf(e.getCodigo()));
        try {
            EquipamentoDAO.inserirTombo(t, conn);
        } catch (Exception ex) {
            //NÂO DEVE TER EXCEPTION
        }
        //Codigo de Tombo duplicado
        try {
            EquipamentoDAO.inserirTombo(t, conn);
        } catch (Exception ex) {
            assertEquals(ex.getMessage(), "Erro: Tombo já existente");
        }
        
        //Recuperar tombo
        Tombo tExistente;
        try {
            tExistente = EquipamentoDAO.consultarTomboPorCodigoTombo(t.getCodigoTombo(), conn);
            assertEquals(tExistente.toString(), t.toString());
        } catch (Exception ex) {
            //NÂO DEVE TER EXCEPTION
        }
        //Recuperar tombo inexistente
        try {
            tExistente = EquipamentoDAO.consultarTomboPorCodigoTombo("arara", conn);
        } catch (Exception ex) {
            assertEquals(ex.getMessage(), null);
        }
        
        
     }
}

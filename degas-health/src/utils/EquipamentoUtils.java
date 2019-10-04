/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package utils;

import database.ConexaoDB;
import database.EquipamentoDAO;
import java.sql.Connection;
import tipos.Equipamento;
import tipos.Tombo;

/**
 *
 * @author eeeeeeeeeeeeeeeeeeee
 */
public class EquipamentoUtils {
    
    public static String novoEquipamento(String codigo, String descricao, String valor)
    {
        try
        {
            Equipamento eqp = new Equipamento(codigo, descricao, valor);
            Connection conn = ConexaoDB.getConexaoMySQL();
            EquipamentoDAO.InserirEquipamento(eqp, conn);
            conn.close();
        }
        catch (Exception ex)
        {
            return ex.getMessage();
        }
        return "Equipamento cadastrado com sucesso";
    }
    
    public static String tombaEquipamento(String codigoEquipamento, String codigoTombo)
    {
        try
        {
            Connection conn = ConexaoDB.getConexaoMySQL();
            Tombo t = new Tombo(codigoEquipamento, codigoTombo);
            EquipamentoDAO.inserirTombo(t, conn);
            conn.close();
        }
        catch (Exception ex)
        {
            return ex.getMessage();
        }
        
        return "Equipamento tombado com sucesso";
    }
}

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package database;

import java.sql.CallableStatement;
import java.sql.Connection;
import java.sql.ResultSet;
import tipos.Equipamento;
import tipos.Tombo;

/**
 *
 * @author eeeeeeeeeeeeeeeeeeee
 */
public class EquipamentoDAO {

    public static void InserirEquipamento(Equipamento eqp, Connection conn) throws Exception {
        String query;
        
        Equipamento eqpExistente = consultarEquipamentoPorCodigo(eqp.getCodigo(), conn);
        
        if(eqpExistente == null)
        {
            query = "{CALL insert_equipamento(?, ?, ?)}";
            CallableStatement stmt = conn.prepareCall(query);
            stmt.setInt(1, eqp.getCodigo());
            stmt.setString(2, eqp.getDescricao());
            stmt.setDouble(3, eqp.getValor());
            
            stmt.execute();
        }
        else
            throw new Exception("Equipamento já cadastrado");
    }

    public static Equipamento consultarEquipamentoPorCodigo(int codigo, Connection conn) throws Exception
    {
        String query = "{CALL get_equipamento_by_code(?)}";
        CallableStatement stmt = conn.prepareCall(query);
        stmt.setInt(1, codigo);
        
        ResultSet rs = stmt.executeQuery();
        
        if(rs.next())
        {
            Equipamento eqp = new Equipamento(rs.getString("codigo"), rs.getString("descricao"), rs.getString("valor"));
            rs.close();
            return eqp;
        }
        return null;
    }

    public static void inserirTombo(Tombo t, Connection conn) throws Exception {
        String query;
        Equipamento eqpExistente = consultarEquipamentoPorCodigo(t.getCodigoEquipamento(), conn);
        Tombo tExistente = consultarTomboPorCodigoTombo(t.getCodigoTombo(), conn);

        if(eqpExistente == null)
            throw new Exception("Erro: Equipamento não existe");
        else if(tExistente != null)
            throw new Exception("Erro: Tombo já existente");
        else
        {
            query = "{CALL insert_tombo(?, ?)}";
            CallableStatement stmt = conn.prepareCall(query);
            stmt.setInt(1, obterIdDBEquipamentoPorCodigo(eqpExistente.getCodigo(), conn));
            stmt.setString(2, t.getCodigoTombo());
            
            stmt.execute();
        }
            
    }

    public static Tombo consultarTomboPorCodigoTombo(String codigoTombo, Connection conn) throws Exception {
        String query = "{CALL get_tombo_by_code(?)}";
        CallableStatement stmt = conn.prepareCall(query);
        stmt.setString(1, codigoTombo);
        
        ResultSet rs = stmt.executeQuery();
        
        if(rs.next())
        {
            Tombo t = new Tombo(rs.getString("codigoEquipamento"), rs.getString("codigoTombo"));
            rs.close();
            return t;
        }
        return null;
    }
    
    public static int obterIdDBEquipamentoPorCodigo(int codigo, Connection conn) throws Exception
    {
        String query = "{CALL get_equipamento_by_code(?)}";
        CallableStatement stmt = conn.prepareCall(query);
        stmt.setInt(1, codigo);
        
        ResultSet rs = stmt.executeQuery();
        
        
        if(rs.next())
            return rs.getInt("id");
        else
            throw new Exception("Codigo de Equipamento não Existe");
    }
    
}

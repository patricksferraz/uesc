/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package database;

import java.sql.CallableStatement;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import tipos.Especialidade;

/**
 *
 * @author eeeeeeeeeeeeeeeeeeee
 */
public class EspecialidadeDAO {
    
    public static void InserirEspecialidade(Especialidade esp, Connection conn) throws Exception
    {
        String query;
        boolean flag = false;
        Especialidade espExistente = consultarEspecialidadePorCodigo(esp.getCodigo(), conn);
        if(espExistente != null)
            flag = true;
        espExistente = consultarEspecialidadePorDescricao(esp.getDescricao(), conn);
        if(espExistente != null)
            flag = true;
        
        if(!flag)
        {
            query = "{CALL insert_especialidade(?, ?)}";
            CallableStatement stmt = conn.prepareCall(query);
            stmt.setInt (1, esp.getCodigo());
            stmt.setString (2, esp.getDescricao());
 
            stmt.execute();
        }
        else
            throw new Exception("Especialidade já cadastrada");
        
        
    }

    public static Especialidade consultarEspecialidadePorCodigo(int codigo, Connection conn) throws Exception
    {
        String query = "{CALL get_especialidade_by_code(?)}";
        CallableStatement stmt = conn.prepareCall(query);
        stmt.setInt(1, codigo);
        
        ResultSet rs = stmt.executeQuery();
        
        if(rs.next())
        {
            Especialidade esp = new Especialidade(rs.getString("codigo"), rs.getString("descricao"));
            rs.close();
            return esp;
        }
        return null;
    }
    
    public static Especialidade consultarEspecialidadePorDescricao(String descricao, Connection conn) throws Exception
    {
        String query = "{CALL get_especialidade_by_description(?)}";
        CallableStatement stmt = conn.prepareCall(query);
        stmt.setString(1, descricao);
        
        ResultSet rs = stmt.executeQuery();
        
        if(rs.next())
        {
            Especialidade esp = new Especialidade(rs.getString("codigo"), rs.getString("descricao"));
            rs.close();
            return esp;
        }
        return null;
    }
}

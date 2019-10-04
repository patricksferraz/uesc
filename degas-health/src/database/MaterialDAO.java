/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package database;

import java.sql.CallableStatement;
import java.sql.Connection;
import java.sql.ResultSet;
import tipos.Material;

/**
 *
 * @author eeeeeeeeeeeeeeeeeeee
 */
public class MaterialDAO {
    public static void InserirMaterial(Material mat, Connection conn) throws Exception {
        String query;
        
        Material matExistente = consultarMaterialPorCodigo(mat.getCodigo(), conn);
        
        if(matExistente == null)
        {
            query = "{CALL insert_material(?, ?, ?)}";
            CallableStatement stmt = conn.prepareCall(query);
            stmt.setInt(1, mat.getCodigo());
            stmt.setString(2, mat.getDescricao());
            stmt.setDouble(3, mat.getValor());
            
            stmt.execute();
        }
        else
            throw new Exception("Material já cadastrado");
    }

    public static Material consultarMaterialPorCodigo(int codigo, Connection conn) throws Exception
    {
        String query = "{CALL get_material_by_code(?)}";
        CallableStatement stmt = conn.prepareCall(query);
        stmt.setInt(1, codigo);
        
        ResultSet rs = stmt.executeQuery();
        
        if(rs.next())
        {
            Material mat = new Material(rs.getString("codigo"), rs.getString("descricao"), rs.getString("valor"));
            rs.close();
            return mat;
        }
        return null;
    }
    
    public static int obterIdDBMaterialPorCodigo(int codigo, Connection conn) throws Exception
    {
        String query = "{CALL get_material_by_code(?)}";
        CallableStatement stmt = conn.prepareCall(query);
        stmt.setInt(1, codigo);
        
        ResultSet rs = stmt.executeQuery();
        
        if(rs.next())
            return rs.getInt("id");
        else
            throw new Exception("Codigo de Material não Existe");
    }
}

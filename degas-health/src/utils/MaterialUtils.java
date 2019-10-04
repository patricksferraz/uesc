/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package utils;

import database.ConexaoDB;
import database.MaterialDAO;
import java.sql.Connection;
import tipos.Material;

/**
 *
 * @author eeeeeeeeeeeeeeeeeeee
 */
public class MaterialUtils {
    public static String novoMaterial(String codigo, String descricao, String valor)
    {
        try
        {
            Material eqp = new Material(codigo, descricao, valor);
            Connection conn = ConexaoDB.getConexaoMySQL();
            MaterialDAO.InserirMaterial(eqp, conn);
            conn.close();
        }
        catch (Exception ex)
        {
            return ex.getMessage();
        }
        return "Material Cadastrado com sucesso";
    }
}

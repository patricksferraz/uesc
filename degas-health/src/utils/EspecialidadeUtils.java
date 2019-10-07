/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package utils;

import database.ConexaoDB;
import database.EspecialidadeDAO;
import java.sql.Connection;
import tipos.Especialidade;
import static utils.StringUtils.isStringInteger;

/**
 *
 * @author eeeeeeeeeeeeeeeeeeee
 */
public class EspecialidadeUtils {

    public static String novaEspecialidade(String codigo, String descricao) 
    {
        try
        {
            Especialidade esp = new Especialidade(codigo, descricao);
            Connection conn = ConexaoDB.getConexaoMySQL();
            EspecialidadeDAO.InserirEspecialidade(esp, conn);
            conn.close();
        }
        catch (Exception ex)
        {
            return ex.getMessage();
        }
        return "Especialidade Registrada com sucesso";
    }

    public static String encontraEspecialidade(String pesquisa) 
    {
        try
        {
            Connection conn = ConexaoDB.getConexaoMySQL();
            Especialidade esp;
            if(isStringInteger(pesquisa))
                esp = EspecialidadeDAO.consultarEspecialidadePorCodigo(Integer.valueOf(pesquisa), conn);
            else
                esp = EspecialidadeDAO.consultarEspecialidadePorDescricao(pesquisa, conn);
            conn.close();
            return esp.toString();
        }
        catch(Exception ex)
        {
            return ex.getMessage();
        }
    }
    
}

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package utils;

import database.ConexaoDB;
import database.FuncionarioDAO;
import java.sql.Connection;
import tipos.Auxiliar;
import tipos.Enfermeiro;
import tipos.Funcionario;
import tipos.Medico;
import static utils.StringUtils.isStringInteger;

/**
 *
 * @author eeeeeeeeeeeeeeeeeeee
 */
public class FuncionarioUtils {
    
    public static String alteraFuncionario(String codigo, String campo, String novoValor, String tipoFuncionario, String tipoCodigo)
    {
        String res = null;
        try 
        {
            if(isDadosValidosFuncionario(Integer.parseInt(codigo), campo, novoValor, tipoFuncionario, tipoCodigo)) 
            {
                try
                {
                    Connection conn = ConexaoDB.getConexaoMySQL();
                    res = FuncionarioDAO.alterarFuncionarPorCodigo(Integer.parseInt(codigo), campo, novoValor, conn, tipoFuncionario, tipoCodigo);
                    conn.close();
                    return res;
                }
                catch (Exception ex)
                {
                    System.out.println("utils.FuncionarioUtils.alteraFuncionario() " + ex.getMessage());
                }
            }
        } 
        catch (Exception ex) 
        {
            return ex.getMessage();
        }
        return res;
    }
    
    public static String encontraFuncionario(String pesquisa, String tipoFuncionario, String tipoCodigo)
    {
        try 
        {
            Funcionario f;
            Connection conn = ConexaoDB.getConexaoMySQL();
            if(isStringInteger(pesquisa))
                f = FuncionarioDAO.consultarFuncionarioPorCodigo(Integer.parseInt(pesquisa), conn, tipoFuncionario);
            else
                f = FuncionarioDAO.consultarFuncionarioPorNome(pesquisa, conn, tipoFuncionario);
            conn.close();
            return f.toString();
        } 
        catch (Exception ex) 
        {
            return null;
        }
    }
    
    public static String novoMedico(String nome, String sexo, String crm, String nacionalidade, String dataNasc, String dataAdmissao, String dataFormatura)
    {
        try
        {
            Medico m = new Medico(nome, sexo, crm, nacionalidade, dataNasc, dataAdmissao, dataFormatura);
            Connection conn = ConexaoDB.getConexaoMySQL();
            FuncionarioDAO.InserirFuncionario(m, conn);
            conn.close();
        }
        catch (Exception e)
        {
            return e.getMessage();
        }
        return "Medico inserido!";
    }
    
    public static String novoEnfermeiro(String nome, String sexo, String coren, String nacionalidade, String dataNasc, String dataAdmissao, String dataFormatura)
    {
        try
        {
            Enfermeiro e = new Enfermeiro(nome, sexo, coren, nacionalidade, dataNasc, dataAdmissao, dataFormatura);
            Connection conn = ConexaoDB.getConexaoMySQL();
            FuncionarioDAO.InserirFuncionario(e, conn);
            conn.close();
        }
        catch (Exception ex)
        {
            return ex.getMessage();
        }
        return "Enfermeiro inserido!";
    }
    
    public static String novoAuxiliar(String nome, String sexo, String coren, String nacionalidade, String dataNasc, String dataAdmissao, String dataFormatura)
    {
        try
        {
            Auxiliar a = new Auxiliar(nome, sexo, coren, nacionalidade, dataNasc, dataAdmissao, dataFormatura);
            Connection conn = ConexaoDB.getConexaoMySQL();
            FuncionarioDAO.InserirFuncionario(a, conn);
            conn.close();
        }
        catch (Exception ex)
        {
            return ex.getMessage();
        }
        return "Auxiliar/Técnico inserido!";
    }
    
    
    private static boolean isDadosValidosFuncionario(int codigo, String campo, String novoValor, String tipoFuncionario, String tipoCodigo) throws Exception 
    {
        try 
        {
            if(campo.equals("DtNasc") || campo.equals("DtAdmiss") || campo.equals("DtFormatura"))
            {                                
                Connection conn = ConexaoDB.getConexaoMySQL();
                Funcionario fTest = FuncionarioDAO.consultarFuncionarioPorCodigo(codigo, conn, tipoFuncionario);

                switch (campo) 
                {
                    case "DtNasc":
                        fTest.setDataNascimento(novoValor);
                        break;
                    case "DtAdmiss":
                        fTest.setDataAdmissao(novoValor);
                        break;
                    default:
                        fTest.setDataFormatura(novoValor);
                        break;
                }
                conn.close();
            }
            return true;
        }
        catch (Exception ex) 
        {
            throw ex;
        }
    }
}

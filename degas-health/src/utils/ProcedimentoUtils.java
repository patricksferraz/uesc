/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package utils;

import database.ConexaoDB;
import database.ProcedimentoDAO;
import java.sql.Connection;
import java.util.ArrayList;
import tipos.Equipamento;
import tipos.Material;
import tipos.Procedimento;
import static utils.StringUtils.isStringInteger;

/**
 *
 * @author eeeeeeeeeeeeeeeeeeee
 */
public class ProcedimentoUtils {
    
    public static String novoProcedimento(String codigo, String Descricao, String Custo)
    {
        try
        {
            Procedimento p = new Procedimento(codigo, Descricao, Custo);
            Connection conn = ConexaoDB.getConexaoMySQL();
            ProcedimentoDAO.InserirProcedimento(p, conn);
        }
        catch (Exception ex)
        {
            return ex.getMessage();
        }
        return "Procedimento Incluido com Sucesso";
    }
    
    public static String encontraProcedimento(String pesquisa)
    {
        try 
        {
            Procedimento p;
            Connection conn = ConexaoDB.getConexaoMySQL();
            if(isStringInteger(pesquisa))
                p = ProcedimentoDAO.consultarProcedimento("codigo", pesquisa, conn);
            else
                p = ProcedimentoDAO.consultarProcedimento("descricao", pesquisa, conn);
            
            if(p == null)
                return "Procedimento não cadastrado";
            
            return p.toString();
        } 
        catch (Exception ex) 
        {
            return null;
        }
    }
    
    public static String alteraProcedimento(String codigo, String campo, String novoValor)
    {
        String res = null;
        try 
        {
            if(isDadosValidosProcedimento(campo, novoValor)) 
            {
                try
                {
                    Connection conn = ConexaoDB.getConexaoMySQL();
                    res = ProcedimentoDAO.alterarProcedimentoPorCodigo(Integer.parseInt(codigo), campo, novoValor, conn);
                    return res;
                }
                catch (Exception ex)
                {
                    System.out.println("facade.Facade.alteraAuxiliar() " + ex.getMessage());
                }
            }
        } 
        catch (Exception ex) 
        {
            return ex.getMessage();
        }
        return res;
    }
    
    public static String materialProcedimento(String codigoProcedimento, String codigoMaterial) 
    {
        try
        {
            Connection conn = ConexaoDB.getConexaoMySQL();
            ProcedimentoDAO.inserirMaterialEmProcedimento(codigoProcedimento, codigoMaterial, conn);
            conn.close();
        }
        catch (Exception ex)
        {
            return ex.getMessage();
        }
        
        return "Material Incluido com sucesso no procedimento";
    }
    
    public static String equipamentoProcedimento(String codigoProcedimento, String codigoEquipamento) 
    {
        try
        {
            Connection conn = ConexaoDB.getConexaoMySQL();
            ProcedimentoDAO.inserirEquipamentoEmProcedimento(codigoProcedimento, codigoEquipamento, conn);
            conn.close();
        }
        catch (Exception ex)
        {
            return ex.getMessage();
        }
        
        return "Equipamento Incluido com sucesso no procedimento";
    }
    
    private static boolean isDadosValidosProcedimento(String campo, String valor) throws Exception 
    {
        try 
        {
            Procedimento pTest = new Procedimento();
            
            switch(campo)
            {
                case "Descricao":
                    pTest.setDescricao(valor);
                    break;
                case "Valor":
                    pTest.setValor(valor);
                    break;
                default:
                    throw new Exception("Campo não alteravel");
            }
            return true;
        }
        catch (Exception ex) 
        {
            throw ex;
        }
    }

    public static String listMateriaisProcedimento(String codigoProcedimento) 
    {
        try
        {
            ArrayList<Material> mats = ProcedimentoDAO.consultarMateriaisEmProcedimento(Integer.valueOf(codigoProcedimento), ConexaoDB.getConexaoMySQL());
            if(mats.isEmpty())
                return "Procedimento não possui Materiais Cadastrados";
            String res = "";
            res = mats.stream().map((m) -> m.getDescricao() + "%").reduce(res, String::concat);
            res = res.substring(0, res.length() - 1);
            return res;
        }
        catch (Exception ex)
        {
            return ex.getMessage();
        }
    }
    
    public static String listEquipamentosProcedimento(String codigoProcedimento) 
    {
        try
        {
            ArrayList<Equipamento> eqps = ProcedimentoDAO.consultarEquipamentosEmProcedimento(Integer.valueOf(codigoProcedimento), ConexaoDB.getConexaoMySQL());
            if(eqps.isEmpty())
                return "Procedimento não possui Equipamentos Cadastrados";
            String res = "";
            res = eqps.stream().map((m) -> m.getDescricao() + "%").reduce(res, String::concat);
            res = res.substring(0, res.length() - 1);
            return res;
        }
        catch (Exception ex)
        {
            return ex.getMessage();
        }
    }
}

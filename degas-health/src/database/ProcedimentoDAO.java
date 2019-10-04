/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package database;
import java.sql.CallableStatement;
import java.util.ArrayList;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import tipos.Equipamento;
import tipos.Material;
import tipos.Procedimento;

/**
 *
 * @author eeeeeeeeeeeeeeeeeeee
 */
public class ProcedimentoDAO {
    public static void InserirProcedimento(Procedimento p, Connection conn) throws Exception
    {   
        if(consultarProcedimento("codigo", String.valueOf(p.getCodigo()), conn) != null)
            throw new Exception("Código de Procedimento Ja Cadastrado");
        else if(consultarProcedimento("descricao", p.getDescricao(), conn) != null)
            throw new Exception("Descrição de Procedimento Ja Cadastrado");
        else
        {
            String query = "{CALL insert_procedimento(?, ?, ?)}";
            CallableStatement stmt = conn.prepareCall(query);
            stmt.setInt (1, p.getCodigo());
            stmt.setString (2, p.getDescricao());
            stmt.setDouble(3, p.getValor());

            stmt.execute();
        }
    }
    
    public static Procedimento consultarProcedimento(String campo, String valor, Connection conn) throws Exception
    {
        String query;
        if(campo.equals("codigo"))
            query = "{CALL get_procedimento_by_code(?)}";
        else
            query = "{CALL get_procedimento_by_description(?)}";
        CallableStatement stmt = conn.prepareCall(query);
        stmt.setString(1, valor);
        
        ResultSet rs = stmt.executeQuery();
        
        if(rs.next())
            return new Procedimento(rs.getString("codigo"), rs.getString("descricao"), rs.getString("valor").replace(".", ","));
        
        return null;
    }
    
    public static String alterarProcedimentoPorCodigo(int codigo, String campo, String novoValor, Connection conn) throws Exception
    {
        if(campo.equals("Descricao") && consultarProcedimento("descricao", campo, conn) != null)
            throw new Exception("Descrição de Procedimento Ja Cadastrado");
        
        String query = "UPDATE Procedimento SET " + campo + " = ? WHERE codigo = ?";
        PreparedStatement preparedStmt = conn.prepareStatement(query);
        preparedStmt.setString(1, novoValor);
        preparedStmt.setInt(2, codigo);
        preparedStmt.execute();
        return "Procedimento alterado com sucesso";
    }
    
    public static int obterIdDBProcedimentoPorCodigo(int codigo, Connection conn) throws Exception
    {
        String query = "{CALL get_procedimento_by_code(?)}";
        CallableStatement stmt = conn.prepareCall(query);
        stmt.setInt(1, codigo);
        
        ResultSet rs = stmt.executeQuery();
        
        if(rs.next())
            return rs.getInt("id");
        else
            throw new Exception("Codigo de Procedimento não Existe");
    }

    public static void inserirMaterialEmProcedimento(String codigoProcedimento, String codigoMaterial, Connection conn) throws Exception
    {
        String query;
        Material matExistente = MaterialDAO.consultarMaterialPorCodigo(Integer.valueOf(codigoMaterial), conn);
        Procedimento pExistente = consultarProcedimento("codigo", codigoProcedimento, conn);
        ArrayList<Material> matsExistentesEmP = consultarMateriaisEmProcedimento(Integer.valueOf(codigoProcedimento), conn);
        
        if(matExistente == null)
            throw new Exception("Erro: Material não existe");
        else if(pExistente == null)
            throw new Exception("Erro: Procedimento não existente");
        
        for(Material mat: matsExistentesEmP)
            if(mat.getCodigo() == Integer.valueOf(codigoMaterial))
                throw new Exception("Erro: Material já foi adicionado");
        
        query = "{CALL insert_materialProcedimento(?, ?)}";
        CallableStatement stmt = conn.prepareCall(query);
        stmt.setInt(1, MaterialDAO.obterIdDBMaterialPorCodigo(matExistente.getCodigo(), conn));
        stmt.setInt(2, obterIdDBProcedimentoPorCodigo(pExistente.getCodigo(), conn));

        stmt.execute();
            
    }
    
    public static ArrayList<Material> consultarMateriaisEmProcedimento(int codigo, Connection conn) throws Exception
    {
        ArrayList<Material> materiais = new ArrayList();
        
        String query = "{CALL get_materialProcedimento_by_codigoProcedimento(?)}";
        CallableStatement stmt = conn.prepareCall(query);
        stmt.setInt(1, codigo);
        
        ResultSet rs = stmt.executeQuery();
        
        while(rs.next())
            materiais.add(new Material(rs.getString("codigo"), rs.getString("descricao"), rs.getString("valor")));
        
        return materiais;
    }
    
    public static void inserirEquipamentoEmProcedimento(String codigoProcedimento, String codigoEquipamento, Connection conn) throws Exception
    {
        String query;
        Equipamento eqExistente = EquipamentoDAO.consultarEquipamentoPorCodigo(Integer.valueOf(codigoEquipamento), conn);
        Procedimento pExistente = consultarProcedimento("codigo", codigoProcedimento, conn);
        ArrayList<Equipamento> eqExistentesEmP = consultarEquipamentosEmProcedimento(Integer.valueOf(codigoProcedimento), conn);
        
        if(eqExistente == null)
            throw new Exception("Erro: Equipamento não existe");
        else if(pExistente == null)
            throw new Exception("Erro: Procedimento não existente");
        
        for(Equipamento eq: eqExistentesEmP)
            if(eq.getCodigo() == Integer.valueOf(codigoEquipamento))
                throw new Exception("Erro: Material já foi adicionado");
        
        query = "{CALL insert_equipamentoProcedimento(?, ?)}";
        CallableStatement stmt = conn.prepareCall(query);
        stmt.setInt(1, EquipamentoDAO.obterIdDBEquipamentoPorCodigo(eqExistente.getCodigo(), conn));
        stmt.setInt(2, obterIdDBProcedimentoPorCodigo(pExistente.getCodigo(), conn));

        stmt.execute();
            
    }
    
    public static ArrayList<Equipamento> consultarEquipamentosEmProcedimento(int codigo, Connection conn) throws Exception
    {
        ArrayList<Equipamento> equipamentos = new ArrayList();
        
        String query = "{CALL get_equipamentoProcedimento_by_codigoProcedimento(?)}";
        CallableStatement stmt = conn.prepareCall(query);
        stmt.setInt(1, codigo);
        
        ResultSet rs = stmt.executeQuery();
        
        while(rs.next())
            equipamentos.add(new Equipamento(rs.getString("codigo"), rs.getString("descricao"), rs.getString("valor")));
        
        return equipamentos;
    }
}

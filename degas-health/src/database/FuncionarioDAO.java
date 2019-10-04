/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package database;

import java.sql.CallableStatement;
import tipos.*;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import static utils.DateUtils.createDateFromString;

/**
 *
 * @author eeeeeeeeeeeeeeeeeeee
 */
public class FuncionarioDAO {
    
    public static void InserirFuncionario(Funcionario f, Connection conn) throws Exception
    {
        String query, tipoCodigo;
        Funcionario fExistente;
        if(f instanceof Medico)
        {
            tipoCodigo = "CRM";
            fExistente = consultarFuncionarioPorCodigo(f.getCodigo(), conn, "Medico");
        }
        else if(f instanceof Enfermeiro)
        {
            tipoCodigo = "COREN";
            fExistente = consultarFuncionarioPorCodigo(f.getCodigo(), conn, "Enfermeiro");
        }
        else
        {
            tipoCodigo = "COREN";
            fExistente = consultarFuncionarioPorCodigo(f.getCodigo(), conn, "Auxiliar");
        }
        if(fExistente == null)
        {
            if(f instanceof Medico)
                query = "{CALL insert_medico(?, ?, ?, ?, ?, ?, ?)}";
            else if(f instanceof Enfermeiro)
                query = "{CALL insert_enfermeiro(?, ?, ?, ?, ?, ?, ?)}";
            else
                query = "{CALL insert_auxiliar(?, ?, ?, ?, ?, ?, ?)}";
            CallableStatement stmt = conn.prepareCall(query);
            stmt.setString (1, f.getNome());
            stmt.setString (2, String.valueOf(f.getSexo()));
            stmt.setInt    (3, f.getCodigo());
            stmt.setString (4, f.getNacionalidade());
            stmt.setDate   (5, new java.sql.Date(f.getDataNascimento().getTime()));
            stmt.setDate   (6, new java.sql.Date(f.getDataAdmissao().getTime()));
            stmt.setDate   (7, new java.sql.Date(f.getDataFormatura().getTime()));
 
            stmt.execute();
        }
        else
            throw new Exception("ERRO! " + tipoCodigo.toUpperCase() + " Já existente!");
        
        
    }
    
    public static Funcionario consultarFuncionarioPorCodigo(int codigo, Connection conn, String tipoFuncionario) throws Exception
    {
        String query;

//        query = "SELECT id, nome," + tipoCodigo + ", sexo, nacionalidade, DATE_FORMAT(dtNasc,'%d/%m/%Y') AS dataNasc, DATE_FORMAT(dtAdmiss,'%d/%m/%Y') AS dataAdmiss, DATE_FORMAT(dtFormatura,'%d/%m/%Y') AS dataFormatura FROM " + tipoFuncionario + " WHERE " + tipoCodigo + " = ?";
        if(tipoFuncionario.equals("Medico"))
            query = "{CALL get_medico_by_code(?)}";
        else if(tipoFuncionario.equals("Enfermeiro"))
            query = "{CALL get_enfermeiro_by_code(?)}";
        else
            query = "{CALL get_auxiliar_by_code(?)}";
    
        CallableStatement stmt = conn.prepareCall(query);
        stmt.setInt(1, codigo);
        
        ResultSet rs = stmt.executeQuery();
        
        if(rs.next())
        {
            switch(tipoFuncionario)
            {
                case "Medico":
                    Medico m = new Medico(rs.getString("nome"), rs.getString("sexo"), rs.getString("crm"), rs.getString("nacionalidade"), rs.getString("dataNasc"), rs.getString("dataAdmiss"), rs.getString("dataFormatura"));
                    rs.close();
                    return m;
                case "Enfermeiro":
                    Enfermeiro e = new Enfermeiro(rs.getString("nome"), rs.getString("sexo"), rs.getString("coren"), rs.getString("nacionalidade"), rs.getString("dataNasc"), rs.getString("dataAdmiss"), rs.getString("dataFormatura"));
                    rs.close();
                    return e;
                case "Auxiliar":
                    Auxiliar a = new Auxiliar(rs.getString("nome"), rs.getString("sexo"), rs.getString("coren"), rs.getString("nacionalidade"), rs.getString("dataNasc"), rs.getString("dataAdmiss"), rs.getString("dataFormatura"));
                    rs.close();
                    return a;
                default:
                    break;
            }
        }
        
        return null;
    }
    
    public static Funcionario consultarFuncionarioPorNome(String nome, Connection conn, String tipoFuncionario) throws Exception
    {
        String query;
        if(tipoFuncionario.equals("Medico"))
            query = "{CALL get_medico_by_name(?)}";
        else if(tipoFuncionario.equals("Enfermeiro"))
            query = "{CALL get_enfermeiro_by_name(?)}";
        else
            query = "{CALL get_auxiliar_by_name(?)}";
        
        CallableStatement stmt = conn.prepareCall(query);
        stmt.setString(1, nome);
        
        ResultSet rs = stmt.executeQuery();
        
        if(rs.next())
        {
            switch(tipoFuncionario)
            {
                case "Medico":
                    Medico m = new Medico(rs.getString("nome"), rs.getString("sexo"), rs.getString("crm"), rs.getString("nacionalidade"), rs.getString("dataNasc"), rs.getString("dataAdmiss"), rs.getString("dataFormatura"));
                    rs.close();
                    return m;
                case "Enfermeiro":
                    Enfermeiro e = new Enfermeiro(rs.getString("nome"), rs.getString("sexo"), rs.getString("coren"), rs.getString("nacionalidade"), rs.getString("dataNasc"), rs.getString("dataAdmiss"), rs.getString("dataFormatura"));
                    rs.close();
                    return e;
                case "Auxiliar":
                    Auxiliar a = new Auxiliar(rs.getString("nome"), rs.getString("sexo"), rs.getString("coren"), rs.getString("nacionalidade"), rs.getString("dataNasc"), rs.getString("dataAdmiss"), rs.getString("dataFormatura"));
                    rs.close();
                    return a;
                default:
                    break;
            }
        }
        
        return null;
    }
    
    
    public static String alterarFuncionarPorCodigo(int codigo, String campo, String valor, Connection conn, String tipoFuncionario, String tipoCodigo) throws Exception
    {
        String query;
        
        query = "UPDATE " + tipoFuncionario + " SET " + campo + " = ?  WHERE " + tipoCodigo + " = ?";
        PreparedStatement preparedStmt = conn.prepareStatement(query);
        if(campo.equals("DtNasc") || campo.equals("DtAdmiss") || campo.equals("DtFormatura"))
            preparedStmt.setDate(1, new java.sql.Date(createDateFromString(valor).getTime()));
        else
            preparedStmt.setString(1, valor);
        preparedStmt.setInt(2, codigo);
        preparedStmt.execute();
        return "Alteracao executada com sucesso!";
    }
}

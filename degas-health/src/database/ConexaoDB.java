/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package database;

/**
 *
 * @author eeeeeeeeeeeeeeeeeeee
 */
 
//Classes necessárias para uso de Banco de dados //

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

//Início da classe de conexão//
 
public class ConexaoDB {
 
    private static String status = "Não conectou...";
 
    public static Connection getConexaoMySQL() 
    {
        Connection connection;          //atributo do tipo Connection
        try {

        // Carregando o JDBC Driver padrão

        String driverName = "com.mysql.cj.jdbc.Driver";                        

        Class.forName(driverName);
        
        // Configurando a nossa conexão com um banco de dados//

        String serverName = "localhost";    //caminho do servidor do BD

        String mydatabase ="hospital";        //nome do seu banco de dados

        String url = "jdbc:mysql://localhost:3306/hospital?useUnicode=true&useJDBCCompliantTimezoneShift=true&useLegacyDatetimeCode=false&serverTimezone=UTC";

        String username = "root";        //nome de um usuário de seu BD      

        String password = "";      //sua senha de acesso

        connection = DriverManager.getConnection(url, username, password);

        //Testa sua conexão//  

        if (connection != null) {

            status = ("STATUS--->Conectado com sucesso!");

        } else {

            status = ("STATUS--->Não foi possivel realizar conexão");

        }
        return connection;
        } 
        catch (ClassNotFoundException e) 
        {  //Driver não encontrado
                System.out.println("O driver expecificado nao foi encontrado.");
                return null;
        } 
        catch (SQLException e) 
        {
            //Não conseguindo se conectar ao banco
            System.out.println("Nao foi possivel conectar ao Banco de Dados.");
            return null;
        }
    }

    //Método que retorna o status da sua conexão//
    public static String statusConection() 
    {
        return status;
    }

    //Método que fecha sua conexão//
    public static boolean FecharConexao() 
    {
        try 
        {
            ConexaoDB.getConexaoMySQL().close();
            return true;
        } 
        catch (SQLException e) 
        {
            return false;
        }
    }
    
    //Método que reinicia sua conexão//

    public static Connection ReiniciarConexao() 
    {
        FecharConexao();
        return ConexaoDB.getConexaoMySQL();
    }
}
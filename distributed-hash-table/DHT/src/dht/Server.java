/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dht;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.net.MalformedURLException;
import java.net.ServerSocket;
import java.net.Socket;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.LinkedList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author ferraz
 */
public class Server extends UnicastRemoteObject implements Service, Runnable{
    //lista de IP dos nós
    //hash
    //idNo
    private String ip;
    private int hashId;
    private TabelaHash tabela;
    private int intervaloInicio;
    private int intervaloFim;
    private int tamTabela = 200;
    private String noVizinho;
    
    public Server(String ip) throws RemoteException
    {
        super();
        this.ip = ip;
    }
    
    @Override
    public void run() {
        
    }

    @Override
    public String buscarArquivo(String nArquivo) throws RemoteException {
        String arquivo = null;
        int codigo = TabelaHash.calculaHash(nArquivo, this.tamTabela);
        
        if (codigo >= this.intervaloInicio && codigo <= intervaloFim)
            if ((arquivo = this.tabela.devolveRegistro(nArquivo)) == null)
                arquivo = "Arquivo nao existe";
        else
        {
            try {
                Service service = (Service) Naming.lookup(noVizinho);
                arquivo = service.buscarArquivo(nArquivo);
                //Socket socket = new Socket("127.0.0.1", 12345);
                //Cliente c = new Cliente();
                //Thread t = new Thread(c);
                //t.start();
            }
            catch (NotBoundException | MalformedURLException ex) {
                Logger.getLogger(Server.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
        
        return arquivo;
    }

    @Override
    public boolean armazenarArquivo(String nArquivo) throws RemoteException {
        boolean validacao = false;
        int codigo = TabelaHash.calculaHash(nArquivo, this.tamTabela);
        
        if (codigo >= this.intervaloInicio && codigo <= intervaloFim)
        {
            this.tabela.adiciona(nArquivo);
            validacao = true;
        }
        else
        {
            try {
                Service service = (Service) Naming.lookup(noVizinho);
                validacao = service.armazenarArquivo(nArquivo);
                //Socket socket = new Socket("127.0.0.1", 12345);
                //Cliente c = new Cliente();
                //Thread t = new Thread(c);
                //t.start();
            }
            catch (NotBoundException | MalformedURLException ex) {
                Logger.getLogger(Server.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
        
        return validacao;
    }

    public int getHashId() {
        return hashId;
    }
    
    public boolean iniciarDHT()
    {
        this.tabela = new TabelaHash(this.tamTabela);
        this.hashId = TabelaHash.calculaHash(ip, this.tamTabela);
        
        return true; // ver
    }
    
    public boolean participarDHT(String enderecoNo)
    {
        try {
            Socket socket = new Socket(enderecoNo, 12345);
            ObjectInputStream entrada = new ObjectInputStream(socket.getInputStream());
            this.tabela = (TabelaHash)entrada.readObject();
            entrada.close();
            
        } catch (IOException | ClassNotFoundException ex) {
            System.out.println("Erro: " + ex.getMessage());
        }
        
        return false; // ver
    }
    
    // Falta implementar
    public boolean aceitarInclusao()
    {
        return false;
    }
    
    // Falta implementar a inicialização do DHT e inserir-se em uma DHT
    public static void main(String[] args)
    {
        try {
            String ip = "127.0.0.1";
            String porta = "1090";
            Service server = new Server(ip);
            String local = "rmi://" + ip + ":" + porta + "/dht";
            Naming.rebind(local, server);
            
            //Cria um socket na porta 12345
            ServerSocket servidor = new ServerSocket (12345);
            System.out.println("Porta 12345 aberta!");

            System.out.println("Servidor ligado");

            do {       
                // Menu para escolher iniciar ou inserir-se em uma DHT
            } while (true);
            
            
            
//            while (true) {
//              Socket cliente = servidor.accept();
////              Server tratamento = new Server();
////              Thread t = new Thread(tratamento);
//              //t.start();
//            }
            
            //Socket socket = new Socket("127.0.0.1", 12345);

            //Cliente c = new Cliente();
            //Thread t = new Thread(c);
            //t.start();
            
        } catch (RemoteException | MalformedURLException ex) {
            System.out.println("Erro: " + ex.getMessage());
        } catch (IOException ex) {
            Logger.getLogger(Server.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}

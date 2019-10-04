/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dht;

import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;

/**
 *
 * @author ferraz
 */
public class Cliente implements Runnable{

    @Override
    public void run()
    {
        System.out.println("Fim do cliente!");
    }
    
    public static void main(String args[])
    {
        String teste = "garganta profunda";
        try {
            String local = "//127.0.0.1:1090/dht";
            Service service = (Service) Naming.lookup(local);
            String n = service.buscarArquivo(teste);
            System.out.println(n);
            //Thread t = new Thread(c);
            //t.start();
        } catch (NotBoundException | MalformedURLException | RemoteException ex) {
            System.out.println("Erro: " + ex.getMessage());
        }
    }
}

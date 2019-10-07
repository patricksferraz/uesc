/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dht;

import java.rmi.Remote;
import java.rmi.RemoteException;

/**
 *
 * @author ferraz
 */
public interface Service extends Remote {
    String buscarArquivo(String arquivo) throws RemoteException;
    boolean armazenarArquivo(String arquivo) throws RemoteException;;
}

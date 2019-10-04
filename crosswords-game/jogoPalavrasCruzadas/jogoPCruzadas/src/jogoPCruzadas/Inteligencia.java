/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package jogoPCruzadas;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.RandomAccessFile;
import javax.swing.JOptionPane;
import sun.security.pkcs11.wrapper.Constants;

/**
 * Classe onde mantem a "conexão" aberta com JVirtual para pesquisa dos "chutes"
 * 
 * @author Patrick
 */
public class Inteligencia {
    
    //Atributo
    private RandomAccessFile fluxoIO;//Fluxo de IO com arquivo da memoria("chutes")
    
    
    //Construtor
    public Inteligencia() {
        
        //Tenta abrir o fluxo com a memoria e o mantem aberto
        try {            
            fluxoIO = new RandomAccessFile("memoria.txt", "rw");            
        } catch (FileNotFoundException e) {
            JOptionPane.showMessageDialog(null, e, "ERRO construtor Inteligencia", JOptionPane.ERROR_MESSAGE);
        }        
    }
    
    
    /**
     * Busca na memoria se a String já foi "dada"
     * 
     * @param palavra
     * @return true se já foi dita, false se ainda não foi dada
     */
    public boolean buscarMemoria(String palavra) {

        try {            
            //Ler a primeira linha
            String s = fluxoIO.readLine();
            
            //Inicio do if
            if(s != null)                
                //Inicio do while
                while (s != null) {
                    
                    //Confirma se a palavra é igual e retornar true(existe) em caso afirmativo
                    if (s.equals(palavra)) {
                        fluxoIO.seek(0);//move o cursor para inicio do arquivo(futuras releituras)
                        return true;
                    }
                    
                    //Pega a prox linha se não achou a palavra
                    s = fluxoIO.readLine();
                }
                //Fim do while
            //Fim do if
            
            //Caso não ache a palavra, move o cursor para incio do arquivo
            fluxoIO.seek(0);

        } catch (IOException e) {
            JOptionPane.showMessageDialog(null, e, "ERRO buscarMemoria Inteligencia", JOptionPane.ERROR_MESSAGE);
        }
        
        return false;//retorna que a palavra não existe no arquivo        
    }
    
    
    /**
     * Grava a String na memoria(arquivo) para não repeti-la
     * 
     * @param palavra String a ser buscada
     */
    public void gravarMemoria(String palavra) {

        try {            
            //Move o cursor para final do arquivo e grava a palavra
            fluxoIO.seek(fluxoIO.length());
            fluxoIO.writeBytes(palavra);
            fluxoIO.writeBytes(Constants.NEWLINE);
            //Move o cursor para o inicio
            fluxoIO.seek(0);

        } catch (IOException e) {
            JOptionPane.showMessageDialog(null, e, "ERRO gravarMemoria Inteligencia", JOptionPane.ERROR_MESSAGE);
        }        
    }
    
    
    /**
     * Finaliza a inteligencia apagando a memoria
     * 
     * Este metodo será "chamado" pelo metodo fimJogadorVirtual
     * quando estiver encerrando o jogo
     */
    public void fimInteligencia() {
        
        //verifica se o fluxo existe
        if(fluxoIO != null)            
            try {                
                fluxoIO.setLength(0);//apaga tudo no arquivo
                fluxoIO.close();//fecha o fluxo

            } catch (IOException e) {
                JOptionPane.showMessageDialog(null, e, "ERRO deleteMemoria Inteligencia", JOptionPane.ERROR_MESSAGE);
            }       
    }
}

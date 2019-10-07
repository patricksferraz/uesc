/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package jogoPCruzadas;

import java.io.File;
import java.io.IOException;
import java.io.RandomAccessFile;
import javax.swing.JOptionPane;

/**
 * Classe que ler as instruções no ARQUIVO para exibir na interface
 * 
 * @author Patrick
 */
public class LeitorInstrucoes {
    
    //Atributos
    private final static File ARQUIVO = new File("instrucoes.txt");;
    private static RandomAccessFile fluxoIO;//declaração do fluxo de IO
        
    
    /**
     * Metodo para leitura das instruções passo a passo
     * 
     * @return retorno de uma String com as instruções. Linhas separadas por ";",
     * senão retorna null
     */
    public static String getInstrucoes() {
        
        try{            
            //Abertura do fluxo com ARQUIVO para leitura
            fluxoIO = new RandomAccessFile(ARQUIVO, "rw");
            
            //Leitura da instrução na primeira linha
            String linha = fluxoIO.readLine();
            
            //Inicio do if
            //Verifica se existem instruções
            if(linha != null){
                
                //Adiciona a primeira linha na string
                String instrucoes = linha+";";
                
                //Sucessivas adições até o final do ARQUIVO
                while(linha != null){
                    
                    linha = fluxoIO.readLine();
                    instrucoes += linha+";";                
                }
                
                return instrucoes;//retorna todas as intruções cocatenadas            
            }
            //Fim do if
            
        } catch (IOException e) {
            JOptionPane.showMessageDialog(null, e, "ERRO getInstrucoes Instrucoes", JOptionPane.ERROR_MESSAGE);
        }
        
        return null;//Caso não exista linha, retorna null        
    }
}

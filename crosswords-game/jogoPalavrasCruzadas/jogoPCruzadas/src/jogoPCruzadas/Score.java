/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package jogoPCruzadas;

import java.io.File;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import javax.swing.JOptionPane;
import sun.security.pkcs11.wrapper.Constants;

/**
 * Classe que armazena ou ler os recordes para exibir na interface
 * 
 * @author Patrick
 */
public class Score {
    
    //Atributos
    private final static File ARQUIVO = new File("score.txt");;
    private static RandomAccessFile fluxoIO;//declaração do fluxo de IO
    
    
    /**
     * Metodo para leitura dos recordes no ARQUIVO e os retorna já ordenados
     * 
     * @return retorno de uma String com os recordes separados por ";", senão
     * existir scores, retona ""
     */
    public static String getScore() {
        
        try{            
            //Abertura do fluxo com ARQUIVO para leitura
            fluxoIO = new RandomAccessFile(ARQUIVO, "rw");
            List<Jogador> scoreJogadores = new ArrayList<>();//Array para coleção de scores com a classe JogadorReal
            String[] linha;//Array utilizado para fazer split a cada leitura de score/linha
            
            //Leitura do score da primeira linha
            String score = fluxoIO.readLine();
            
            //Inicio do if
            //Verifica se existem scores
            if(score != null){
                
                while(score != null){
                    
                    //Split dos scores/linhas para adicionar no ArrayList
                    linha = score.split("\t");
                    scoreJogadores.add(new Jogador(linha[0], Integer.parseInt(linha[1]), linha[2], linha[3]+"\t"+linha[4]));
                    //Pega a prox linha
                    score = fluxoIO.readLine();                
                }
                
                //Ordena o array de JogadorReal com implements comparable, presente na classe
                Collections.sort(scoreJogadores);
                
                //Inicio do for
                //laço para leitura dos scores no array
                for(Jogador j : scoreJogadores)                    
                    //Na primeira tentativa, score = null, ou seja, ele inicializa o score com o primeiro valor
                    if(score == null)
                        score = j.getNome()+"\t"+j.getScore()+"\t"+j.getDificuldade()+"\t"+j.getData()+";";
                    //Soma consecutivas dos arrays com um limitador ";"
                    else
                        score += j.getNome()+"\t"+j.getScore()+"\t"+j.getDificuldade()+"\t"+j.getData()+";";                
                //Fim do for
                
                return score;//retorna todos os scores cocatenados            
            }
            //Fim do if
            
        } catch (IOException e) {
            JOptionPane.showMessageDialog(null, e, "ERRO getScore Score", JOptionPane.ERROR_MESSAGE);
        }
        
        return "";//Caso não exista score, retorna ""        
    }
    
    
    /**
     * Metodo utilizado para gravar o score no ARQUIVO, metodo chamado na classe
     * fimJogadorReal para guardar o recorde
     * 
     * @param gravaScore Instancia de JogadorReal passada por parametro para gravação
     */
    public static void setScore(Jogador gravaScore){
        
        try{            
            //Abre fluxo com ARQUIVO para gravação
            fluxoIO = new RandomAccessFile(ARQUIVO, "rw");
            //posiciona o cursor no final do ARQUIVO e grava os dados
            fluxoIO.seek(fluxoIO.length());
            fluxoIO.writeBytes(gravaScore.getNome()+"\t"+gravaScore.getScore()+"\t"+gravaScore.getDificuldade()+"\t"+gravaScore.getData());
            fluxoIO.writeBytes(Constants.NEWLINE);//Adiciona uma nova linha no ARQUIVO
            //fecha o fluxo
            fluxoIO.close();

        }catch(IOException e){
            JOptionPane.showMessageDialog(null, e, "ERRO setScore Score", JOptionPane.ERROR_MESSAGE);
        }        
    }
    
    
    //Metodo utilizado para apagar todos recordes
    public static void deleteScore(){
        
        try{            
            //Abre o fluxo com o ARQUIVO e apaga todo os dados
            fluxoIO = new RandomAccessFile(ARQUIVO, "rw");
            fluxoIO.setLength(0);
            
        } catch (IOException e) {
            JOptionPane.showMessageDialog(null, e, "ERRO deleteScore Score", JOptionPane.ERROR_MESSAGE);
        }        
    }
}

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

/**
 * Classe procura no banco de dados (arquivo dicionario), a quantidade de
 * palavras de acordo com a dificuldade
 * 
 * @author Patrick
 */
public class BDPCruzadas {
    
    //Atributos
    private final List sorteio;//ArrayList para add todas palavra para o sorteio
    private final File arquivo;
    private final String dificuldade;
    
    
    //Construtor
    public BDPCruzadas(String dificuldade){
        
        //Abre "conexão" com arquivo e inicializa dificuldade e sorteio
        arquivo = new File("dicionarioPalCruz.txt");
        this.dificuldade = dificuldade;
        sorteio = sorteioPCruzadas();        
    }
    
    
    /**
     * Adiciona as palavras em um array, embaralha e sorteia, afim de evitar
     * que as cruzadinhas sejam diferentes a cada inicio de partida
     * 
     * @return Array com as palavras embaralhadas, senão retorna o array vazio
     */
    public final List sorteioPCruzadas(){
        
        //Array que será add as palavras
        List palavras = new ArrayList();
        
        try{            
            //Abre fluxo com o arquivo
            RandomAccessFile fluxo = new RandomAccessFile(arquivo, "rw");
            
            //Linha de leitura do arquivo
            String linha = fluxo.readLine();
            
            //Verifica se o arquivo está vazio
            if(linha != null)                
                //Adiciona todas palavras no array em maiusculo
                while(linha != null){
                    palavras.add(linha.toUpperCase());
                    linha = fluxo.readLine();
                }
            
            //Embaralha o array
            Collections.shuffle(palavras);
            
            return palavras;//Retorna o array embaralhado
        
        }catch (IOException e) {
            JOptionPane.showMessageDialog(null, e, "ERRO getScore Score", JOptionPane.ERROR_MESSAGE);
        }
        
        return palavras;
    }
    
    
    /**
     * Metodo busca no array uma dica e sua respectiva palavra com tamanho
     * maior que 5 para o minimo de cruzadinhas permitidas no jogo
     * 
     * @return Retorna a palavra da vertical para construção, senão retorna
     * String[] vazia
     */
    public String[] getPalavraVert(){
        
        //Palavra que será retornada com sua respectiva dica
        String[] palavra = new String[2];
        
        //Inicio do for
        //Laço "pula" as palavras no array, até encontrar a exigida
        for(int i = 0; i < sorteio.size(); i++){
            
            //Separa a palavra de sua dica
            palavra = ((String)sorteio.get(i)).split(":");
            
            if(dificuldade.equals("facil") || dificuldade.equals("medio")){
                
                //Verifica se a palavra serve para vertical e a retorna com sua dica
                if(palavra[1].length() == 7){
                    sorteio.remove(i);//Remove a selecionada do array para não repeti-la
                    return palavra;
                }
                
            }else{
            
                //Verifica se a palavra serve para vertical e a retorna com sua dica
                if(palavra[1].length() >= 9){
                    sorteio.remove(i);//Remove a selecionada do array para não repeti-la
                    return palavra;
                }
            }
        }
        //Fim do for
        
        return palavra;        
    }
    
    
    /**
     * Metodo busca no array uma dica e sua respectiva palavra para horizontal
     * que possua a letra passada por parametro
     * 
     * @param letra Busca palavras que possuam essa letra
     * @return retorna a dica e sua palavra, senão retorna String[] vazia
     */
    public String[] getPalavraHori(char letra){
        
        //Palavra que será retornada, caso encontrada
        String[] palavra = new String[2];
        
        //Inicio do for
        //Laço "pula" as palavras no array até encontrar a exigida
        for(int i = 0; i < sorteio.size(); i++){
            
            //Separa a palavra de sua dica
            palavra = ((String)sorteio.get(i)).split(":");
            
            //Verifica se a palavra serve para cruzar na horizontal e a retorna com sua dica
            if(palavra[1].indexOf(letra) != -1){            
                sorteio.remove(i);//Remove a selecionada do array para não repeti-la
                return palavra;
            }            
        }
        //Fim do for
        
        return palavra;
    }
}

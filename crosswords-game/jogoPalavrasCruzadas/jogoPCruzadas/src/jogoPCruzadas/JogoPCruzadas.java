/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package jogoPCruzadas;

import java.util.ArrayList;
import java.util.List;

/**
 * Classe para criação do jogo PCruzadas
 * 
 * @author Patrick
 */
public class JogoPCruzadas {
    
    //Atributos
    private final BDPCruzadas bancoDDados;
    private final List dicas, palavras;
    protected static final int MAX_LINHA = 20, MAX_COLUNA = 20;//Tamanho maximo da matriz de cruzadas que será exibida
    

    //Construtor
    public JogoPCruzadas(String dificuldade) {
        
        bancoDDados = new BDPCruzadas(dificuldade);//Referencia bancoDDados para recuperar as cruzadinhas do novo jogo
        dicas = new ArrayList();//Array list que será adicionada todas as dicas
        palavras = new ArrayList();//Array list que será adicionada todas as palavras das respectivas dicas    
    }
    
    
    /**
     * Constroe a cruzada procurando as palavras horizontais a partir de uma
     * vertical especifica
     * 
     * @return matriz com a cruzadinha
     */
    public char[][] constroeCruzada(){
        
        //Array de char das palavras horizontais e a vertical
        char[] palavraVert, palavraHori;        
        //Matriz de char para o retorno da cruzadinha montada
        char[][] pCruzadas = new char[MAX_LINHA][MAX_COLUNA];
        
        //Procura a palavra/dica para vertical, no banco de dados
        String[] palavrasEDicas = bancoDDados.getPalavraVert();
        
        //Adiciona a palavra no array de char e no ArrayList com sua respectiva dica
        palavraVert = palavrasEDicas[1].toCharArray();
        dicas.add(palavrasEDicas[0]);
        palavras.add(palavrasEDicas[1]);
        
        //Inicio do for
        /*
        * Preenche a palavraVertical no centro da matriz e resgata o char do indicePV
        * para a busca das palavrasHorizontais que possui o mesmo char presente no indicePV
        * linha = (formula para encontrar o centro)
        */
        for/**/( int linha = (MAX_LINHA-palavraVert.length)/2, indicePV = 0, indiceInicioHori; indicePV < palavraVert.length;
                linha++, indicePV++ )/**/{
            
            //Coloca um identificador para o botão na linha anterior da vertical
            if(linha == (MAX_LINHA-palavraVert.length)/2 && indicePV == 0)
                pCruzadas[linha-1][MAX_COLUNA/2] = 1;
            
            //Preencher a palavra da verticial no centro da matriz durante o laço
            pCruzadas[linha][MAX_COLUNA/2] = palavraVert[indicePV];
            
            //Busca a palavra da horizontal que se cruza de acordo com o char do indicePV,
            //add a dica e palavra encontrada no array
            palavrasEDicas = bancoDDados.getPalavraHori(palavraVert[indicePV]);
            
            //Inicio do if
            //Testa se encontrou a palavra para preencher
            if(palavrasEDicas != null && (float)indicePV%2 == 0.0){
                
                dicas.add(palavrasEDicas[0]);
                palavras.add(palavrasEDicas[1]);

                //Pega o indice da ocorrencia, do char presente em indicePV, na palavraHori
                //para localizar onde inicia o preenchimento de palavraHori na matriz
                indiceInicioHori = palavrasEDicas[1].indexOf(palavraVert[indicePV]);

                //Converte a palavra encontrada em um array de char para o preenchimento
                palavraHori = palavrasEDicas[1].toCharArray();

                //Preenche a matriz com a palavraHori encontrada, a partir da coluna determinada,
                //para que elas se cruzem no indice correto
                for(int indicePH = 0, coluna = (MAX_COLUNA/2)-indiceInicioHori; indicePH < palavraHori.length; indicePH++, coluna++){
                    
                    //Coloca um identificador para o botão na coluna anterior da horizontal
                    if(coluna == ((MAX_COLUNA/2)-indiceInicioHori) && indicePH == 0)
                        pCruzadas[linha][coluna-1] = 1;
                    
                    pCruzadas[linha][coluna] = palavraHori[indicePH];
                }                
            }
            //Fim do if
        }
        //Fim do for
        
        return pCruzadas;//Retorna a cruzadinha
    }
    
    
    //Retorna o ArrayList com as dicas
    public List getDicas(){
        return dicas;
    }
    
    
    //Retorna o ArrayList com as palavras
    public List getPalavras(){
        return palavras;
    }
}

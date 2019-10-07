/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package jogoPCruzadas;


import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.text.SimpleDateFormat;
import java.util.GregorianCalendar;
import java.util.Locale;
import javax.swing.JOptionPane;

/**
 * Classe designada ao jogador máquina extendendo a classe Jogador
 * 
 * @author Patrick
 */
public class JogadorVirtual extends Jogador{
    
    //Atributos
    private static final String NOME = "JogadorVirtual";
    private RandomAccessFile fluxoIO;//Fluxo de IO com arquivo de dicionario do JVirtual
    private Inteligencia palavra;
    
    
    //Construtor
    public JogadorVirtual(String dificuldade){
        
        //Chama default para inicio de jogo quando score e data não são necessarios
        super(NOME, 0, dificuldade, null);        
        //Quando JVirtual é referenciado, "abre" uma conexão com sua inteligencia
        palavra = new Inteligencia();
        
        //Abre o fluxoIO e o deixa aberto enquanto o jogo está em execução
        try{            
            fluxoIO = new RandomAccessFile("dicionarioJVirtual.txt", "rw");
            
        }catch(FileNotFoundException e){
            JOptionPane.showMessageDialog(null, e, "ERRO construtor JVirtual", JOptionPane.ERROR_MESSAGE);
        }        
    }
    
    
    /**
     * 
     * Metodo de "palpite" do JVirtual
     * 
     * @param dica = Dica para buscar a palavra
     * @param tamanho = tamanho da palavra de busca
     * @return = dica palavra "palpite", senão retorna null(Passa a vez)
    */
    public String palpite(String dica, int tamanho){
        
        //Indice é o local da String onde o char está localizado
        int indice = -1;
        //Letra é o char que aparece no referente indice
        char letra = 0;
        /*Exemplo: String dica = "a3", dica dica é que existe uma char 'dica' no indice 3 da string*/
        
        //Testando se existem as dicas
        if(dica != null && (getDificuldade().equals("medio") || getDificuldade().equals("dificil"))){
            indice = Integer.parseInt(dica.substring(1));//posição 1 indica o indice
            letra = dica.charAt(0);//posição 0 indica dica letra
        }
        
        //Leitura do fluxo e suas comparações
        try{            
            String linha, chute = null;
            linha = fluxoIO.readLine();
            
                //Inicio do while
                //Verifica até o fim do arquivo
                while(linha != null){
                    
                    //Inicio do if
                    //Procura palavra do mesmo tamanho
                    if(linha.length() == tamanho){
                        
                        //Verifica se o "palpite" com essa palavra ja foi dado
                        if(!(palavra.buscarMemoria(linha))){           
                            
                            //Compara com as dicas passadas por parametro, para dar o "palpite"
                            if((indice != -1) && (linha.charAt(indice) == letra)){
                                chute = linha;
                                fluxoIO.seek(0);//Retorna o cursor para o inicio do arquivo(dicionario JVirtual)
                                break;//Encerra o while se encontrar o melhor palpite(Compativel com as dicas)                            
                            //Se as dicas não existem, mas o tamanho é o mesmo. Guarda o "palpite"
                            }else{
                                chute = linha;
                            }                            
                        }                        
                    }
                    //Fim do if
                    
                    //Pega prox String para verificar qual melhor "palpite"
                    linha = fluxoIO.readLine();                    
                }
                //Fim do while
                
                //Verifica se o "palpite" realmente existe e ainda não foi dado e o grava
                if((chute != null) && !(palavra.buscarMemoria(chute))){
                    palavra.gravarMemoria(chute);
                    fluxoIO.seek(0);//Retorna o cursor para o inicio do arquivo(dicionario JVirtual)
                    return chute;//retorna o palpite
                }
                
        }catch(IOException e){
            JOptionPane.showMessageDialog(null, e, "ERRO Chute JVirtual", JOptionPane.ERROR_MESSAGE);
        }
        
        return "";//Se o JVirtual não souber, ele retorna "" para passar a vez        
    }
    
    
    /**
     * Metodo chamado quando o jogo for finalizado, para salvar o score do jogador
     * 
     * @param b true se a partida encerrou normalmente, false se a partida foi
     * interrompida
     */
    @Override
    public void fimJogador(boolean b){
        
        if(b == true){
            //Quando o metodo é acionado, ele salva a data da partida para gravar o score
            GregorianCalendar calendar = new GregorianCalendar();
            SimpleDateFormat formatador = new SimpleDateFormat("dd/MM/yyyy\tHH:mm", new Locale("pt","BR"));
            setData(formatador.format(calendar.getTime()));
            Score.setScore(this);
        }
        
        //Deleta memoria e fecha fluxo na classe inteligencia
        palavra.fimInteligencia();        
        //Se existe o fluxo, ele o fecha
        if(fluxoIO != null)            
            try{                
                fluxoIO.close();
                
            }catch(IOException e){
                JOptionPane.showMessageDialog(null, e, "ERRO fimJVirtual JVirtual", JOptionPane.ERROR_MESSAGE);
            }       
    }
}

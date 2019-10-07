/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package jogoPCruzadas;

import java.text.SimpleDateFormat;
import java.util.GregorianCalendar;
import java.util.Locale;

/**
 * Classe Jogador pai de JReal e JVirtual, implements Comparable para
 * ordenar a leitura dos scores por ordem decrescente
 * 
 * @author Patrick
 */
public class Jogador implements Comparable<Jogador>{
    
    //Atributos
    private String nome;
    private int score;
    private String data;
    private final String dificuldade;
    
    
    //Construtor utilizado para ler score
    public Jogador(String nome, int score, String dificuldade, String data){
        this.nome = nome;
        this.score = score;
        this.dificuldade = dificuldade;
        this.data = data;
    }
    
    
    //Retorna o nome do jogador
    public String getNome() {
        return nome;
    }
    
    
    //Retorna o recorde
    public int getScore() {
        return score;
    }
    
    
    //Retorna a dificuldade escolhida pelo usuario
    public String getDificuldade() {
        return dificuldade;
    }
    
    
    //Retorna a data, utilizado na classe Score metodo setScore
    public String getData() {
        return data;
    }
    
    
    //Metodo utilizado na classe Score para ordenação da coleção
    public void setNome(String nome) {
        this.nome = nome;
    }
    
    
    //Soma os pontos passados por parametro ao score que o jogador já possui
    public void setScore(int score) {
        this.score += score;
    }
    
    
    //Metodo utilizado para gravar a data do ocorrido
    public void setData(String data) {
        this.data = data;
    }
    

    /**
     * Metodo utilizado para ordenação de coleção por metodo Collections.sort();
     * ordena descrecente
     * 
     * @param jogador
     * @return 
     */
    @Override
    public int compareTo(Jogador jogador) {
        
        if(this.score > jogador.score){
            return -1;
        }
        else 
            if(this.score < jogador.score){
                return 1;
            }
        return this.getNome().compareToIgnoreCase(jogador.getNome());
        
    }
    

    /**
     * Metodo chamado quando o jogo for finalizado, para salvar o score do jogador
     * 
     * @param b true se a partida encerrou normalmente, false se a partida foi
     * interrompida
     */
    public void fimJogador(boolean b){
        
        if(b == true){
            GregorianCalendar calendar = new GregorianCalendar();
            SimpleDateFormat formatador = new SimpleDateFormat("dd/MM/yyyy\tHH:mm", new Locale("pt","BR"));
            this.data = formatador.format(calendar.getTime());
            Score.setScore(this);
        }
    }
}

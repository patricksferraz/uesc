/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package jogoPCruzadas;

/**
 * Classe para JogadorReal extendendo a classe Jogador
 * 
 * @author Patrick
 */
public class JogadorReal extends Jogador{
    
    
    //Construtor
    public JogadorReal(String nome, String dificuldade){
        super(nome, 0, dificuldade, null);
    }
}
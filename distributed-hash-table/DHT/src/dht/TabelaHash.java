/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dht;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

/**
 *
 * @author ferraz
 */
public class TabelaHash {
    
    private List<List<String>> tabela = new ArrayList<List<String>>();
    private int tamTabela;
    private int qntRegistros = 0;
    
    public TabelaHash(int tamTabela)
    {
        this.tamTabela = tamTabela;
        for (int i = 0; i < this.tamTabela; i++)
        {
            LinkedList<String> lista = new LinkedList<String>();
            tabela.add(lista);
        }
    }
    
    public static int funcaoHash(String palavra)
    {
        int codigo = 1;
        palavra = palavra.toLowerCase();
        
        for (int i = 0; i < palavra.length(); i++)
            codigo = 31 * codigo + palavra.charAt(i);
        
        return codigo;
    }
    
    public static int calculaHash(String palavra, int tamTabela)
    {
        return Math.abs(TabelaHash.funcaoHash(palavra)) % tamTabela;
    }
    
    public void adiciona(String palavra)
    {
        if (!this.contem(palavra))
        {
            int indice = TabelaHash.calculaHash(palavra, this.tamTabela);
            List<String> lista = this.tabela.get(indice);
            lista.add(palavra);
            this.qntRegistros ++;
        }
    }

    public void remove(String palavra)
    {
        if (this.contem(palavra))
        {
            int indice = TabelaHash.calculaHash(palavra, this.tamTabela);
            List<String> lista = this.tabela.get(indice);
            lista.remove(palavra);
            this.qntRegistros --;
        }
    }
    
    public String devolveRegistro(String palavra)
    {
        // Necessário melhorar caso implementado com arquivos
        if (this.contem(palavra))
            return palavra;
        return null;
    }

    public boolean contem(String palavra)
    {
        int indice = TabelaHash.calculaHash(palavra, this.tamTabela);
        List<String> lista = this.tabela.get(indice);

        return lista.contains(palavra);
    }

    public List<String> retornaTodaTabela(){
        List<String> tabela = new ArrayList<String>();

        for (int i = 0; i < this.tabela.size(); i++)
            tabela.addAll(this.tabela.get(i));

        return tabela;
    }

    public int qntRegistros() {
        return this.qntRegistros;
    }
}

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package tipos;

import database.ConexaoDB;
import database.ProcedimentoDAO;
import static utils.DoubleUtils.*;

/**
 *
 * @author eeeeeeeeeeeeeeeeeeee
 */
public class Procedimento {
    
    private int codigo;
    private String descricao;
    private double valor;
    
    public Procedimento()
    {
    }

    public Procedimento(String codigo, String descricao, String valor) throws Exception
    {
        setCodigo(codigo);
        setDescricao(descricao);
        setValor(valor);
    }
    
    public int getCodigo() {
        return codigo;
    }

    public final void setCodigo(String codigo) {
        this.codigo = Integer.parseInt(codigo);
    }

    public String getDescricao() {
        return descricao;
    }

    public final void setDescricao(String descricao) throws Exception {
        this.descricao = descricao;
    }

    public double getValor() {
        return valor;
    }

    public final void setValor(String valor) throws Exception {
        if(valor.substring(0, 2).equals("R$"))
            valor = valor.replace("R$", "");
        else if(valor.substring(0, 1).equals("$"))
            valor = valor.replace("$", "");
       
        if(valor.contains("."))
            throw new Exception("Erro: valor de custo inválido");
        else if(valor.contains(","))
            valor = valor.replace(",", ".");
        try
        {
            this.valor = Double.valueOf(valor);            
        }
        catch(NumberFormatException ex)
        {
            System.out.println(ex.getMessage());
            throw new Exception("Erro: valor de custo inválido");
        }
    }
   
    @Override
    public String toString()
    {
        return getCodigo() + "%" + getDescricao() + "%" + formatDoubleToString(getValor());
    }
}

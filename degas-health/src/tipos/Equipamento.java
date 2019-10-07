/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package tipos;

import static utils.DoubleUtils.formatDoubleToString;
/**
 *
 * @author eeeeeeeeeeeeeeeeeeee
 */
public final class Equipamento {
    private int codigo;
    private String descricao;
    private double valor;
    
    public Equipamento()
    {
    }
    
    public Equipamento(String codigo, String descricao, String valor)
    {
        this.setCodigo(codigo);
        this.setDescricao(descricao);
        this.setValor(valor);
    }

    public void setCodigo(String codigo) {
        this.codigo = Integer.valueOf(codigo);
    }

    public void setDescricao(String descricao) {
        this.descricao = descricao;
    }

    public void setValor(String valor) {
        this.valor = Double.valueOf(valor);
    }

    public int getCodigo() {
        return codigo;
    }

    public String getDescricao() {
        return descricao;
    }

    public double getValor() {
        return valor;
    }
    
    @Override
    public String toString()
    {
        return this.getCodigo() + "%" + this.getDescricao() + "%" + formatDoubleToString(this.getValor());
    }
}

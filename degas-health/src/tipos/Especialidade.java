/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package tipos;

/**
 *
 * @author eeeeeeeeeeeeeeeeeeee
 */
public final class Especialidade {
    private int codigo;
    private String descricao;
    
    public Especialidade()
    {
    }
    
    public Especialidade(String codigo, String descricao)
    {
        this.setCodigo(codigo);
        this.setDescricao(descricao);
    }

    public void setCodigo(String codigo) {
        this.codigo = Integer.valueOf(codigo);
    }
    
    public void setDescricao(String descricao) {
        this.descricao = descricao;
    }

    public int getCodigo() {
        return codigo;
    }

    public String getDescricao() {
        return descricao;
    }
    
    @Override
    public String toString()
    {
        return this.getCodigo() + "%" + this.getDescricao();
    }
    
}

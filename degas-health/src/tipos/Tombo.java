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
public final class Tombo {
    private int codigoEquipamento;
    private String codigoTombo;
    
    public Tombo(String codigoEquipamento, String codigoTombo)
    {
        this.setCodigoEquipamento(codigoEquipamento);
        this.setCodigoTombo(codigoTombo);
    }
    
    public void setCodigoEquipamento(String codigoEquipamento)
    {
        this.codigoEquipamento = Integer.valueOf(codigoEquipamento);
    }
    
    public int getCodigoEquipamento()
    {
        return this.codigoEquipamento;
    }
    
    public void setCodigoTombo(String codigoTombo)
    {
        this.codigoTombo = codigoTombo;
    }
    
    public String getCodigoTombo()
    {
        return this.codigoTombo;
    }
    
    @Override
    public String toString()
    {
        return this.getCodigoEquipamento() + "%" + this.getCodigoTombo();
    }
}

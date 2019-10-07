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
public class Enfermeiro extends Funcionario {
    
    public Enfermeiro()
    {
        super();
    }
    
    public Enfermeiro(String nome, String sexo, String coren, String nacionalidade, String dataNasc, String dataAdmissao, String dataFormatura) throws Exception
    {
        super(nome, sexo, nacionalidade, dataNasc, dataAdmissao, dataFormatura, Integer.parseInt(coren));
    }
}

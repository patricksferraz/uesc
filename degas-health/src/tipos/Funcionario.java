/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package tipos;

import java.util.Date;
import static utils.DateUtils.*;
import static utils.StringUtils.*;

/**
 *
 * @author eeeeeeeeeeeeeeeeeeee
 */
public class Funcionario {
    private String Nome;
    private char Sexo;
    private String Nacionalidade;
    private Date DataNascimento;
    private Date DataAdmissao;
    private Date DataFormatura;
    private int codigo;
    
    public Funcionario()
    {
    }
    
    public Funcionario(String nome, String sexo, String nacionalidade, String dataNasc, String dataAdmissao, String dataFormatura, int codigo) throws Exception
    {
        this.setNome(nome);
        this.setSexo(sexo);
        this.setNacionalidade(nacionalidade);
        this.setDataNascimento(dataNasc);
        this.setDataAdmissao(dataAdmissao);
        this.setDataFormatura(dataFormatura);
        this.setCodigo(codigo);
    }
    
    public String getNome() {
        return Nome;
    }

    public final void setNome(String Nome) throws Exception{
        int pos = findSpecialChar(Nome);
        if(pos == -1)
            this.Nome = Nome;
        else
            throw new Exception("ERRO! Caracter '" + Nome.charAt(pos) + "' Invalido!");
    }

    public char getSexo() {
        return Sexo;
    }

    public final void setSexo(String Sexo) {
        this.Sexo = Sexo.charAt(0);
    }
    
    public String getNacionalidade() {
        return Nacionalidade;
    }

    public final void setNacionalidade(String Nacionalidade) throws Exception {
        int pos = findSpecialChar(Nacionalidade);
        if(pos == -1)
            this.Nacionalidade = Nacionalidade;
        else
            throw new Exception("ERRO! Caracter '" + Nacionalidade.charAt(pos) + "' Invalido!");
    }

    public Date getDataNascimento() {
        return DataNascimento;
    }

    public final void setDataNascimento(String DataNascimento) throws Exception {
        if(validateDate(DataNascimento))
        {
            this.DataNascimento = createDateFromString(DataNascimento);
        }
            
        else
            throw new Exception("ERRO! Data Inválida!");
    }

    public Date getDataAdmissao() {
        return DataAdmissao;
    }

    public final void setDataAdmissao(String DataAdmissao) throws Exception {
        if(validateDate(DataAdmissao))
            this.DataAdmissao = createDateFromString(DataAdmissao);
        else
            throw new Exception("ERRO! Data Inválida!");
        if(this.getDataFormatura() != null && this.getDataFormatura().after(this.getDataAdmissao()))
            throw new Exception("ERRO! Inconsistencia de datas: Formatura posterior a admissão!");
    }

    public Date getDataFormatura() {
        return DataFormatura;
    }

    public final void setDataFormatura(String DataFormatura) throws Exception {
        if(validateDate(DataFormatura))
            this.DataFormatura = createDateFromString(DataFormatura);
        else
            throw new Exception("ERRO! Data Inválida!");
        if(this.getDataFormatura().after(this.getDataAdmissao()))
            throw new Exception("ERRO! Inconsistencia de datas: Formatura posterior a admissão!");
    }


    public int getCodigo() {
        return codigo;
    }

    public final void setCodigo(int codigo) {
        this.codigo = codigo;
    }
    
    @Override
    public String toString()
    {
        return this.getNome() + "%" + this.getSexo() + "%" + this.getCodigo()+ "%" + this.getNacionalidade() + "%" + formatDateBR(this.getDataNascimento()) + "%" + formatDateBR(this.getDataAdmissao()) + "%" + formatDateBR(this.getDataFormatura());
    }
}

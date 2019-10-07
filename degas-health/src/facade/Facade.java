/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package facade;

import utils.EquipamentoUtils;
import utils.FuncionarioUtils;
import utils.ProcedimentoUtils;
import utils.EspecialidadeUtils;
import utils.MaterialUtils;

/**
 *
 * @author eeeeeeeeeeeeeeeeeeee
 */

public class Facade {
    
    public String novoMedico(String nome, String sexo, String crm, String nacionalidade, String dataNasc, String dataAdmissao, String dataFormatura)
    {
        String res = FuncionarioUtils.novoMedico(nome, sexo, crm, nacionalidade, dataNasc, dataAdmissao, dataFormatura);
        return res;
    }
    
    public String encontraMedico(String pesquisa)
    {
        String res = FuncionarioUtils.encontraFuncionario(pesquisa, "Medico", "CRM");
        return res;
    }
    
    public String alteraMedico(String crm, String campo, String novoValor)
    {
        String res = FuncionarioUtils.alteraFuncionario(crm, campo, novoValor, "Medico", "CRM");
        return res;
    }
    
    public String novoEnfermeiro(String nome, String sexo, String coren, String nacionalidade, String dataNasc, String dataAdmissao, String dataFormatura)
    {
        String res = FuncionarioUtils.novoEnfermeiro(nome, sexo, coren, nacionalidade, dataNasc, dataAdmissao, dataFormatura);
        return res;
    }
    
    public String encontraEnfermeiro(String pesquisa)
    {
        String res = FuncionarioUtils.encontraFuncionario(pesquisa, "Enfermeiro", "COREN");
        return res;
    }
    
    public String alteraEnfermeiro(String coren, String campo, String novoValor)
    {
        String res = FuncionarioUtils.alteraFuncionario(coren, campo, novoValor, "Enfermeiro", "COREN");
        return res;
    }
    
    public String novoAuxiliar(String nome, String sexo, String coren, String nacionalidade, String dataNasc, String dataAdmissao, String dataFormatura)
    {
        String res = FuncionarioUtils.novoAuxiliar(nome, sexo, coren, nacionalidade, dataNasc, dataAdmissao, dataFormatura);
        return res;
    }
    
    public String encontraAuxiliar(String pesquisa)
    {
        String res = FuncionarioUtils.encontraFuncionario(pesquisa, "Auxiliar", "COREN");
        return res;
    }
    
    public String alteraAuxiliar(String coren, String campo, String novoValor)
    {
        String res = FuncionarioUtils.alteraFuncionario(coren, campo, novoValor, "Auxiliar", "COREN");
        return res;
    }

    public String novoProcedimento(String codigo, String Descricao, String Custo)
    {
        String res = ProcedimentoUtils.novoProcedimento(codigo, Descricao, Custo);
        return res;
    }
    
    public String encontraProcedimento(String pesquisa)
    {
        String res = ProcedimentoUtils.encontraProcedimento(pesquisa);
        return res;
    }
    
    public String alteraProcedimento(String codigo, String campo, String novoValor)
    {
        String res = ProcedimentoUtils.alteraProcedimento(codigo, campo, novoValor);
        return res;
    }
    
    public String novaEspecialidade(String codigo, String descricao)
    {
        String res = EspecialidadeUtils.novaEspecialidade(codigo, descricao);
        return res;
    }
    
    public String encontraEspecialidade(String pesquisa)
    {
        String res = EspecialidadeUtils.encontraEspecialidade(pesquisa);
        return res;
    }
    
    public String novoEquipamento(String codigo, String descricao, String valor)
    {
        String res = EquipamentoUtils.novoEquipamento(codigo, descricao, valor);
        return res;
    }
    
    public String tombaEquipamento(String codigoEquipamento, String codigoTombo)
    {
        String res = EquipamentoUtils.tombaEquipamento(codigoEquipamento, codigoTombo);
        return res;
    }
    
    public String novoMaterial(String codigo, String descricao, String valor)
    {
        String res = MaterialUtils.novoMaterial(codigo, descricao, valor);
        return res;
    }
    
    public String materialProcedimento(String codigoProcedimento, String codigoMaterial)
    {
        String res = ProcedimentoUtils.materialProcedimento(codigoProcedimento, codigoMaterial);
        return res;
    }
    
    public String equipamentoProcedimento(String codigoProcedimento, String codigoEquipamento)
    {
        String res = ProcedimentoUtils.equipamentoProcedimento(codigoProcedimento, codigoEquipamento);
        return res;
    }
    
    public String listMateriaisProcedimento(String codigoProcedimento)
    {
        String res = ProcedimentoUtils.listMateriaisProcedimento(codigoProcedimento);
        return res;
    }
    
    public String listEquipamentosProcedimento(String codigoEquipamentos)
    {
        String res = ProcedimentoUtils.listEquipamentosProcedimento(codigoEquipamentos);
        return res;
    }
}

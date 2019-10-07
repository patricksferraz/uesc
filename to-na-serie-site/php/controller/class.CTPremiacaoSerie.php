<?php 

/**
* 
*/
class MDPremiacaoSerie
{
	private $id_serie;
    private $ano;
    private $id_premiacao;
    private $id_categoria_premio;
	private $resultado;
    private $data_cadastro;
    private $id_usuario_cadastrou;
    private $validacao_cadastro;
    private $data_validacao;
    private $id_usuario_validou;
	
	function __construct($id_serie, $ano, $id_premiacao, $id_categoria_premio, $resultado, $data_cadastro, $id_usuario_cadastrou, $validacao_cadastro, $data_validacao, $id_usuario_validou)
	{
		$this->id_serie = $id_serie;
		$this->ano = $ano;
		$this->id_premiacao = $id_premiacao;
		$this->id_categoria_premio = $id_categoria_premio;
		$this->resultado = $resultado;
		$this->data_cadastro = $data_cadastro;
		$this->id_usuario_cadastrou = $id_usuario_cadastrou;
		$this->validacao_cadastro = $validacao_cadastro;
		$this->data_validacao = $data_validacao;
		$this->id_usuario_validou = $id_usuario_validou;
	}
}

?>
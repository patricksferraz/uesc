<?php 

/**
* 
*/
class MDGeneroSerie
{
	private $id_serie;
    private $id_genero;
    private $data_cadastro;
    private $id_usuario_cadastrou;
    private $validacao_cadastro;
    private $data_validacao;
    private $id_usuario_validou;
	
	function __construct($id_serie, $id_genero, $data_cadastro, $id_usuario_cadastrou, $validacao_cadastro, $data_validacao, $id_usuario_validou)
	{
		$this->id_serie = $id_serie;
		$this->id_genero = $id_genero;
		$this->data_cadastro = $data_cadastro;
		$this->id_usuario_cadastrou = $id_usuario_cadastrou;
		$this->validacao_cadastro = $validacao_cadastro;
		$this->data_validacao = $data_validacao;
		$this->id_usuario_validou = $id_usuario_validou;
	}
}

?>
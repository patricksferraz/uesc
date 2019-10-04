<?php 

/**
* 
*/
class MDInfracaoUsuario
{
	private $id_infracao;
	private $id_usuario;
    private $data_infracao;
    private $descricao;
	
	function __construct($id_infracao, $id_usuario, $data_infracao, $descricao)
	{
		$this->id_infracao = $id_infracao;
		$this->id_usuario = $id_usuario;
		$this->data_infracao = $data_infracao;
		$this->descricao = $descricao;
	}
}

?>
<?php 

/**
* 
*/
class MDSeguidorUsuario
{
	private $id_usuario_seguidor;
    private $id_usuario_seguido;
    private $data_solicitacao;
	private $validacao_solicitacao;
    private $data_validacao;
	
	function __construct($id_usuario_seguidor, $id_usuario_seguido, $data_solicitacao, $validacao_solicitacao, $data_validacao)
	{
		$this->id_usuario_seguidor = $id_usuario_seguidor;
		$this->id_usuario_seguido = $id_usuario_seguido;
		$this->data_solicitacao = $data_solicitacao;
		$this->validacao_solicitacao = $validacao_solicitacao;
		$this->data_validacao = $data_validacao;
	}
}

?>
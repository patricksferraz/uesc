<?php 

/**
* 
*/
class CTComentarioSerie
{
	private $id_serie;
    private $id_usuario_comentou;
    private $data_comentario;
    private $mensagem;
    private $validacao_mensagem;
    private $data_validacao;
    private $id_usuario_validou;
	
	function __construct($id_serie, $id_usuario_comentou, $data_comentario, $mensagem, $validacao_mensagem, $data_validacao, $id_usuario_validou)
	{
		$this->id_serie = $id_serie;
		$this->id_usuario_comentou = $id_usuario_comentou;
		$this->data_comentario = $data_comentario;
		$this->mensagem = $mensagem;
		$this->validacao_mensagem = $validacao_mensagem;
		$this->data_validacao = $data_validacao;
		$this->id_usuario_validou = $id_usuario_validou;
	}
}

?>
<?php 

/**
* 
*/
class MDComentarioSerieAuditado
{
	private $id_serie;
    private $id_usuario_comentou;
    private $data_comentario;
    private $mensagem;
    private $descricao_motivo;
    private $data_auditoria;
    private $id_usuario_auditou;
	
	function __construct($id_serie, $id_usuario_comentou, $data_comentario, $mensagem, $descricao_motivo, $data_auditoria, $id_usuario_auditou)
	{
		$this->id_serie = $id_serie;
		$this->id_usuario_comentou = $id_usuario_comentou;
		$this->data_comentario = $data_comentario;
		$this->mensagem = $mensagem;
		$this->descricao_motivo = $descricao_motivo;
		$this->data_auditoria = $data_auditoria;
		$this->id_usuario_auditou = $id_usuario_auditou;
	}
}

?>
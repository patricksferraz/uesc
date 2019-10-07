<?php 

/**
* 
*/
class MDHistoricoVisualizacaoUsuario
{
	private $id_usuario_visitado;
    private $id_usuario_visitante;
    private $data_visualizacao;
	
	function __construct($id_usuario_visitado, $id_usuario_visitante, $data_visualizacao)
	{
		$this->id_usuario_visitado = $id_usuario_visitado;
		$this->id_usuario_visitante = $id_usuario_visitante;
		$this->data_visualizacao = $data_visualizacao;
	}
}

?>
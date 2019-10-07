<?php 

/**
* 
*/
class MDHistoricoVisualizacaoSerie
{
	private $id_serie;
    private $id_usuario;
    private $data_visualizacao;
	
	function __construct($id_serie, $id_usuario, $data_visualizacao)
	{
		$this->id_serie = $id_serie;
		$this->id_usuario = $id_usuario;
		$this->data_visualizacao = $data_visualizacao;
	}
}

?>
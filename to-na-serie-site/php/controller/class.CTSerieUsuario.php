<?php 

/**
* 
*/
class MDSerieUsuario
{
	private $id_serie;
    private $id_usuario;
    private $data_adicao;
	
	function __construct($id_serie, $id_usuario, $data_adicao)
	{
		$this->id_serie = $id_serie;
		$this->id_usuario = $id_usuario;
		$this->data_adicao = $data_adicao;
	}
}

?>
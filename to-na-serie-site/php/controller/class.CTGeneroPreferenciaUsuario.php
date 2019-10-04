<?php 

/**
* 
*/
class MDGeneroPreferenciaUsuario
{
	private $id_usuario;
    private $id_genero;
    private $data_cadastro;
    private $nivel_preferencia;
	
	function __construct($id_usuario, $id_genero, $data_cadastro, $nivel_preferencia)
	{
		$this->id_usuario = $id_usuario;
		$this->id_genero = $id_genero;
		$this->data_cadastro = $data_cadastro;
		$this->nivel_preferencia = $nivel_preferencia;
	}
}

?>
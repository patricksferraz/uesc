<?php 

/**
* 
*/
class MDEpisodioAssistidoUsuario
{
	private $id_serie;
    private $id_temporada_serie;
    private $id_episodio_temporada_serie;
    private $id_usuario;
    private $avaliacao;
    private $observacoes;
    private $data_visualizacao;
	
	function __construct($id_serie, $id_temporada_serie, $id_episodio_temporada_serie, $id_usuario, $avaliacao, $observacoes, $data_visualizacao)
	{
		$this->id_serie = $id_serie;
		$this->id_temporada_serie = $id_temporada_serie;
		$this->id_episodio_temporada_serie = $id_episodio_temporada_serie;
		$this->id_usuario = $id_usuario;
		$this->avaliacao = $avaliacao;
		$this->observacoes = $observacoes;
		$this->data_visualizacao = $data_visualizacao;
	}
}

?>
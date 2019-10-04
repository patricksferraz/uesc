<?php 

/**
* 
*/
class MDEpisodioTemporadaSerie
{
	private $id_serie;
    private $id_temporada_serie;
    private $id_episodio_temporada_serie;
    private $titulo_original;
    private $titulo_portugues;
    private $data_exibicao_usa;
    private $data_exibicao_bra;
    private $sinopse;
    private $data_cadastro;
    private $id_usuario_cadastrou;
    private $validacao_cadastro;
    private $data_validacao;
    private $id_usuario_validou;
	
	function __construct($id_serie, $id_temporada_serie, $id_episodio_temporada_serie, $titulo_original, $titulo_portugues, $data_exibicao_usa, $data_exibicao_bra, $sinopse, $data_cadastro, $id_usuario_cadastrou, $validacao_cadastro, $data_validacao, $id_usuario_validou)
	{
		$this->id_serie = $id_serie;
		$this->id_temporada_serie = $id_temporada_serie;
		$this->id_episodio_temporada_serie = $id_episodio_temporada_serie;
		$this->titulo_original = $titulo_original;
		$this->titulo_portugues = $titulo_portugues;
		$this->data_exibicao_usa = $data_exibicao_usa;
		$this->data_exibicao_bra = $data_exibicao_bra;
		$this->sinopse = $sinopse;
		$this->data_cadastro = $data_cadastro;
		$this->id_usuario_cadastrou = $id_usuario_cadastrou;
		$this->validacao_cadastro = $validacao_cadastro;
		$this->data_validacao = $data_validacao;
		$this->id_usuario_validou = $id_usuario_validou;
	}
}

?>
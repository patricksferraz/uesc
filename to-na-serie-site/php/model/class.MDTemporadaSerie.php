<?php 

/**
* 
*/
class MDTemporadaSerie
{
	private $id_serie;
    private $id_temporada_serie;
    private $data_inicio;
    private $data_fim;
    private $descricao;
    private $nome_imagem;
    private $tamanho_imagem;
    private $tipo_imagem;
    private $imagem;
    private $nome_video;
    private $tamanho_video;
    private $tipo_video;
    private $video;
    private $data_cadastro;
    private $id_usuario_cadastrou;
    private $validacao_cadastro;
    private $data_validacao;
    private $id_usuario_validou;
	
	function __construct($id_serie, $id_temporada_serie, $data_inicio, $data_fim, $descricao, $nome_imagem, $tamanho_imagem, $tipo_imagem, $imagem, $nome_video, $tamanho_video, $tipo_video, $video, $data_cadastro, $id_usuario_cadastrou, $validacao_cadastro, $data_validacao, $id_usuario_validou)
	{
		$this->id_serie = $id_serie;
		$this->id_temporada_serie = $id_temporada_serie;
		$this->data_inicio = $data_inicio;
		$this->data_fim = $data_fim;
		$this->descricao = $descricao;
		$this->nome_imagem = $nome_imagem;
		$this->tamanho_imagem = $tamanho_imagem;
		$this->tipo_imagem = $tipo_imagem;
		$this->imagem = $imagem;
		$this->nome_video = $nome_video;
		$this->tamanho_video = $tamanho_video;
		$this->tipo_video = $tipo_video;
		$this->video = $video;
		$this->data_cadastro = $data_cadastro;
		$this->id_usuario_cadastrou = $id_usuario_cadastrou;
		$this->validacao_cadastro = $validacao_cadastro;
		$this->data_validacao = $data_validacao;
		$this->id_usuario_validou = $id_usuario_validou;
	}
}

?>
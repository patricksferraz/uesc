<?php 

/**
* 
*/
class MDSerie
{
	private $id_serie;
    private $titulo_original;
    private $titulo_portugues;
    private $data_estreia;
    private $data_fim;
    private $id_emissora;
    private $id_pais;
    private $id_idioma;
    private $id_classificacao_etaria;
    private $sinopse;
    private $nome_imagem;
    private $tamanho_imagem;
    private $tipo_imagem;
    private $imagem_cabecalho;
    private $data_cadastro;
    private $status;
    private $id_usuario_cadastrou;
    private $validacao_cadastro;
    private $data_validacao;
    private $id_usuario_validou;
	
	function __construct($array)
	{
		$this->id_serie = $array[0];
		$this->titulo_original = $array[1];
		$this->titulo_portugues = $array[2];
		$this->data_estreia = $array[3];
		$this->data_fim = $array[4];
		$this->id_emissora = $array[5];
		$this->id_pais = $array[6];
		$this->id_idioma = $array[7];
		$this->id_classificacao_etaria = $array[8];
		$this->sinopse = $array[9];
		$this->nome_imagem = $array[10];
		$this->tamanho_imagem = $array[11];
		$this->tipo_imagem = $array[12];
		$this->imagem_cabecalho = $array[13];
		$this->data_cadastro = $array[14];
		$this->status = $array[15];
		$this->id_usuario_cadastrou = $array[16];
		$this->validacao_cadastro = $array[17];
		$this->data_validacao = $array[18];
		$this->id_usuario_validou = $array[19];
	}

    /**
     * @return mixed
     */
    public function getIdSerie()
    {
        return $this->id_serie;
    }

    /**
     * @param mixed $id_serie
     *
     * @return self
     */
    public function setIdSerie($id_serie)
    {
        $this->id_serie = $id_serie;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getTituloOriginal()
    {
        return $this->titulo_original;
    }

    /**
     * @param mixed $titulo_original
     *
     * @return self
     */
    public function setTituloOriginal($titulo_original)
    {
        $this->titulo_original = $titulo_original;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getTituloPortugues()
    {
        return $this->titulo_portugues;
    }

    /**
     * @param mixed $titulo_portugues
     *
     * @return self
     */
    public function setTituloPortugues($titulo_portugues)
    {
        $this->titulo_portugues = $titulo_portugues;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getDataEstreia()
    {
        return $this->data_estreia;
    }

    /**
     * @param mixed $data_estreia
     *
     * @return self
     */
    public function setDataEstreia($data_estreia)
    {
        $this->data_estreia = $data_estreia;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getDataFim()
    {
        return $this->data_fim;
    }

    /**
     * @param mixed $data_fim
     *
     * @return self
     */
    public function setDataFim($data_fim)
    {
        $this->data_fim = $data_fim;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getIdEmissora()
    {
        return $this->id_emissora;
    }

    /**
     * @param mixed $id_emissora
     *
     * @return self
     */
    public function setIdEmissora($id_emissora)
    {
        $this->id_emissora = $id_emissora;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getIdPais()
    {
        return $this->id_pais;
    }

    /**
     * @param mixed $id_pais
     *
     * @return self
     */
    public function setIdPais($id_pais)
    {
        $this->id_pais = $id_pais;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getIdIdioma()
    {
        return $this->id_idioma;
    }

    /**
     * @param mixed $id_idioma
     *
     * @return self
     */
    public function setIdIdioma($id_idioma)
    {
        $this->id_idioma = $id_idioma;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getIdClassificacaoEtaria()
    {
        return $this->id_classificacao_etaria;
    }

    /**
     * @param mixed $id_classificacao_etaria
     *
     * @return self
     */
    public function setIdClassificacaoEtaria($id_classificacao_etaria)
    {
        $this->id_classificacao_etaria = $id_classificacao_etaria;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getSinopse()
    {
        return $this->sinopse;
    }

    /**
     * @param mixed $sinopse
     *
     * @return self
     */
    public function setSinopse($sinopse)
    {
        $this->sinopse = $sinopse;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getNomeImagem()
    {
        return $this->nome_imagem;
    }

    /**
     * @param mixed $nome_imagem
     *
     * @return self
     */
    public function setNomeImagem($nome_imagem)
    {
        $this->nome_imagem = $nome_imagem;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getTamanhoImagem()
    {
        return $this->tamanho_imagem;
    }

    /**
     * @param mixed $tamanho_imagem
     *
     * @return self
     */
    public function setTamanhoImagem($tamanho_imagem)
    {
        $this->tamanho_imagem = $tamanho_imagem;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getTipoImagem()
    {
        return $this->tipo_imagem;
    }

    /**
     * @param mixed $tipo_imagem
     *
     * @return self
     */
    public function setTipoImagem($tipo_imagem)
    {
        $this->tipo_imagem = $tipo_imagem;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getImagemCabecalho()
    {
        return $this->imagem_cabecalho;
    }

    /**
     * @param mixed $imagem_cabecalho
     *
     * @return self
     */
    public function setImagemCabecalho($imagem_cabecalho)
    {
        $this->imagem_cabecalho = $imagem_cabecalho;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getDataCadastro()
    {
        return $this->data_cadastro;
    }

    /**
     * @param mixed $data_cadastro
     *
     * @return self
     */
    public function setDataCadastro($data_cadastro)
    {
        $this->data_cadastro = $data_cadastro;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getStatus()
    {
        return $this->status;
    }

    /**
     * @param mixed $status
     *
     * @return self
     */
    public function setStatus($status)
    {
        $this->status = $status;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getIdUsuarioCadastrou()
    {
        return $this->id_usuario_cadastrou;
    }

    /**
     * @param mixed $id_usuario_cadastrou
     *
     * @return self
     */
    public function setIdUsuarioCadastrou($id_usuario_cadastrou)
    {
        $this->id_usuario_cadastrou = $id_usuario_cadastrou;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getValidacaoCadastro()
    {
        return $this->validacao_cadastro;
    }

    /**
     * @param mixed $validacao_cadastro
     *
     * @return self
     */
    public function setValidacaoCadastro($validacao_cadastro)
    {
        $this->validacao_cadastro = $validacao_cadastro;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getDataValidacao()
    {
        return $this->data_validacao;
    }

    /**
     * @param mixed $data_validacao
     *
     * @return self
     */
    public function setDataValidacao($data_validacao)
    {
        $this->data_validacao = $data_validacao;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getIdUsuarioValidou()
    {
        return $this->id_usuario_validou;
    }

    /**
     * @param mixed $id_usuario_validou
     *
     * @return self
     */
    public function setIdUsuarioValidou($id_usuario_validou)
    {
        $this->id_usuario_validou = $id_usuario_validou;

        return $this;
    }
}

?>
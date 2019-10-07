<?php 

/**
* 
*/
class MDClassificacaoEtaria
{
	private $id_classificacao_etaria;
    private $descricao;
    private $nome_imagem;
    private $tamanho_imagem;
    private $tipo_imagem;
    private $imagem;
    private $data_cadastro;
    private $id_usuario_cadastrou;
	
	function __construct($array)
	{
		$this->id_classificacao_etaria = $array[0];
		$this->descricao = $array[1];
		$this->nome_imagem = $array[2];
		$this->tamanho_imagem = $array[3];
		$this->tipo_imagem = $array[4];
		$this->imagem = $array[5];
		$this->data_cadastro = $array[6];
		$this->id_usuario_cadastrou = $array[7];
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
    public function getDescricao()
    {
        return $this->descricao;
    }

    /**
     * @param mixed $descricao
     *
     * @return self
     */
    public function setDescricao($descricao)
    {
        $this->descricao = $descricao;

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
    public function getImagem()
    {
        return $this->imagem;
    }

    /**
     * @param mixed $imagem
     *
     * @return self
     */
    public function setImagem($imagem)
    {
        $this->imagem = $imagem;

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
}

?>
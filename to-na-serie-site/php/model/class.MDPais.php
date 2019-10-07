<?php 

/**
* 
*/
class MDPais
{
	private $id_pais;
    private $nome;
    private $nome_imagem;
    private $tamanho_imagem;
    private $tipo_imagem;
    private $imagem;
    private $data_cadastro;
    private $id_usuario_cadastrou;
	
	function __construct($array)
	{
		$this->id_pais = $array[0];
		$this->nome = $array[1];
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
    public function getNome()
    {
        return $this->nome;
    }

    /**
     * @param mixed $nome
     *
     * @return self
     */
    public function setNome($nome)
    {
        $this->nome = $nome;

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
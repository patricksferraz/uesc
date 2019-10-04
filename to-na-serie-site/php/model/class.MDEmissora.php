<?php 

/**
* 
*/
class MDEmissora
{
	private $id_emissora;
    private $nome;
    private $sigla;
    private $pagina_oficial;
    private $data_cadastro;
    private $id_usuario_cadastrou;
	
	function __construct($array)
	{
		$this->id_emissora = $array[0];
		$this->nome = $array[1];
		$this->sigla = $array[2];
		$this->pagina_oficial = $array[3];
		$this->data_cadastro = $array[4];
		$this->id_usuario_cadastrou = $array[5];
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
    public function getSigla()
    {
        return $this->sigla;
    }

    /**
     * @param mixed $sigla
     *
     * @return self
     */
    public function setSigla($sigla)
    {
        $this->sigla = $sigla;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getPaginaOficial()
    {
        return $this->pagina_oficial;
    }

    /**
     * @param mixed $pagina_oficial
     *
     * @return self
     */
    public function setPaginaOficial($pagina_oficial)
    {
        $this->pagina_oficial = $pagina_oficial;

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
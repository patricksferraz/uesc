<?php 

/**
* 
*/
class MDIdioma
{
	private $id_idioma;
    private $nome;
    private $data_cadastro;
    private $id_usuario_cadastrou;
	
	function __construct($array)
	{
		$this->id_idioma = $array[0];
		$this->nome = $array[1];
		$this->data_cadastro = $array[2];
		$this->id_usuario_cadastrou = $array[3];
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
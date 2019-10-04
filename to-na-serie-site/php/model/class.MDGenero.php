<?php 

/**
* 
*/
class MDGenero
{
	private $id_genero;
    private $nome;
    private $data_cadastro;
    private $id_usuario_cadastrou;
	
	function __construct($array)
	{
		$this->id_genero = $array[0];
		$this->nome = $array[1];
		$this->data_cadastro = $array[2];
		$this->id_usuario_cadastrou = $array[3];
	}

    /**
     * @return mixed
     */
    public function getIdGenero()
    {
        return $this->id_genero;
    }

    /**
     * @param mixed $id_genero
     *
     * @return self
     */
    public function setIdGenero($id_genero)
    {
        $this->id_genero = $id_genero;

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
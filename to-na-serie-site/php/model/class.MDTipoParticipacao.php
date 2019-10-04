<?php 

/**
* 
*/
class MDTipoParticipacao
{
	private $id_tipo_participacao;
    private $nome;
    private $data_cadastro;
    private $id_usuario_cadastrou;
	
	function __construct($array)
	{
		$this->id_tipo_participacao = $array[0];
		$this->nome = $array[1];
		$this->data_cadastro = $array[2];
		$this->id_usuario_cadastrou = $array[3];
	}

    /**
     * @return mixed
     */
    public function getIdTipoParticipacao()
    {
        return $this->id_tipo_participacao;
    }

    /**
     * @param mixed $id_tipo_participacao
     *
     * @return self
     */
    public function setIdTipoParticipacao($id_tipo_participacao)
    {
        $this->id_tipo_participacao = $id_tipo_participacao;

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
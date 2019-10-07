<?php 

/**
* 
*/
class MDAlteracaoDadosUsuario
{
	private $id_usuario;
    private $data_alteracao;
    private $id_usuario_alterou;
	
	function __construct($array)
	{
		$this->id_usuario = $array[0];
		$this->data_alteracao = $array[1];
		$this->id_usuario_alterou = $array[2];
	}

    /**
     * @return mixed
     */
    public function getIdUsuario()
    {
        return $this->id_usuario;
    }

    /**
     * @param mixed $id_usuario
     *
     * @return self
     */
    public function setIdUsuario($id_usuario)
    {
        $this->id_usuario = $id_usuario;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getDataAlteracao()
    {
        return $this->data_alteracao;
    }

    /**
     * @param mixed $data_alteracao
     *
     * @return self
     */
    public function setDataAlteracao($data_alteracao)
    {
        $this->data_alteracao = $data_alteracao;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getIdUsuarioAlterou()
    {
        return $this->id_usuario_alterou;
    }

    /**
     * @param mixed $id_usuario_alterou
     *
     * @return self
     */
    public function setIdUsuarioAlterou($id_usuario_alterou)
    {
        $this->id_usuario_alterou = $id_usuario_alterou;

        return $this;
    }
}

?>
<?php 

/**
* 
*/
class MDAlteracaoDadosSerie
{
	private $id_serie;
    private $data_alteracao;
    private $id_usuario_alterou;
	
	function __construct($array)
	{
		$this->id_serie = $array[0];
		$this->data_alteracao = $array[1];
		$this->id_usuario_alterou = $array[2];
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
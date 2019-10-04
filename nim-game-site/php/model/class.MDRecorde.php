<?php 

/**
* 
*/
class MDRecorde
{
	private $id_recorde;
    private $pontos;
    private $qnt_linha;
    private $data;
    private $id_usuario;
	
	function __construct($array)
	{
		$this->id_recorde = $array[0];
		$this->pontos     = $array[1];
		$this->qnt_linha  = $array[2];
		$this->data       = $array[3];
        $this->id_usuario = $array[4];
	}

    /**
     * @return mixed
     */
    public function getIdRecorde()
    {
        return $this->id_recorde;
    }

    /**
     * @param mixed $id_recorde
     *
     * @return self
     */
    public function setIdRecorde($id_recorde)
    {
        $this->id_recorde = $id_recorde;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getPontos()
    {
        return $this->pontos;
    }

    /**
     * @param mixed $pontos
     *
     * @return self
     */
    public function setPontos($pontos)
    {
        $this->pontos = $pontos;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getQntLinha()
    {
        return $this->qnt_linha;
    }

    /**
     * @param mixed $qnt_linha
     *
     * @return self
     */
    public function setQntLinha($qnt_linha)
    {
        $this->qnt_linha = $qnt_linha;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getData()
    {
        return $this->data;
    }

    /**
     * @param mixed $data
     *
     * @return self
     */
    public function setData($data)
    {
        $this->data = $data;

        return $this;
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
}

?>
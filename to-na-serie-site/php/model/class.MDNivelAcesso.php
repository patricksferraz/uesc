<?php 

/**
* 
*/
class MDNivelAcesso
{
	private $id_nivel_acesso;
    private $nome;
	
	function __construct($array)
	{
		$this->id_nivel_acesso = $array[0];
		$this->nome = $array[1];
	}

    /**
     * @return mixed
     */
    public function getIdNivelAcesso()
    {
        return $this->id_nivel_acesso;
    }

    /**
     * @param mixed $id_nivel_acesso
     *
     * @return self
     */
    public function setIdNivelAcesso($id_nivel_acesso)
    {
        $this->id_nivel_acesso = $id_nivel_acesso;

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
}

?>
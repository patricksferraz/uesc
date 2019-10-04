<?php 

require_once __ROOT__.'/php/model/class.CTHistoricoLogin.php';

/**
* 
*/
class MDHistoricoLogin
{
	private $id_usuario;
    private $data_login;
    private $data_logout;
    private $ip_login;
    private $user_agent;
	
	function __construct($array)
	{
		$this->id_usuario = $array[0];
		$this->data_login = $array[1];
		$this->data_logout = $array[2];
		$this->ip_login = $array[3];
		$this->user_agent = $array[4];
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
    public function getDataLogin()
    {
        return $this->data_login;
    }

    /**
     * @param mixed $data_login
     *
     * @return self
     */
    public function setDataLogin($data_login)
    {
        $this->data_login = $data_login;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getDataLogout()
    {
        return $this->data_logout;
    }

    /**
     * @param mixed $data_logout
     *
     * @return self
     */
    public function setDataLogout($data_logout)
    {
        $this->data_logout = $data_logout;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getIpLogin()
    {
        return $this->ip_login;
    }

    /**
     * @param mixed $ip_login
     *
     * @return self
     */
    public function setIpLogin($ip_login)
    {
        $this->ip_login = $ip_login;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getUserAgent()
    {
        return $this->user_agent;
    }

    /**
     * @param mixed $user_agent
     *
     * @return self
     */
    public function setUserAgent($user_agent)
    {
        $this->user_agent = $user_agent;

        return $this;
    }
}

?>
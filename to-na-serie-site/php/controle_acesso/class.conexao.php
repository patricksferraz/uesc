<?php

class Conexao
{
    protected $link;
    private $dsn, $username, $password;

    public function __construct($dsn, $username, $password)
    {
        $this->dsn = $dsn;
        $this->username = $username;
        $this->password = $password;
        $this->conectar();
    }

    public function __destruct(){
        $this->link = null;
    }

    private function conectar()
    {
        try
        {
            $this->link = new PDO($this->dsn, $this->username, $this->password, array(PDO::ATTR_PERSISTENT => true));
            $this->link->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
        }
        catch (PDOException $e)
        {
            $this->link = false;
        }
    }

    public function __sleep()
    {
        return array('dsn', 'username', 'password');
    }

    public function __wakeup()
    {
        $this->conectar();
    }

    public function getConexao()
    {
        return $this->link;
    }
}

?>
<?php

require_once 'class.conexao.php';


function con_db_jogo_nim()
{

    $dns = "mysql:host=127.0.0.1;dbname=db_jogo_nim";
    $usr = "root";
    $pas = "root";

    $con = new Conexao($dns, $usr, $pas);
    return $con->getConexao();

}

?>

<?php

require_once 'class.conexao.php';


function con_db_tns()
{

    $dns = "mysql:host=localhost;dbname=db_to_na_serie";
    $usr = "root";
    $pas = "root";

    $con = new Conexao($dns, $usr, $pas);
    return $con->getConexao();

}

?>
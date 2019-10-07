<?php

require_once 'resgate_sessao.php';
require_once 'nvl_acesso.php';

if (!esta_conectado($_SESSION))
{
    header("Location: ../index.php");
}

?>
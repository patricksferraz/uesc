<?php

require_once 'resgate_sessao.php';
session_destroy(); // Destrói a sessão limpando todos os valores salvos
header("Location: ../../www/index.php");  // Redireciona o visitante

?>
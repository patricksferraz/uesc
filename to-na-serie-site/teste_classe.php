<?php 

require_once 'www/dir_root.php';
require_once __ROOT__.'/php/autoload_class.php';
require_once __ROOT__.'/php/controle_acesso/conexao.php';
require_once __ROOT__.'/php/controller/class.CTClassificacaoEtaria.php';

$con = con_db_tns();

$n = CTClassificacaoEtaria::selectClassificacoesEtarias($con);

foreach ($n as $k) {
	echo "<img src='gera.php?id=".$k->getTipoImagem()."&img=".$k->getImagem()."' width='100' height='100' border='1'>";
}

?>
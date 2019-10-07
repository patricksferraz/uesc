<?php
$p = &$_POST;

require_once 'class.controlador.php';
require_once 'model/class.MDUsuario.php';
require_once 'model/class.MDRecorde.php';
require_once 'conexao.php';

$con = con_db_jogo_nim();
$dados = array();
$acao  = $p['acao'];

switch ($acao)
{
	case 'cadastroJogador':
		$nome  = $p['nome'];
		$email = $p['email'];
		$senha = $p['senha'];

		$retorno = Controlador::selectUsuario($con, $nome);

		if ($retorno->getNome())
		{
			$dados['validacao'] = false;
			$dados['motivo'] 	= "Usuário já existente";
		}
		else
		{
			$usuario = new MDUsuario(array(null, $nome, $email, md5($senha), null));
			$result = Controlador::insertUsuario($con, $usuario);
			if ($result == false)
			{
				$dados['motivo'] = "Erro ao cadastrar usuário. Entre em contato com suporte";
			}

			$dados['validacao'] = $result;

			$usuario = null;
		}

		$retorno = null;

		break;
	
	case 'loginJogador':
		$usuario = $p['usuario'];
		$senha 	 = $p['senha'];

		$retorno = Controlador::selectUsuario($con, $usuario);

		if (empty($retorno->getNome()) || ($retorno->getSenha() != md5($senha)))
			$dados['validacao'] = false;
		else
		{
			$dados['codUsuario'] = $retorno->getIdUsuario();
			$dados['validacao']  = true;
		}

		$retorno = null;

		break;

	case 'graveRecorde':
        $qntLinhas    = $p['qntLinhas'];
        $codJogador   = $p['codJogador'];
        $scoreJogador = $p['scoreJogador'];

    	if ($scoreJogador[0] != 0)
    	{
	    	if ($codJogador[0] == '') $codJogador[0] = null;
	        $recorde = new MDRecorde(array(null, $scoreJogador[0], $qntLinhas, null, $codJogador[0]));
			Controlador::insertRecorde($con, $recorde);
	        $recorde = null;
    	}

    	if ($scoreJogador[1] != 0)
    	{
	    	if ($codJogador[1] == '') $codJogador[1] = null;
	        $recorde = new MDRecorde(array(null, $scoreJogador[1], $qntLinhas, null, $codJogador[1]));
			Controlador::insertRecorde($con, $recorde);
			$recorde = null;
    	}

		break;

	default:
		break;
}

 echo json_encode($dados);

?>

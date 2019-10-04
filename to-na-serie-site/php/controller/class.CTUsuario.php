<?php

require_once __ROOT__.'/php/model/class.MDUsuario.php';
require_once __ROOT__.'/php/funs_php.php';
require_once __ROOT__.'/php/controller/class.CTAlteracaoDadosUsuario.php';

/**
* 
*/
class CTUsuario
{

	public static function validarDadosCadastroUsuario($p)
	{
		$t = array();

		$t[] = esta_setado($p, 'nId');
		$t[] = esta_setado($p, 'sNivelAcesso');
		$t[] = esta_setado($p, 'tNome');
		$t[] = esta_setado($p, 'tApelido');
		$t[] = esta_setado($p, 'sSexo');
		$t[] = esta_setado($p, 'dDataNascimento');
		$t[] = esta_setado($p, 'eEmail');
		$t[] = esta_setado($p, 'tTelefone');
		$t[] = esta_setado($p, 'tFacebook');
		$t[] = esta_setado($p, 'pSenha');
		if (!$temp = esta_setado($p, 'status'))
			$t[] = 1;
		else
			$t[] = $temp;
	    $t[] = esta_setado($p, 'nome_imagem');
	    $t[] = esta_setado($p, 'tamanho_imagem');
	    $t[] = esta_setado($p, 'tipo_imagem');
	    $t[] = esta_setado($p, 'imagem');
	    if (!$temp = esta_setado($p, 'validacao_cadastro'))
	    	$t[] = 0;
	    else
	    	$t[] = $temp;
	    $t[] = esta_setado($p, 'data_cadastro');
	    $t[] = esta_setado($p, 'id_usuario_cadastrou');

		return $t;
	}

	public static function selectUsuarios($con)
	{
		try 
		{
			$usuario = array();
			$sql = "SELECT * FROM usr_usuario ORDER BY usr_id_usuario";

			foreach ($con->query($sql) as $row) {
				$usuario[] = new MDUsuario($row);
			}

			return $usuario;

		}
		catch (Exception $e) 
		{

			return false;
			
		}
	}

	public static function selectUsuario($con, $nome)
	{
		try 
		{
			$usuario = array();

			$sql = "SELECT * FROM usr_usuario WHERE usr_nome LIKE :nome";

			$stmt = $con->prepare($sql);
			$stmt->execute(array('nome' => "%$nome%"));
			$row = $stmt->fetchAll();

			foreach ($row as $r) {
				$usuario[] = new MDUsuario($r);
			}

			$stmt = $row = null;

			return $usuario;

		}
		catch (Exception $e) 
		{

			return false;
			
		}
	}

	public static function selectUsuarioId($con, $id)
	{
		try 
		{

			$sql = "SELECT * FROM usr_usuario WHERE usr_id_usuario = $id";

			$stmt = $con->query($sql);
			$row = $stmt->fetch();

			$usuario = new MDUsuario($row);

			$stmt = $row = null;

			return $usuario;

		}
		catch (Exception $e) 
		{

			return false;
			
		}
	}

	public static function insertUpdateUsuario($con, $id_usuario_logado, MDUsuario $usuario)
	{
		try 
		{

			$duplicidade = array();
			date_default_timezone_set("America/Sao_Paulo");

			if ($usuario->getIdNivelAcesso() == null)
				$usuario->setIdNivelAcesso(6);

			if ($usuario->getIdUsuario() == null)
			{
				$duplicidade = self::existeDuplicidade($con, $usuario->getApelido(), $usuario->getEmail());

				if (count($duplicidade))
					return $duplicidade;

				$usuario->setIdUsuario(self::proxId($con));
				$usuario->setDataCadastro(date("Y-m-d H:i:s"));

				if (isset($id_usuario_logado))
					$usuario->setIdUsuarioCadastrou($id_usuario_logado);
				else
					$usuario->setIdUsuarioCadastrou($usuario->getIdUsuario());
				
				$sql = "INSERT INTO usr_usuario (usr_id_usuario, usr_id_nivel_acesso, usr_nome, usr_apelido, usr_sexo, usr_data_nascimento, usr_email, usr_telefone, usr_facebook, usr_senha, usr_status, usr_nome_imagem, usr_tamanho_imagem, usr_tipo_imagem, usr_imagem, usr_validacao_cadastro, usr_data_cadastro, usr_id_usuario_cadastrou)
					VALUES (:id_usuario, :id_nivel_acesso, :nome, :apelido, :sexo, :data_nascimento, :email, :telefone, :facebook, :senha, :status, :nome_imagem, :tamanho_imagem, :tipo_imagem, :imagem, :validacao_cadastro, :data_cadastro, :id_usuario_cadastrou)";
			}
			else
			{
				$sql = "UPDATE usr_usuario SET usr_id_usuario = :id_usuario, usr_id_nivel_acesso = :id_nivel_acesso, usr_nome = :nome, usr_apelido = :apelido, usr_sexo = :sexo, usr_data_nascimento = :data_nascimento, usr_email = :email, usr_telefone = :telefone, usr_facebook = :facebook, usr_senha = :senha, usr_status = :status, usr_nome_imagem = :nome_imagem, usr_tamanho_imagem = :tamanho_imagem, usr_tipo_imagem = :tipo_imagem, usr_imagem = :imagem, usr_validacao_cadastro = :validacao_cadastro, usr_data_cadastro = :data_cadastro, usr_id_usuario_cadastrou = :id_usuario_cadastrou
					WHERE usr_id_usuario = ".$usuario->getIdUsuario();
			}

			$stmt = $con->prepare($sql);
			$stmt->execute(array(
				'id_usuario' => $usuario->getIdUsuario(),
				'id_nivel_acesso' => $usuario->getIdNivelAcesso(),
				'nome' => $usuario->getNome(),
				'apelido' => $usuario->getApelido(),
				'sexo' => $usuario->getSexo(),
				'data_nascimento' => $usuario->getDataNascimento(),
				'email' => $usuario->getEmail(),
				'telefone' => $usuario->getTelefone(),
				'facebook' => $usuario->getFacebook(),
				'senha' => md5($usuario->getSenha()),
				'status' => $usuario->getStatus(),
				'nome_imagem' => $usuario->getNomeImagem(),
				'tamanho_imagem' => $usuario->getTamanhoImagem(),
				'tipo_imagem' => $usuario->getTipoImagem(),
				'imagem' => $usuario->getImagem(),
				'validacao_cadastro' => $usuario->getValidacaoCadastro(),
				'data_cadastro' => $usuario->getDataCadastro(),
				'id_usuario_cadastrou' => $usuario->getIdUsuarioCadastrou()
			));
			
			$alteracao_dados_usuario = new MDAlteracaoDadosUsuario(array(
				$usuario->getIdUsuario(),
				null,
				$id_usuario_logado
			));

			CTAlteracaoDadosUsuario::insertAlteracaoDadosUsuario($con, $alteracao_dados_usuario);

			return $duplicidade;

		}
		catch (Exception $e) 
		{
			$msg[] = $e->getMessage();
			return $msg;
			
		}
	}

	public static function existeDuplicidade($con, $apelido, $email)
	{
		try 
		{
			$msg_erro = array();


			$sql = "SELECT * FROM usr_usuario WHERE usr_apelido LIKE :apelido AND usr_email LIKE :email";
			$stmt = $con->prepare($sql);

			$stmt->execute(array('apelido' => $apelido, "email" => '%'));
			$qnt_row = $stmt->rowCount();
			if ($qnt_row)
				$msg_erro[] = "Já existe usuário cadastrado com esse apelido";

			$stmt->execute(array('email' => $email, "apelido" => '%'));
			$qnt_row = $stmt->rowCount();
			if ($qnt_row)
				$msg_erro[] = "Já existe usuário cadastrado com esse e-mail";

			$stmt = $qnt_row = null;

			return $msg_erro;

		}
		catch (Exception $e) 
		{

			$msg[] = $e->getMessage();
			return $msg;
			
		}
	}

	public static function proxId($con)
	{
		try 
		{
			$sql = "SELECT max(usr_id_usuario) FROM usr_usuario";

			$stmt = $con->query($sql);
			$row = $stmt->fetch();

			$prox_id = $row[0]+1;

			$stmt = $row = null;

			return $prox_id;

		}
		catch (Exception $e) 
		{

			return false;
			
		}
	}
}

?>
<?php 

require_once 'dir_root.php';
require_once __ROOT__.'/php/model/class.MDRecorde.php';
require_once __ROOT__.'/php/model/class.MDUsuario.php';

/**
* 
*/
class Controlador
{
	public static function selectRecordes($con)
	{
		try 
		{
			$recorde = array();
			$sql = "SELECT * FROM rec_recorde ORDER BY rec_pontos DESC";

			foreach ($con->query($sql) as $row)
			{
				$recorde[] = new MDRecorde($row);
			}

			return $recorde;

		}
		catch (Exception $e) 
		{

			return false;
			
		}
	}

	public static function selectUsuario($con, $usr)
	{
		try 
		{
			if (is_string($usr))
				$sql = "SELECT * FROM usu_usuario WHERE usu_nome LIKE '$usr'";
			else
				$sql = "SELECT * FROM usu_usuario WHERE usu_id_usuario = $usr";

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

	public static function insertUsuario($con, MDUsuario $usuario)
	{
		try 
		{

			date_default_timezone_set("America/Sao_Paulo");

			$usuario->setIdUsuario(self::proxIdUsuario($con));
			$usuario->setDataCriacao(date("Y-m-d H:i:s"));

			$sql = "INSERT INTO usu_usuario (usu_id_usuario, usu_nome, usu_email, usu_senha, usu_data_criacao)
				VALUES (:id_usuario, :nome, :email, :senha, :data_criacao)";

			$stmt = $con->prepare($sql);
			$stmt->execute(array(
				'id_usuario'   => $usuario->getIdUsuario(),
				'nome' 		   => $usuario->getNome(),
				'email' 	   => $usuario->getEmail(),
				'senha' 	   => $usuario->getSenha(),
				'data_criacao' => $usuario->getDataCriacao()
			));

			return true;

		}
		catch (Exception $e) 
		{

			return false;

		}
	}

	public static function proxIdUsuario($con)
	{
		try 
		{
			$sql = "SELECT max(usu_id_usuario) FROM usu_usuario";

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

	public static function insertRecorde($con, MDRecorde $recorde)
	{
		try 
		{

			date_default_timezone_set("America/Sao_Paulo");

			$recorde->setIdRecorde(self::proxIdRecorde($con));
			$recorde->setData(date("Y-m-d H:i:s"));

			$sql = "INSERT INTO rec_recorde (rec_id_recorde, rec_pontos, rec_qnt_linha, rec_data, rec_id_usuario)
				VALUES (:id_recorde, :pontos, :qnt_linha, :data, :id_usuario)";

			$stmt = $con->prepare($sql);
			$stmt->execute(array(
				'id_recorde' => $recorde->getIdRecorde(),
				'pontos' 	 => $recorde->getPontos(),
				'qnt_linha'  => $recorde->getQntLinha(),
				'data' 	     => $recorde->getData(),
				'id_usuario' => $recorde->getIdUsuario()
			));

			return true;

		}
		catch (Exception $e) 
		{

			return false;

		}
	}

	public static function proxIdRecorde($con)
	{
		try 
		{
			$sql = "SELECT max(rec_id_recorde) FROM rec_recorde";

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
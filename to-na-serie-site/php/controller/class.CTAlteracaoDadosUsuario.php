<?php 

require_once __ROOT__.'/php/model/class.MDAlteracaoDadosUsuario.php';

/**
* 
*/
class CTAlteracaoDadosUsuario
{
	public static function insertAlteracaoDadosUsuario($con, MDAlteracaoDadosUsuario $alteracao_dados_usuario)
	{
		try 
		{
			date_default_timezone_set("America/Sao_Paulo");

			$sql = "INSERT INTO adu_alteracao_dados_usuario (adu_id_usuario, adu_data_alteracao, adu_id_usuario_alterou)
				VALUES (:id_usuario, :data_alteracao, :id_usuario_alterou)";

			$stmt = $con->prepare($sql);
			$stmt->execute(array(
				'id_usuario' => $alteracao_dados_usuario->getIdUsuario(),
				'data_alteracao' => date("Y-m-d H:i:s"),
				'id_usuario_alterou' => $alteracao_dados_usuario->getIdUsuarioAlterou()
			));

			return true;

		}
		catch (Exception $e) 
		{

			return false;
			
		}
	}
}

?>
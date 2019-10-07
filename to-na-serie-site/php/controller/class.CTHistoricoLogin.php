<?php 

require_once __ROOT__.'/php/model/class.MDHistoricoLogin.php';

/**
* 
*/
class CTHistoricoLogin
{

	public static function selectHistoricoLogin($con)
	{
		try 
		{
			$historico_login = array();
			$sql = "SELECT * FROM htl_historico_login ORDER BY htl_data_login";

			foreach ($con->query($sql) as $row) {
				$historico_login[] = new MDHistoricoLogin($row);
			}

			return $historico_login;

		}
		catch (Exception $e) 
		{

			return false;
			
		}
	}

	public static function insertHistoricoLogin($con, MDHistoricoLogin $historico_login)
	{
		try 
		{
			date_default_timezone_set("America/Sao_Paulo");
			
			$sql = "INSERT INTO htl_historico_login (htl_id_usuario, htl_data_login, htl_data_logout, htl_ip_login, htl_user_agent)
				VALUES (:id_usuario, :data_login, :data_logout, :ip_login, :user_agent)";
			$stmt = $con->prepare($sql);
			$stmt->execute(array(
				'id_usuario' => $historico_login->getIdUsuario(),
				'data_login' => $historico_login->getDataLogin();
				'data_logout' => date("Y-m-d H:i:s");
				'ip_login' => $historico_login->getIpLogin();
				'user_agent' => $historico_login->getUserAgent();
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
<?php

require_once __ROOT__.'/php/model/class.MDNivelAcesso.php';

/**
* 
*/
class CTNivelAcesso
{
	public static function selectNiveisAcesso($con)
	{
		try 
		{
			$nivel_acesso = array();
			$sql = "SELECT * FROM nva_nivel_acesso ORDER BY nva_nome";

			foreach ($con->query($sql) as $row) {
				$nivel_acesso[] = new MDNivelAcesso($row);
			}

			return $nivel_acesso;

		}
		catch (Exception $e) 
		{

			return false;
			
		}
	}

	public static function selectNivelAcesso($con, $id)
	{
		try 
		{
			$sql = "SELECT * FROM nva_nivel_acesso WHERE nva_id_nivel_acesso = $id";

			$stmt = $con->query($sql);
			$row = $stmt->fetch();

			$nivel_acesso = new MDNivelAcesso($row);

			$stmt = $row = null;

			return $nivel_acesso;

		}
		catch (Exception $e) 
		{

			return false;
			
		}
	}
}

?>
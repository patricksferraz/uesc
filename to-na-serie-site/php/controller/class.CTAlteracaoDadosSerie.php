<?php 

require_once __ROOT__.'/php/model/class.MDAlteracaoDadosSerie.php';

/**
* 
*/
class CTAlteracaoDadosSerie
{
	public static function insertAlteracaoDadosSerie($con, MDAlteracaoDadosSerie $alteracao_dados_serie)
	{
		try 
		{
			date_default_timezone_set("America/Sao_Paulo");

			$sql = "INSERT INTO adu_alteracao_dados_serie (adu_id_serie, adu_data_alteracao, adu_id_usuario_alterou)
				VALUES (:id_serie, :data_alteracao, :id_usuario_alterou)";

			$stmt = $con->prepare($sql);
			$stmt->execute(array(
				'id_serie' => $alteracao_dados_serie->getIdSerie(),
				'data_alteracao' => date("Y-m-d H:i:s"),
				'id_usuario_alterou' => $alteracao_dados_serie->getIdUsuarioAlterou()
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
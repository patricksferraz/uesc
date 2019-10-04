<?php 

require_once __ROOT__.'/php/model/class.MDEmissora.php';

/**
* 
*/
class CTEmissora
{	
	public static function selectEmissoras($con)
	{
		try 
		{
			$emissora = array();
			$sql = "SELECT * FROM emi_emissora ORDER BY emi_nome";

			foreach ($con->query($sql) as $row) {
				$emissora[] = new MDEmissora($row);
			}

			return $emissora;

		}
		catch (Exception $e) 
		{

			return false;
			
		}
	}

	public static function selectEmissora($con, $id)
	{
		try 
		{
			$sql = "SELECT * FROM emi_emissora WHERE emi_id_emissora = $id";

			$stmt = $con->query($sql);
			$row = $stmt->fetch();

			$emissora = new MDEmissora($row);

			$stmt = $row = null;

			return $emissora;

		}
		catch (Exception $e) 
		{

			return false;
			
		}
	}

	public static function insertUpdateEmissora($con, $id_usuario_logado, MDEmissora $emissora)
	{
		try 
		{

			date_default_timezone_set("America/Sao_Paulo");
			
			if ($emissora->getIdEmissora() == null)
			{

				$emissora->setIdEmissora(self::proxId($con));
				$emissora->setDataCadastro(date("Y-m-d H:i:s"));
				$emissora->setIdUsuarioCadastrou($id_usuario_logado);
				
				$sql = "INSERT INTO emi_emissora (emi_id_emissora, emi_nome, emi_sigla, emi_pagina_oficial, emi_data_cadastro, emi_id_usuario_cadastrou)
					VALUES (:id_emissora, :nome, :sigla, :pagina_oficial, :data_cadastro, :id_usuario_cadastrou)";
			}
			else
			{
				$sql = "UPDATE emi_emissora SET emi_id_emissora = id_emissora, emi_nome = nome, emi_sigla = sigla, emi_pagina_oficial = pagina_oficial, emi_data_cadastro = data_cadastro, emi_id_usuario_cadastrou = id_usuario_cadastrou
					WHERE emi_id_emissora = ".$emissora->getIdEmissora();
			}

			$stmt = $con->prepare($sql);
			$stmt->execute(array(
				'id_emissora' => $emissora->getIdEmissora(),
				'nome' => $emissora->getNome(),
				'sigla' => $emissora->getSigla(),
				'pagina_oficial' => $emissora->getPaginaOficial(),
				'data_cadastro' => $emissora->getDataCadastro(),
				'id_usuario_cadastrou' => $emissora->getIdUsuarioCadastrou()
			));

			return false;

		}
		catch (Exception $e) 
		{

			return "Já existe emissora cadastrada com este nome";
			
		}
	}

	public static function proxId($con)
	{
		try 
		{
			$sql = "SELECT max(emi_id_emissora) FROM emi_emissora";

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
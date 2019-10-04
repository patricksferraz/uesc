<?php 

require_once __ROOT__.'/php/model/class.MDIdioma.php';

/**
* 
*/
class CTIdioma
{
	public static function selectIdiomas($con)
	{
		try 
		{
			$idioma = array();
			$sql = "SELECT * FROM idm_idioma ORDER BY idm_nome";

			foreach ($con->query($sql) as $row) {
				$idioma[] = new MDIdioma($row);
			}

			return $idioma;

		}
		catch (Exception $e) 
		{

			return false;
			
		}
	}

	public static function selectIdioma($con, $id)
	{
		try 
		{
			$sql = "SELECT * FROM idm_idioma WHERE idm_id_idioma = $id";

			$stmt = $con->query($sql);
			$row = $stmt->fetch();

			$idioma = new MDIdioma($row);

			$stmt = $row = null;

			return $idioma;

		}
		catch (Exception $e) 
		{

			return false;
			
		}
	}

	public static function insertUpdateIdioma($con, $id_usuario_logado, MDIdioma $idioma)
	{
		try 
		{

			date_default_timezone_set("America/Sao_Paulo");
			
			if ($idioma->getIdIdioma() == null)
			{

				$idioma->setIdIdioma(self::proxId($con));
				$idioma->setDataCadastro(date("Y-m-d H:i:s"));
				$idioma->setIdUsuarioCadastrou($id_usuario_logado);
				
				$sql = "INSERT INTO idm_idioma (idm_id_idioma, idm_nome, idm_data_cadastro, idm_id_usuario_cadastrou 				)
					VALUES (:id_idioma, :nome, :data_cadastro, :id_usuario_cadastrou)";
			}
			else
			{
				$sql = "UPDATE idm_idioma SET idm_id_idioma = :id_idioma, idm_nome = :nome, idm_data_cadastro = :data_cadastro, idm_id_usuario_cadastrou = :id_usuario_cadastrou
					WHERE idm_id_idioma = ".$idioma->getIdIdioma();
			}

			$stmt = $con->prepare($sql);
			$stmt->execute(array(
				'id_idioma' => $idioma->getIdIdioma(),
				'nome' => $idioma->getNome(),
				'data_cadastro' => $idioma->getDataCadastro(),
				'id_usuario_cadastrou' => $idioma->getIdUsuarioCadastrou()
			));

			return false;

		}
		catch (Exception $e) 
		{

			return "Já existe idioma cadastrado com este nome";
			
		}
	}

	public static function proxId($con)
	{
		try 
		{
			$sql = "SELECT max(idm_id_idioma) FROM idm_idioma";

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
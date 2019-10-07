<?php 

require_once __ROOT__.'/php/model/class.MDGenero.php';

/**
* 
*/
class CTGenero
{
    public static function selectGeneros($con)
	{
		try 
		{
			$genero = array();
			$sql = "SELECT * FROM gnr_genero ORDER BY gnr_nome";

			foreach ($con->query($sql) as $row) {
				$genero[] = new MDGenero($row);
			}

			return $genero;

		}
		catch (Exception $e) 
		{

			return false;
			
		}
	}

	public static function selectGenero($con, $id)
	{
		try 
		{
			$sql = "SELECT * FROM gnr_genero WHERE gnr_id_genero = $id";

			$stmt = $con->query($sql);
			$row = $stmt->fetch();

			$genero = new MDGenero($row);

			$stmt = $row = null;

			return $genero;

		}
		catch (Exception $e) 
		{

			return false;
			
		}
	}

	public static function insertUpdateGenero($con, $id_usuario_logado, MDGenero $genero)
	{
		try 
		{

			date_default_timezone_set("America/Sao_Paulo");
			
			if ($genero->getIdGenero() == null)
			{

				$genero->setIdGenero(self::proxId($con));
				$genero->setDataCadastro(date("Y-m-d H:i:s"));
				$genero->setIdUsuarioCadastrou($id_usuario_logado);
				
				$sql = "INSERT INTO gnr_genero (gnr_id_genero, gnr_nome, gnr_data_cadastro, gnr_id_usuario_cadastrou)
					VALUES (:id_genero, :nome, :data_cadastro, :id_usuario_cadastrou)";
			}
			else
			{
				$sql = "UPDATE gnr_genero SET gnr_id_genero = :id_genero, gnr_nome = :nome, gnr_data_cadastro = :data_cadastro, gnr_id_usuario_cadastrou = :id_usuario_cadastrou
					WHERE gnr_id_genero = ".$genero->getIdGenero();
			}

			$stmt = $con->prepare($sql);
			$stmt->execute(array(
				'id_genero' => $genero->getIdGenero(),
				'nome' => $genero->getNome(),
				'data_cadastro' => $genero->getDataCadastro(),
				'id_usuario_cadastrou' => $genero->getIdUsuarioCadastrou()
			));

			return false;

		}
		catch (Exception $e) 
		{

			return "Já existe genero cadastrado com este nome";
			
		}
	}

	public static function proxId($con)
	{
		try 
		{
			$sql = "SELECT max(gnr_id_genero) FROM gnr_genero";

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
<?php 

require_once __ROOT__.'/php/model/class.MDCategoriaPremio.php';

/**
* 
*/
class CTCategoriaPremio
{
	public static function selectCategoriasPremio($con)
	{
		try 
		{
			$categoria_premio = array();
			$sql = "SELECT * FROM ctp_categoria_premio ORDER BY ctp_nome";

			foreach ($con->query($sql) as $row) {
				$categoria_premio[] = new MDCategoriaPremio($row);
			}

			return $categoria_premio;

		}
		catch (Exception $e) 
		{

			return false;
			
		}
	}

	public static function selectCategoriaPremio($con, $id)
	{
		try 
		{
			$sql = "SELECT * FROM ctp_categoria_premio WHERE ctp_id_categoria_premio = $id";

			$stmt = $con->query($sql);
			$row = $stmt->fetch();

			$categoria_premio = new MDCategoriaPremio($row);

			$stmt = $row = null;

			return $categoria_premio;

		}
		catch (Exception $e) 
		{

			return false;
			
		}
	}

	public static function insertUpdateCategoriaPremio($con, $id_usuario_logado, MDCategoriaPremio $categoria_premio)
	{
		try 
		{

			date_default_timezone_set("America/Sao_Paulo");
			
			if ($categoria_premio->getIdCategoriaPremio() == null)
			{

				$categoria_premio->setIdCategoriaPremio(self::proxId($con));
				$categoria_premio->setDataCadastro(date("Y-m-d H:i:s"));
				$categoria_premio->setIdUsuarioCadastrou($id_usuario_logado);
				
				$sql = "INSERT INTO ctp_categoria_premio (ctp_id_categoria_premio, ctp_nome, ctp_data_cadastro, ctp_id_usuario_cadastrou 				)
					VALUES (:id_categoria_premio, :nome, :data_cadastro, :id_usuario_cadastrou)";
			}
			else
			{
				$sql = "UPDATE ctp_categoria_premio SET ctp_id_categoria_premio = :id_categoria_premio, ctp_nome = :nome, ctp_data_cadastro = :data_cadastro, ctp_id_usuario_cadastrou = :id_usuario_cadastrou
					WHERE ctp_id_categoria_premio = ".$categoria_premio->getIdCategoriaPremio();
			}

			$stmt = $con->prepare($sql);
			$stmt->execute(array(
				'id_categoria_premio' => $categoria_premio->getIdCategoriaPremio(),
				'nome' => $categoria_premio->getNome(),
				'data_cadastro' => $categoria_premio->getDataCadastro(),
				'id_usuario_cadastrou' => $categoria_premio->getIdUsuarioCadastrou()
			));

			return false;

		}
		catch (Exception $e) 
		{

			return "Já existe categoria cadastrada com este nome";
			
		}
	}

	public static function proxId($con)
	{
		try 
		{
			$sql = "SELECT max(ctp_id_categoria_premio) FROM ctp_categoria_premio";

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
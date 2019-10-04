<?php 

require_once __ROOT__.'/php/model/class.MDPessoa.php';

/**
* 
*/
class CTPessoa
{
    public static function selectPessoas($con)
	{
		try 
		{
			$pessoa = array();
			$sql = "SELECT * FROM pes_pessoa ORDER BY pes_nome";

			foreach ($con->query($sql) as $row) {
				$pessoa[] = new MDPessoa($row);
			}

			return $pessoa;

		}
		catch (Exception $e) 
		{

			return false;
			
		}
	}

	public static function selectPessoa($con, $id)
	{
		try 
		{
			$sql = "SELECT * FROM pes_pessoa WHERE pes_id_pessoa = $id";

			$stmt = $con->query($sql);
			$row = $stmt->fetch();

			$pessoa = new MDPessoa($row);

			$stmt = $row = null;

			return $pessoa;

		}
		catch (Exception $e) 
		{

			return false;
			
		}
	}

	public static function insertUpdatePessoa($con, $id_usuario_logado, MDPessoa $pessoa)
	{
		try 
		{

			date_default_timezone_set("America/Sao_Paulo");
			
			if ($pessoa->getIdPessoa() == null)
			{

				$pessoa->setIdPessoa(self::proxId($con));
				$pessoa->setDataCadastro(date("Y-m-d H:i:s"));
				$pessoa->setIdUsuarioCadastrou($id_usuario_logado);
				
				$sql = "INSERT INTO pes_pessoa (pes_id_pessoa, pes_nome, pes_id_pais, pes_data_cadastro, pes_id_usuario_cadastrou)
					VALUES (:id_pessoa, :nome, :id_pais, :data_cadastro, :id_usuario_cadastrou)";
			}
			else
			{
				$sql = "UPDATE pes_pessoa SET pes_id_pessoa = :id_pessoa, pes_nome = :nome, pes_id_pais = :id_pais, pes_data_cadastro = :data_cadastro, pes_id_usuario_cadastrou = :id_usuario_cadastrou
					WHERE pes_id_pessoa = ".$pessoa->getIdPessoa();
			}

			$stmt = $con->prepare($sql);
			$stmt->execute(array(
				'id_pessoa' => $pessoa->getIdPessoa(),
				'nome' => $pessoa->getNome(),
				'id_pais' => $pessoa->getIdPais(),
				'data_cadastro' => $pessoa->getDataCadastro(),
				'id_usuario_cadastrou' => $pessoa->getIdUsuarioCadastrou()
			));

			return false;

		}
		catch (Exception $e) 
		{

			return "Já existe uma pessoa cadastrada com estas informações";
			
		}
	}

	public static function proxId($con)
	{
		try 
		{
			$sql = "SELECT max(pes_id_pessoa) FROM pes_pessoa";

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
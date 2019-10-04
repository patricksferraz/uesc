<?php 

require_once __ROOT__.'/php/model/class.MDPremiacao.php';

/**
* 
*/
class CTPremiacao
{
	public static function selectPremiacoes($con)
	{
		try 
		{
			$premiacao = array();
			$sql = "SELECT * FROM prm_premiacao ORDER BY prm_nome";

			foreach ($con->query($sql) as $row) {
				$premiacao[] = new MDPremiacao($row);
			}

			return $premiacao;

		}
		catch (Exception $e) 
		{

			return false;
			
		}
	}

	public static function selectPremiacao($con, $id)
	{
		try 
		{
			$sql = "SELECT * FROM prm_premiacao WHERE prm_id_premiacao = $id";

			$stmt = $con->query($sql);
			$row = $stmt->fetch();

			$premiacao = new MDPremiacao($row);

			$stmt = $row = null;

			return $premiacao;

		}
		catch (Exception $e) 
		{

			return false;
			
		}
	}

	public static function insertUpdatePremiacao($con, $id_usuario_logado, MDPremiacao $premiacao)
	{
		try 
		{

			date_default_timezone_set("America/Sao_Paulo");
			
			if ($premiacao->getIdPremiacao() == null)
			{

				$premiacao->setIdPremiacao(self::proxId($con));
				$premiacao->setDataCadastro(date("Y-m-d H:i:s"));
				$premiacao->setIdUsuarioCadastrou($id_usuario_logado);
				
				$sql = "INSERT INTO prm_premiacao (prm_id_premiacao, prm_nome, prm_sigla, prm_id_pais, prm_descricao, prm_data_cadastro, prm_id_usuario_cadastrou)
					VALUES (:id_premiacao, :nome, :sigla, :id_pais, :descricao, :data_cadastro, :id_usuario_cadastrou)";
			}
			else
			{
				$sql = "UPDATE prm_premiacao SET prm_id_premiacao = :id_premiacao, prm_nome = :nome, prm_sigla = :sigla, prm_id_pais = :id_pais, prm_descricao = :descricao, prm_data_cadastro = :data_cadastro, prm_id_usuario_cadastrou = :id_usuario_cadastrou
					WHERE prm_id_premiacao = ".$premiacao->getIdPremiacao();
			}

			$stmt = $con->prepare($sql);
			$stmt->execute(array(
				'id_premiacao' => $premiacao->getIdPremiacao(),
				'nome' => $premiacao->getNome(),
				'sigla' => $premiacao->getSigla(),
				'id_pais' => $premiacao->getIdPais(),
				'descricao' => $premiacao->getDescricao(),
				'data_cadastro' => $premiacao->getDataCadastro(),
				'id_usuario_cadastrou' => $premiacao->getIdUsuarioCadastrou()
			));

			return false;

		}
		catch (Exception $e) 
		{

			return "Já existe premiação cadastrada com este nome";
			
		}
	}

	public static function proxId($con)
	{
		try 
		{
			$sql = "SELECT max(prm_id_premiacao) FROM prm_premiacao";

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
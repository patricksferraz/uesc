<?php 

require_once __ROOT__.'/php/model/class.MDTipoParticipacao.php';

/**
* 
*/
class CTTipoParticipacao
{
	private $id_tipo_participacao;
    private $nome;
    private $data_cadastro;
    private $id_usuario_cadastrou;
	
	public static function selectTiposParticipacao($con)
	{
		try 
		{
			$tipo_participacao = array();
			$sql = "SELECT * FROM tpp_tipo_participacao ORDER BY tpp_nome";

			foreach ($con->query($sql) as $row) {
				$tipo_participacao[] = new MDTipoParticipacao($row);
			}

			return $tipo_participacao;

		}
		catch (Exception $e) 
		{

			return false;
			
		}
	}

	public static function selectTipoParticipacao($con, $id)
	{
		try 
		{
			$sql = "SELECT * FROM tpp_tipo_participacao WHERE tpp_id_tipo_participacao = $id";

			$stmt = $con->query($sql);
			$row = $stmt->fetch();

			$tipo_participacao = new MDTipoParticipacao($row);

			$stmt = $row = null;

			return $tipo_participacao;

		}
		catch (Exception $e) 
		{

			return false;
			
		}
	}

	public static function insertUpdateTipoParticipacao($con, $id_usuario_logado, MDTipoParticipacao $tipo_participacao)
	{
		try 
		{

			date_default_timezone_set("America/Sao_Paulo");
			
			if ($tipo_participacao->getIdTipoParticipacao() == null)
			{

				$tipo_participacao->setIdTipoParticipacao(self::proxId($con));
				$tipo_participacao->setDataCadastro(date("Y-m-d H:i:s"));
				$tipo_participacao->setIdUsuarioCadastrou($id_usuario_logado);
				
				$sql = "INSERT INTO tpp_tipo_participacao (tpp_id_tipo_participacao, tpp_nome, tpp_data_cadastro, tpp_id_usuario_cadastrou)
					VALUES (:id_tipo_participacao, :nome, :data_cadastro, :id_usuario_cadastrou)";
			}
			else
			{
				$sql = "UPDATE tpp_tipo_participacao SET tpp_id_tipo_participacao = :id_tipo_participacao, tpp_nome = :nome, tpp_data_cadastro = :data_cadastro, tpp_id_usuario_cadastrou = :id_usuario_cadastrou
					WHERE tpp_id_tipo_participacao = ".$tipo_participacao->getIdTipoParticipacao();
			}

			$stmt = $con->prepare($sql);
			$stmt->execute(array(
				'id_tipo_participacao' => $tipo_participacao->getIdTipoParticipacao(),
				'nome' => $tipo_participacao->getNome(),
				'data_cadastro' => $tipo_participacao->getDataCadastro(),
				'id_usuario_cadastrou' => $tipo_participacao->getIdUsuarioCadastrou()
			));

			return false;

		}
		catch (Exception $e) 
		{

			return "Já existe um tipo de participação cadastrado com este nome";
			
		}
	}

	public static function proxId($con)
	{
		try 
		{
			$sql = "SELECT max(tpp_id_tipo_participacao) FROM tpp_tipo_participacao";

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
<?php 

require_once __ROOT__.'/php/model/class.MDPais.php';

/**
* 
*/
class CTPais
{
	public static function selectPaises($con)
	{
		try 
		{
			$pais = array();
			$sql = "SELECT * FROM pas_pais ORDER BY pas_nome";

			foreach ($con->query($sql) as $row) {
				$pais[] = new MDPais($row);
			}

			return $pais;

		}
		catch (Exception $e) 
		{

			return false;
			
		}
	}

	public static function selectPais($con, $id)
	{
		try 
		{
			$sql = "SELECT * FROM pas_pais WHERE pas_id_pais = $id";

			$stmt = $con->query($sql);
			$row = $stmt->fetch();

			$pais = new MDPais($row);

			$stmt = $row = null;

			return $pais;

		}
		catch (Exception $e) 
		{

			return false;
			
		}
	}

	public static function insertUpdatePais($con, $id_usuario_logado, MDPais $pais)
	{
		try 
		{

			date_default_timezone_set("America/Sao_Paulo");
			
			if ($pais->getIdPais() == null)
			{

				$pais->setIdPais(self::proxId($con));
				$pais->setDataCadastro(date("Y-m-d H:i:s"));
				$pais->setIdUsuarioCadastrou($id_usuario_logado);
				
				$sql = "INSERT INTO pas_pais (pas_id_pais, pas_nome, pas_nome_imagem, pas_tamanho_imagem, pas_tipo_imagem, pas_imagem, pas_data_cadastro, pas_id_usuario_cadastrou)
					VALUES (:id_pais, :nome, :nome_imagem, :tamanho_imagem, :tipo_imagem, :imagem, :data_cadastro, :id_usuario_cadastrou)";
			}
			else
			{
				$sql = "UPDATE pas_pais SET pas_id_pais = :id_pais, pas_nome = :nome, pas_nome_imagem = :nome_imagem, pas_tamanho_imagem = :tamanho_imagem, pas_tipo_imagem = :tipo_imagem, pas_imagem = :imagem, pas_data_cadastro = :data_cadastro, pas_id_usuario_cadastrou = :id_usuario_cadastrou
					WHERE pas_id_pais = ".$pais->getIdPais();
			}

			$stmt = $con->prepare($sql);
			$stmt->execute(array(
				'id_pais' => $pais->getIdPais(),
				'nome' => $pais->getNome(),
				'nome_imagem' => $pais->getNomeImagem(),
				'tamanho_imagem' => $pais->getTamanhoImagem(),
				'tipo_imagem' => $pais->getTipoImagem(),
				'imagem' => $pais->getImagem(),
				'data_cadastro' => $pais->getDataCadastro(),
				'id_usuario_cadastrou' => $pais->getIdUsuarioCadastrou()
			));

			return false;

		}
		catch (Exception $e) 
		{

			return "Já existe país cadastrado com este nome";
			
		}
	}

	public static function proxId($con)
	{
		try 
		{
			$sql = "SELECT max(pas_id_pais) FROM pas_pais";

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
<?php 

require_once __ROOT__.'/php/model/class.MDClassificacaoEtaria.php';

/**
* 
*/
class CTClassificacaoEtaria
{

	public static function selectClassificacoesEtarias($con)
	{
		try 
		{
			$classificacao_etaria = array();
			$sql = "SELECT * FROM cle_classificacao_etaria ORDER BY cle_descricao";

			foreach ($con->query($sql) as $row) {
				$classificacao_etaria[] = new MDClassificacaoEtaria($row);
			}

			return $classificacao_etaria;

		}
		catch (Exception $e) 
		{

			return false;
			
		}
	}

	public static function selectClassificacaoEtaria($con, $id)
	{
		try 
		{
			$sql = "SELECT * FROM cle_classificacao_etaria WHERE cle_id_classificacao_etaria = $id";

			$stmt = $con->query($sql);
			$row = $stmt->fetch();

			$classificacao_etaria = new MDClassificacaoEtaria($row);

			$stmt = $row = null;

			return $classificacao_etaria;

		}
		catch (Exception $e) 
		{

			return false;
			
		}
	}

	public static function insertUpdateClassificacaoEtaria($con, $id_usuario_logado, MDClassificacaoEtaria $classificacao_etaria)
	{
		try 
		{

			date_default_timezone_set("America/Sao_Paulo");
			
			if ($classificacao_etaria->getIdClassificacaoEtaria() == null)
			{
				/*$duplicidade = self::existeDuplicidade($con, $classificacao_etaria->getDescricao());

				if ($duplicidade)
					return $duplicidade;*/

				$classificacao_etaria->setIdClassificacaoEtaria(self::proxId($con));
				$classificacao_etaria->setDataCadastro(date("Y-m-d H:i:s"));
				$classificacao_etaria->setIdUsuarioCadastrou($id_usuario_logado);
				
				$sql = "INSERT INTO cle_classificacao_etaria (cle_id_classificacao_etaria, cle_descricao, cle_nome_imagem, cle_tamanho_imagem, cle_tipo_imagem, cle_imagem, cle_data_cadastro, cle_id_usuario_cadastrou)
					VALUES (:id_classificacao_etaria, :descricao, :nome_imagem, :tamanho_imagem, :tipo_imagem, :imagem, :data_cadastro, :id_usuario_cadastrou)";
			}
			else
			{
				$sql = "UPDATE cle_classificacao_etaria SET cle_id_classificacao_etaria = :id_classificacao_etaria, cle_descricao = :descricao, cle_nome_imagem = :nome_imagem, cle_tamanho_imagem = :tamanho_imagem, cle_tipo_imagem = :tipo_imagem, cle_imagem = :imagem, cle_data_cadastro = :data_cadastro, cle_id_usuario_cadastrou = :id_usuario_cadastrou
					WHERE cle_id_classificacao_etaria = ".$classificacao_etaria->getIdClassificacaoEtaria();
			}

			$stmt = $con->prepare($sql);
			$stmt->execute(array(
				'id_classificacao_etaria' => $classificacao_etaria->getIdClassificacaoEtaria(),
				'descricao' => $classificacao_etaria->getDescricao(),
				'nome_imagem' => $classificacao_etaria->getNomeImagem(),
				'tamanho_imagem' => $classificacao_etaria->getTamanhoImagem(),
				'tipo_imagem' => $classificacao_etaria->getTipoImagem(),
				'imagem' => $classificacao_etaria->getImagem(),
				'data_cadastro' => $classificacao_etaria->getDataCadastro(),
				'id_usuario_cadastrou' => $classificacao_etaria->getIdUsuarioCadastrou()
			));

			return false;

		}
		catch (Exception $e) 
		{

			return "Já existe classificação etária cadastrada com esta descrição";
			
		}
	}
/*
	public static function existeDuplicidade($con, $descricao)
	{
		try 
		{
			$msg_erro = false;

			$sql = "SELECT * FROM cle_classificacao_etaria WHERE cle_descricao = $descricao";

			$stmt = $con->query($sql);
			$qnt_row = $stmt->rowCount();

			if ($qnt_row)
			{
				$msg_erro = "Já existe classificação etária cadastrada com esta descrição";
			}

			$stmt = $qnt_row = null;

			return $msg_erro;

		}
		catch (Exception $e) 
		{

			return false;
			
		}
	}
*/
	public static function proxId($con)
	{
		try 
		{
			$sql = "SELECT max(cle_id_classificacao_etaria) FROM cle_classificacao_etaria";

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
<?php 

require_once __ROOT__.'/php/model/class.MDSerie.php';
require_once __ROOT__.'/php/funs_php.php';
require_once __ROOT__.'/php/controller/class.CTAlteracaoDadosSerie.php';

/**
* 
*/
class CTSerie
{
	
	public static function validarDadosCadastroSerie($p, $f)
	{
		$t = array();

		$t[] = esta_setado($p, 'nId');
		$t[] = esta_setado($p, 'tTituloOriginal');
		$t[] = esta_setado($p, 'tTituloPortugues');
		$t[] = esta_setado($p, 'dDataEstreia');
		$t[] = esta_setado($p, 'dDataFim');
		$t[] = esta_setado($p, 'sEmissora');
		$t[] = esta_setado($p, 'sPais');
		$t[] = esta_setado($p, 'sIdioma');
		$t[] = esta_setado($p, 'sClassificacaoIndicativa');
		$t[] = esta_setado($p, 'taSinopse');

		if ($f && !empty($f['fImg']['tmp_name']))
		{
			$img_nome = $f['fImg']['name'];
			$img_tamanho = $f['fImg']['size'];
			$img_tipo = $f['fImg']['type'];
			$img = $f['fImg']['tmp_name'];
			
			if ($img != 'none')
			{
				$fp = fopen($img, "rb");
				$conteudo = fread($fp, $img_tamanho);
				$conteudo = addslashes($conteudo);
				fclose($fp);

				$t[] = $img_nome;
				$t[] = $img_tamanho;
				$t[] = $img_tipo;
				$t[] = $conteudo;
			}

		}
		else
		{
			$t[] = null;
			$t[] = null;
			$t[] = null;
			$t[] = null;
		}

		$t[] = esta_setado($p, 'data_cadastro');
		$t[] = esta_setado($p, 'rStatus');
		$t[] = esta_setado($p, 'id_usuario_cadastrou');

	    if (!$temp = esta_setado($p, 'validacao_cadastro'))
	    	$t[] = 0;
	    else
	    	$t[] = $temp;

	    $t[] = esta_setado($p, 'data_validacao');
	    $t[] = esta_setado($p, 'id_usuario_validou');
	    
		return $t;
	}

	public static function selectSeries($con)
	{
		try 
		{
			$serie = array();
			$sql = "SELECT * FROM ser_series ORDER BY ser_id_serie";

			foreach ($con->query($sql) as $row) {
				$serie[] = new MDSerie($row);
			}

			return $serie;

		}
		catch (Exception $e) 
		{

			return false;
			
		}
	}

	public static function selectSerie($con, $nome)
	{
		try 
		{
			$serie = array();
			$sql = "SELECT * FROM ser_serie WHERE ser_titulo_original LIKE :nome OR ser_titulo_portugues LIKE :nome";

			$stmt = $con->prepare($sql);
			$stmt->execute(array('nome' => "%$nome%"));
			$row = $stmt->fetchAll();

			foreach ($row as $r) {
				$serie[] = new MDSerie($r);
			}

			$stmt = $row = null;

			return $serie;

		}
		catch (Exception $e) 
		{

			return false;
			
		}
	}

	public static function insertUpdateSerie($con, $id_usuario_logado, MDSerie $serie)
	{
		try 
		{

			$duplicidade = array();
			date_default_timezone_set("America/Sao_Paulo");

			if ($serie->getIdSerie() == null)
			{
				$duplicidade = self::existeDuplicidade($con, $serie->getTituloOriginal(), $serie->getTituloPortugues());

				if (count($duplicidade))
					return $duplicidade;

				$serie->setIdSerie(self::proxId($con));
				$serie->setDataCadastro(date("Y-m-d H:i:s"));

				if (isset($id_usuario_logado))
					$serie->setIdUsuarioCadastrou($id_usuario_logado);
				else
					$serie->setIdUsuarioCadastrou($serie->getIdUsuario());
				
				$sql = "INSERT INTO ser_serie (ser_id_serie, ser_titulo_original, ser_titulo_portugues, ser_data_estreia, ser_data_fim, ser_id_emissora, ser_id_pais, ser_id_idioma, ser_id_classificacao_etaria, ser_sinopse, ser_nome_imagem, ser_tamanho_imagem, ser_tipo_imagem, ser_imagem_cabecalho, ser_data_cadastro, ser_status, ser_id_usuario_cadastrou, ser_validacao_cadastro, ser_data_validacao, ser_id_usuario_validou)
					VALUES (:id_serie, :titulo_original, :titulo_portugues, :data_estreia, :data_fim, :id_emissora, :id_pais, :id_idioma, :id_classificacao_etaria, :sinopse, :nome_imagem, :tamanho_imagem, :tipo_imagem, :imagem_cabecalho, :data_cadastro, :status, :id_usuario_cadastrou, :validacao_cadastro, :data_validacao, :id_usuario_validou)";
			}
			else
			{
				$sql = "UPDATE ser_serie SET ser_id_serie = :id_serie, ser_titulo_original = :titulo_original, ser_titulo_portugues = :titulo_portugues, ser_data_estreia = :data_estreia, ser_data_fim = :data_fim, ser_id_emissora = :id_emissora, ser_id_pais = :id_pais, ser_id_idioma = :id_idioma, ser_id_classificacao_etaria = :id_classificacao_etaria, ser_sinopse = :sinopse, ser_nome_imagem = :nome_imagem, ser_tamanho_imagem = :tamanho_imagem, ser_tipo_imagem = :tipo_imagem, ser_imagem_cabecalho = :imagem_cabecalho, ser_data_cadastro = :data_cadastro, ser_status = :status, ser_id_usuario_cadastrou = :id_usuario_cadastrou, ser_validacao_cadastro = :validacao_cadastro, ser_data_validacao = :data_validacao, ser_id_usuario_validou = :id_usuario_validou
					WHERE ser_id_serie = ".$serie->getIdSerie();
			}

			$stmt = $con->prepare($sql);
			$stmt->execute(array(
				'id_serie' => $serie->getIdSerie(),
				'titulo_original' => $serie->getTituloOriginal(),
				'titulo_portugues' => $serie->getTituloPortugues(),
				'data_estreia' => $serie->getDataEstreia(),
				'data_fim' => $serie->getDataFim(),
				'id_emissora' => $serie->getIdEmissora(),
				'id_pais' => $serie->getIdPais(),
				'id_idioma' => $serie->getIdIdioma(),
				'id_classificacao_etaria' => $serie->getIdClassificacaoEtaria(),
				'sinopse' => $serie->getSinopse(),
				'nome_imagem' => $serie->getNomeImagem(),
				'tamanho_imagem' => $serie->getTamanhoImagem(),
				'tipo_imagem' => $serie->getImagemCabecalho(),
				'imagem_cabecalho' => $serie->getImagemCabecalho(),
				'data_cadastro' => $serie->getDataCadastro(),
				'status' => $serie->getStatus(),
				'id_usuario_cadastrou' => $serie->getIdUsuarioCadastrou(),
				'validacao_cadastro' => $serie->getValidacaoCadastro(),
				'data_validacao' => $serie->getDataValidacao(),
				'id_usuario_validou' => $serie->getIdUsuarioValidou()
			));
			
			$alteracao_dados_serie = new MDAlteracaoDadosSerie(array(
				$serie->getIdSerie(),
				null,
				$id_usuario_logado
			));

			CTAlteracaoDadosSerie::insertAlteracaoDadosSerie($con, $alteracao_dados_serie);

			return $duplicidade;

		}
		catch (Exception $e) 
		{
			$msg[] = $e->getMessage();
			return $msg;
			
		}
	}

	public static function existeDuplicidade($con, $titulo_original, $titulo_portugues)
	{
		try 
		{
			$msg_erro = array();


			$sql = "SELECT * FROM ser_serie WHERE ser_titulo_original LIKE :titulo_original AND ser_titulo_portugues LIKE :titulo_portugues";
			$stmt = $con->prepare($sql);

			$stmt->execute(array('titulo_original' => $titulo_original, "titulo_portugues" => '%'));
			$qnt_row = $stmt->rowCount();
			if ($qnt_row)
				$msg_erro[] = "Já existe série cadastrada com esse título original";

			$stmt->execute(array('titulo_portugues' => $titulo_portugues, "titulo_original" => '%'));
			$qnt_row = $stmt->rowCount();
			if ($qnt_row)
				$msg_erro[] = "Já existe série cadastrada com esse título em português";

			$stmt = $qnt_row = null;

			return $msg_erro;

		}
		catch (Exception $e) 
		{

			$msg[] = $e->getMessage();
			return $msg;
			
		}
	}

	public static function proxId($con)
	{
		try 
		{
			$sql = "SELECT max(ser_id_serie) FROM ser_serie";

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
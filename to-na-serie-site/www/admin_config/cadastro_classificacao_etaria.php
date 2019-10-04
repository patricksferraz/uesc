<?php

require_once 'cabeca_admin_config.php';
require_once __ROOT__.'/php/controller/class.CTClassificacaoEtaria.php';

$s = &$_SESSION;
$p = &$_POST;
$f = &$_FILES;

$id_usuario = $s['id_usuario'];

$con = con_db_tns();

if ($p && $f)
{
	$id = $p['nId'];
	$descricao = $p['tDescricao'];
	$img_nome = $f['fImg']['name'];
	$img_tamanho = $f['fImg']['size'];
	$img_tipo = $f['fImg']['type'];
	$img = $f['fImg']['tmp_name'];

	if ( $img != "none" )
	{
		$fp = fopen($img, "rb");
		$conteudo = fread($fp, $img_tamanho);
		$conteudo = addslashes($conteudo);
		fclose($fp);
	}

	$dados_classificacao = array($id, $descricao, $img_nome, $img_tamanho, $img_tipo, $conteudo, null, null);

	$obj_classificacao_etaria = new MDClassificacaoEtaria($dados_classificacao);
	$erro = CTClassificacaoEtaria::insertUpdateClassificacaoEtaria($con, $id_usuario, $obj_classificacao_etaria);
}

?>
<!DOCTYPE html>
<html lang="pt-br">
<head>
	<?php require_once '../cabeca.php'; ?>
    <!--Título-->
    <title>Tô na Série - Cadastro de Classificação Etária</title>
</head>
<body>

	<?php require_once '../cabecalho.php'; ?>

	<div class="container-fluid padding-top">
		<div class="row">

			<?php require_once 'menu_admin_config.php'; ?>

			<div class="col-sm-10 panel panel-orange margin-top">

				<form action="<?php echo $_SERVER['PHP_SELF'] ?>" method="POST" accept-charset="utf-8" enctype="multipart/form-data">

					<div class="row">
						<h3 class="col-md-12">Cadastro de Classificação Etária</h3>
					</div>

					<div class="row">
						<p class="col-md-12 text-danger">* Campos obrigatórios</p>
					</div>

					<div class="row margin-top">
						<div id="alert" class="col-md-12">
						
						<?php if (isset($erro) && !$erro):
						?>

							<div class="alert alert-success" role="alert">
								<span class="fa fa-check-circle" aria-hidden="true"></span>
								<span class="sr-only">Sucesso:</span>
								Dados inseridos com sucesso
							</div>
						
						<?php elseif (isset($erro) && $erro): ?>

							<div class="alert alert-danger" role="alert">
								<span class="fa fa-exclamation-circle" aria-hidden="true"></span>
								<span class="sr-only">Erro:</span>
								<?php echo $erro; ?>
							</div>

						<?php endif; ?>

						</div>
					</div>

					<div class="row">
						<div class="form-group col-md-2">
							<input name="nId" type="hidden" class="form-control" value="<?php echo esta_setado($p, 'nId'); ?>" readonly>
						</div>
					</div>

					<div class="row">
						<div class="form-group col-md-8">
							<label for="tDescricao" class="control-label">Descrição <span class="text-danger">*</span>:</label>
							<input name="tDescricao" type="text" class="form-control" value="<?php echo esta_setado($p, 'tDescricao'); ?>" required>
						</div>
						<div class="form-group col-md-4">
							<label for="fImg" class="control-label">Ícone <span class="text-danger">*</span> <span title="Será o ícone de exibição para classificar a série" class="fa fa-info-circle"></span>:</label>
							<input name="fImg" type="file" class="form-control" value="<?php if (isset($f['fImg'])) echo $f['fImg']; ?>" required>
						</div>
					</div>

					<div class="row">
						<div class="form-group col-md-12 text-right">
							<button type="reset" class="btn btn-warning"><span class="fa fa-minus-circle" aria-hidden="true"></span> Limpar</button>
							<button type="submit" class="btn btn-warning"><span class="fa fa-save" aria-hidden="true"></span> Salvar</button>
						</div>
					</div>

				</form>

				<?php 
					$classificacao_etaria = CTClassificacaoEtaria::selectClassificacoesEtarias($con);

					if ($classificacao_etaria):
				?>
					
					<form action="<?php echo $_SERVER['PHP_SELF'] ?>" method="POST" accept-charset="utf-8">

						<div class="table-responsive">
							<table class="table table-hover">
								<thead>
									<tr>
										<th>ID</th>
										<th>Descrição</th>
										<th>Imagem</th>
										<th></th>
										<th></th>
									</tr>
								</thead>
								<tbody>
									<?php
										
										foreach ($classificacao_etaria as $cle) {
									        echo "<tr onclick=''>
												<td>".$cle->getIdClassificacaoEtaria()."</td>
												<td>".$cle->getDescricao()."</td>
												<td>EXIBIR IMAGEM</td>

												<td><button name='b-edit' value='".$cle->getIdClassificacaoEtaria()."' type='submit' class='btn-link'><span class='fa fa-edit text-primary' aria-hidden='true'></span></button></td>
												<td><button name='b-delete' value='".$cle->getIdClassificacaoEtaria()."' type='submit' class='btn-link'><span class='fa fa-trash-o text-danger' aria-hidden='true'></span></button></td>
											</tr>";
									    }

									?>
								</tbody>
							</table>
						</div>
					</form>

				<?php endif; ?>

			</div>
	
		</div>
	</div>

	<?php 
	require_once '../rodape.php';
	$con = null;
	?>

</body>
</html>
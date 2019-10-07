<?php

require_once 'cabeca_admin_config.php';
require_once __ROOT__.'/php/controller/class.CTPais.php';

$s = &$_SESSION;
$p = &$_POST;
$f = &$_FILES;

$id_usuario = $s['id_usuario'];

$con = con_db_tns();

if ($p && $f)
{
	$id = $p['nId'];
	$nome = $p['tNome'];
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

	$dados_pais = array($id, $nome, $img_nome, $img_tamanho, $img_tipo, $conteudo, null, null);

	$obj_pais = new MDPais($dados_pais);
	$erro = CTPais::insertUpdatePais($con, $id_usuario, $obj_pais);
}

?>
<!DOCTYPE html>
<html lang="pt-br">
<head>
	<?php require_once '../cabeca.php'; ?>
    <!--Título-->
    <title>Tô na Série - Cadastro de País</title>
</head>
<body>

	<?php require_once '../cabecalho.php'; ?>

	<div class="container-fluid padding-top">
		<div class="row">

			<?php require_once 'menu_admin_config.php'; ?>

			<div class="col-sm-10 panel panel-orange margin-top">

				<form action="<?php echo $_SERVER['PHP_SELF'] ?>" method="POST" accept-charset="utf-8" enctype="multipart/form-data">

					<div class="row">
						<h3 class="col-md-12">Cadastro de País</h3>
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
							<label for="tNome" class="control-label">Nome <span class="text-danger">*</span>:</label>
							<input name="tNome" type="text" class="form-control" value="<?php echo esta_setado($p, 'tNome'); ?>" required>
						</div>
						<div class="form-group col-md-4">
							<label for="fImg" class="control-label">Bandeira <span class="text-danger">*</span> <span title="Será o ícone de exibição para informar o país" class="fa fa-info-circle"></span>:</label>
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
					$pais = CTPais::selectPaises($con);

					if ($pais):
				?>
					
					<form action="<?php echo $_SERVER['PHP_SELF'] ?>" method="POST" accept-charset="utf-8">

						<div class="table-responsive">
							<table class="table table-hover">
								<thead>
									<tr>
										<th>ID</th>
										<th>Nome</th>
										<th>Imagem</th>
										<th></th>
										<th></th>
									</tr>
								</thead>
								<tbody>
									<?php
										
										foreach ($pais as $pas) {
									        echo "<tr onclick=''>
												<td>".$pas->getIdPais()."</td>
												<td>".$pas->getNome()."</td>
												<td>EXIBIR IMAGEM</td>

												<td><button name='b-edit' value='".$pas->getIdPais()."' type='submit' class='btn-link'><span class='fa fa-edit text-primary' aria-hidden='true'></span></button></td>
												<td><button name='b-delete' value='".$pas->getIdPais()."' type='submit' class='btn-link'><span class='fa fa-trash-o text-danger' aria-hidden='true'></span></button></td>
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
<?php

require_once 'cabeca_admin_config.php';
require_once __ROOT__.'/php/controller/class.CTEmissora.php';

$s = &$_SESSION;
$p = &$_POST;

$id_usuario = $s['id_usuario'];

$con = con_db_tns();

if ($p)
{
	$id = $p['nId'];
	$nome = $p['tNome'];
	$sigla = $p['tSigla'];
	$pagina_oficial = $p['tPgOficial'];

	$dados_emissora = array($id, $nome, $sigla, $pagina_oficial, null, null);

	$obj_emissora = new MDEmissora($dados_emissora);
	$erro = CTEmissora::insertUpdateEmissora($con, $id_usuario, $obj_emissora);
}

?>
<!DOCTYPE html>
<html lang="pt-br">
<head>
	<?php require_once '../cabeca.php'; ?>
    <!--Título-->
    <title>Tô na Série - Cadastro de Emissora</title>
</head>
<body>

	<?php require_once '../cabecalho.php'; ?>

	<div class="container-fluid padding-top">
		<div class="row">

			<?php require_once 'menu_admin_config.php'; ?>

			<div class="col-sm-10 panel panel-orange margin-top">
				<form action="<?php echo $_SERVER['PHP_SELF'] ?>" method="POST" accept-charset="utf-8">

					<div class="row">
						<h3 class="col-md-12">Cadastro de Emissora</h3>
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
						<div class="form-group col-md-5">
							<label for="tNome" class="control-label">Nome <span class="text-danger">*</span>:</label>
							<input name="tNome" type="text" class="form-control" value="<?php echo esta_setado($p, 'tNome'); ?>" required>
						</div>
						<div class="form-group col-md-2">
							<label for="tSigla" class="control-label">Sigla <span class="text-danger">*</span>:</label>
							<input name="tSigla" type="text" class="form-control" value="<?php echo esta_setado($p, 'tSigla'); ?>" required>
						</div>
						<div class="col-md-5">
							<label>Página Oficial:</label>
							<div class="input-group">
								<span for="tPgOficial" class="input-group-addon">http://www.</span>
								<input name="tPgOficial" type="text" class="form-control" value="<?php echo esta_setado($p, 'tPgOficial'); ?>">
							</div>
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
					$emissora = CTEmissora::selectEmissoras($con);

					if ($emissora):
				?>
					
					<form action="<?php echo $_SERVER['PHP_SELF'] ?>" method="POST" accept-charset="utf-8">

						<div class="table-responsive">
							<table class="table table-hover">
								<thead>
									<tr>
										<th>ID</th>
										<th>Nome</th>
										<th>Sigla</th>
										<th>Página Oficial</th>
										<th></th>
										<th></th>
									</tr>
								</thead>
								<tbody>
									<?php
										
										foreach ($emissora as $emi) {
									        echo "<tr onclick=''>
												<td>".$emi->getIdEmissora()."</td>
												<td>".$emi->getNome()."</td>
												<td>".$emi->getSigla()."</td>
												<td>".$emi->getPaginaOficial()."</td>

												<td><button name='b-edit' value='".$emi->getIdEmissora()."' type='submit' class='btn-link'><span class='fa fa-edit text-primary' aria-hidden='true'></span></button></td>
												<td><button name='b-delete' value='".$emi->getIdEmissora()."' type='submit' class='btn-link'><span class='fa fa-trash-o text-danger' aria-hidden='true'></span></button></td>
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
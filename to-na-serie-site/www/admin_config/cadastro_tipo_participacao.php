<?php

require_once 'cabeca_admin_config.php';
require_once __ROOT__.'/php/controller/class.CTTipoParticipacao.php';

$s = &$_SESSION;
$p = &$_POST;

$id_usuario = $s['id_usuario'];

$con = con_db_tns();

if ($p)
{
	$id = $p['nId'];
	$nome = $p['tNome'];

	$dados_tipo_participacao = array($id, $nome, null, null);

	$obj_tipo_participacao = new MDTipoParticipacao($dados_tipo_participacao);
	$erro = CTTipoParticipacao::insertUpdateTipoParticipacao($con, $id_usuario, $obj_tipo_participacao);
}

?>
<!DOCTYPE html>
<html lang="pt-br">
<head>
	<?php require_once '../cabeca.php'; ?>
    <!--Título-->
    <title>Tô na Série - Cadastro de Tipo de Participação</title>
</head>
<body>

	<?php require_once '../cabecalho.php'; ?>

	<div class="container-fluid padding-top">
		<div class="row">

			<?php require_once 'menu_admin_config.php'; ?>

			<div class="col-sm-10 panel panel-orange margin-top">

				<form action="" method="POST" accept-charset="utf-8">
					<div class="row">
						<h3 class="col-md-12">Cadastro de Tipo de Participação</h3>
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
						<div class="form-group col-md-6">
							<label for="tNome" class="control-label">Tipo de Participação <span class="text-danger">*</span>:</label>
							<input name="tNome" type="text" class="form-control" value="<?php echo esta_setado($p, 'tNome'); ?>" required>
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
				$tipo_participacao = CTTipoParticipacao::selectTiposParticipacao($con);

				if ($tipo_participacao):
				?>
					
					<form action="<?php echo $_SERVER['PHP_SELF'] ?>" method="POST" accept-charset="utf-8">

						<div class="table-responsive">
							<table class="table table-hover">
								<thead>
									<tr>
										<th>ID</th>
										<th>Nome</th>
										<th></th>
										<th></th>
									</tr>
								</thead>
								<tbody>
									<?php
										
									foreach ($tipo_participacao as $tpp) {
								        echo "<tr onclick=''>
											<td>".$tpp->getIdTipoParticipacao()."</td>
											<td>".$tpp->getNome()."</td>

											<td><button name='b-edit' value='".$tpp->getIdTipoParticipacao()."' type='submit' class='btn-link'><span class='fa fa-edit text-primary' aria-hidden='true'></span></button></td>
											<td><button name='b-delete' value='".$tpp->getIdTipoParticipacao()."' type='submit' class='btn-link'><span class='fa fa-trash-o text-danger' aria-hidden='true'></span></button></td>
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
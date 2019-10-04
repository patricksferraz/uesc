<?php

require_once 'cabeca_admin_config.php';
require_once __ROOT__.'/php/controller/class.CTPremiacao.php';
require_once __ROOT__.'/php/funs_php.php';

$s = &$_SESSION;
$p = &$_POST;

$id_usuario = $s['id_usuario'];

$con = con_db_tns();

if ($p)
{
	$id = $p['nId'];
	$nome = $p['tNome'];
	$sigla = esta_setado($p, 'tSigla');
	$pais = $p['sPais'];
	$descricao = esta_setado($p, 'taDescricao');

	$dados_premiacao = array($id, $nome, $sigla, $pais, $descricao, null, null);

	$obj_premiacao = new MDPremiacao($dados_premiacao);
	$erro = CTPremiacao::insertUpdatePremiacao($con, $id_usuario, $obj_premiacao);
}

?>
<!DOCTYPE html>
<html lang="pt-br">
<head>
	<?php require_once '../cabeca.php'; ?>
    <!--Título-->
    <title>Tô na Série - Cadastro de Premiação</title>
</head>
<body>

	<?php require_once '../cabecalho.php'; ?>

	<div class="container-fluid padding-top">
		<div class="row">

			<?php require_once 'menu_admin_config.php'; ?>

			<div class="col-sm-10 panel panel-orange margin-top">
				<form action="" method="POST" accept-charset="utf-8">

					<div class="row">
						<h3 class="col-md-12">Cadastro de Premiação</h3>
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
						<div class="form-group col-md-3">
							<label for="tSigla" class="control-label">Sigla:</label>
							<input name="tSigla" type="text" class="form-control" value="<?php echo esta_setado($p, 'tSigla'); ?>" required>
						</div>
						<div class="form-group col-md-4">
							<label for="sPais" class="control-label">País <span class="text-danger">*</span>:</label>
							<select name="sPais" class="form-control">

								<?php 
								$temp_pais = esta_setado($p, 'sPais');
								if ($temp_pais): 

									$pais = CTPais::selectPais($con, $temp_pais);
								?>

									<option value="<?php echo $pais->getIdPais();?>"><?php echo $pais->getNome(); ?></option>
								
								<?php else: ?>

									<option value=""></option>
								
								<?php endif;
								
								$paises = CTPais::selectPaises($con);
								foreach ($paises as $pas) {
									echo "<option value='".$pas->getIdPais()."'>".$pas->getNome()."</option>";
								}

								?>

							</select>
						</div>
					</div>

					<div class="row">
						<div class="form-group col-md-12">
							<label for="taDescricao" class="control-label">Descrição:</label>
							<textarea name="taDescricao" class="form-control" rows="5" maxlength="500"><?php echo esta_setado($p, 'taDescricao'); ?></textarea>
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
					$premiacao = CTPremiacao::selectPremiacoes($con);

					if ($premiacao):
				?>
					
					<form action="<?php echo $_SERVER['PHP_SELF'] ?>" method="POST" accept-charset="utf-8">

						<div class="table-responsive">
							<table class="table table-hover">
								<thead>
									<tr>
										<th>ID</th>
										<th>Nome</th>
										<th>Sigla</th>
										<th>País</th>
										<th>Descrição</th>
										<th></th>
										<th></th>
									</tr>
								</thead>
								<tbody>
									<?php
										
										foreach ($premiacao as $prm) {
									        echo "<tr onclick=''>
												<td>".$prm->getIdPremiacao()."</td>
												<td>".$prm->getNome()."</td>
												<td>".$prm->getSigla()."</td>";
											
											$pais_temp = CTPais::selectPais($con, $prm->getIdPais());

											echo"<td>".$pais_temp->getNome()."</td>
												<td>".$prm->getDescricao()."</td>

												<td><button name='b-edit' value='".$prm->getIdPremiacao()."' type='submit' class='btn-link'><span class='fa fa-edit text-primary' aria-hidden='true'></span></button></td>
												<td><button name='b-delete' value='".$prm->getIdPremiacao()."' type='submit' class='btn-link'><span class='fa fa-trash-o text-danger' aria-hidden='true'></span></button></td>
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
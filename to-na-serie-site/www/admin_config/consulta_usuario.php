<?php

require_once 'cabeca_admin_config.php';
require_once __ROOT__.'/php/controller/class.CTUsuario.php';

$p = &$_POST;

$con = con_db_tns();

?>
<!DOCTYPE html>
<html lang="pt-br">
<head>
	<?php require_once '../cabeca.php'; ?>
    <!--Título-->
    <title>Tô na Série - Consulta de Usuário</title>
</head>
<body>

	<?php require_once '../cabecalho.php'; ?>

	<div class="container-fluid padding-top">
		<div class="row">

			<?php require_once 'menu_admin_config.php'; ?>

			<div class="col-sm-10 panel panel-orange margin-top">
				<form action="<?php echo $_SERVER['PHP_SELF'] ?>" method="POST" accept-charset="utf-8">

					<div class="row">
						<h3 class="col-md-12">Consulta de Usuário</h3>
					</div>

					<?php 
					if ($p && isset($p['tUsuario']))
						$usuario = CTUsuario::selectUsuario($con, $p['tUsuario']);
					else
						$usuario = CTUsuario::selectUsuarios($con);

					if (!$usuario):
					?>
						<div class="alert alert-danger" role="alert">
							<span class="fa fa-exclamation-circle" aria-hidden="true"></span>
							<span class="sr-only">Erro:</span>
							Nenhum registro encontrado
						</div>

					<?php endif; ?>

					<div class="row">
						<div class="col-md-6">
							<div class="input-group">
								<input type="text" name="tUsuario" class="form-control" value="<?php echo esta_setado($p, 'tUsuario'); ?>"" placeholder="Buscar usuário">
								<span class="input-group-btn">
									<button class="btn btn-default" type="submit"><span class="fa fa-search" aria-hidden="true"></span></button>
								</span>
							</div>
						</div>
					</div>

				</form>

				<?php
				if ($usuario):
				?>
					
					<form class="margin-top" action="<?php echo $_SERVER['PHP_SELF'] ?>" method="POST" accept-charset="utf-8">

						<div class="table-responsive">
							<table class="table table-hover">
								<thead>
									<tr>
										<th>ID</th>
										<th>Nome</th>
										<th>Apelido</th>
										<th>E-mail</th>
										<th>Qnt. Seguidores</th>
										<th></th>
										<th></th>
									</tr>
								</thead>
								<tbody>
									<?php
										
										foreach ($usuario as $usr) {
									        echo "<tr onclick=''>
												<td>".$usr->getIdUsuario()."</td>
												<td>".$usr->getNome()."</td>
												<td>".$usr->getApelido()."</td>
												<td>".$usr->getEmail()."</td>
												<td>SEGUIDORES</td>

												<td><button name='b-edit' value='".$usr->getIdUsuario()."' type='submit' class='btn-link'><span class='fa fa-edit text-primary' aria-hidden='true'></span></button></td>
												<td><button name='b-delete' value='".$usr->getIdUsuario()."' type='submit' class='btn-link'><span class='fa fa-trash-o text-danger' aria-hidden='true'></span></button></td>
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
<?php

require_once 'cabeca_admin_config.php';

?>
<!DOCTYPE html>
<html lang="pt-br">
<head>
	<?php require_once '../cabeca.php'; ?>
    <!--Título-->
    <title>Tô na Série - Consulta de Série</title>
</head>
<body>

	<?php require_once '../cabecalho.php'; ?>

	<div class="container-fluid padding-top">
		<div class="row">

			<?php require_once 'menu_admin_config.php'; ?>

			<div class="col-sm-10 panel panel-orange margin-top">
				<form action="" method="POST" accept-charset="utf-8">
					<div class="row">
						<h3 class="col-md-12">Consulta de Série</h3>
					</div>

					<div class="row">
							<label class="control-label col-md-12">Nome da Série:</label>
							<div class="col-md-6">
								<div class="input-group">
									<input type="text" class="form-control" placeholder="Buscar série">
									<span class="input-group-btn">
										<button class="btn btn-default" type="button"><span class="fa fa-search" aria-hidden="true"></span></button>
									</span>
								</div>
							</div>
						</div>

						<div class="row">
							<div class="col-md-12">
								<div class="table-responsive margin-top">
									<table class="table table-hover">
										<thead>
											<tr>
												<th>#</th>
												<th>Nome</th>
												<th>Qnt. seguidores</th>
											</tr>
										</thead>
										<tbody>
											<tr class="cursor-hand" onclick="">
												<td>1</td>
												<td>Game of Thrones</td>
												<td>1.900</td>
											</tr>
											<tr class="cursor-hand" onclick="">
												<td>2</td>
												<td>The Walking Dead</td>
												<td>1543</td>
											</tr>
											<tr class="cursor-hand" onclick="">
												<td>3</td>
												<td>The Big Bang</td>
												<td>788</td>
											</tr>
										</tbody>
									</table>
								</div>
							</div>
						</div>
				</form>
			</div>
		
		</div>
	</div>

	<?php require_once '../rodape.php'; ?>

</body>
</html>
<!DOCTYPE html>
<html lang="pt-br">
<head>
	<?php require_once '../cabeca.php'; ?>
    <!--Título-->
    <title>Tô na Série - Ranking das Séries</title>
</head>
<body>

	<?php require_once '../cabecalho.php'; ?>

	<div class="container-fluid padding-top">
		<div class="row">

			<?php require_once 'menu_busca_serie.php'; ?>

			<div class="col-sm-3">
				<div class="thumbnail thumbnail-usuario">
					<img src="img/serie/ser_game_of_thrones.jpg" alt="Imagem Usuário" class="img-responsive">
					<div class="caption">
						<h3>Série</h3>
						<p>PRÉ VISUALIZAÇÃO DE ALGUNS DADOS DO USUÁRIO</p>
					</div>
				</div>
			</div>

			<div class="col-sm-9">
				<div class="panel panel-default">
					<div class="panel-body">
					Basic panel example
					</div>
				</div>
				<!--<div class="table-responsive margin-top">
					<table class="table table-hover">
						<thead>
							<tr>
								<th>#</th>
								<th>Nome</th>
								<th>Qnt. Séries</th>
							</tr>
						</thead>
						<tbody>
							<tr class="cursor-hand" onclick="alterarPagina('view/perfil_serie.php');">
								<td>1</td>
								<td>Patrick</td>
								<td>34</td>
							</tr>
							<tr class="cursor-hand" onclick="alterarPagina('view/perfil_serie.php');">
								<td>2</td>
								<td>Matheus</td>
								<td>23</td>
							</tr>
							<tr class="cursor-hand" onclick="alterarPagina('view/perfil_serie.php');">
								<td>3</td>
								<td>Jonas</td>
								<td>12</td>
							</tr>
						</tbody>
					</table>
				</div>-->
			</div>

		</div>
	</div>

	<?php require_once '../rodape.php'; ?>

</body>
</html>
<!DOCTYPE html>
<html lang="pt-br">
<head>
	<?php require_once '../cabeca.php'; ?>
    <!--Título-->
    <title>Tô na Série - Perfis das Séries</title>
</head>
<body>

	<?php require_once '../cabecalho.php'; ?>

	<div class="container-fluid padding-top">
		<div class="row">

			<?php require_once 'menu_busca_serie.php'; ?>

			<div class="col-xs-6 col-sm-4 col-md-2">
				<a href="www/serie/perfil/perfil_serie_dados_gerais.php" class="thumbnail">
					<img class="img-responsive" src="img/serie/ser_game_of_thrones.jpg" alt="ser_game_of_thrones">
				</a>
			</div>

			<div class="col-xs-6 col-sm-4 col-md-2">
				<a href="#" class="thumbnail">
					<img class="img-responsive" src="img/serie/ser_legends_of_tomorrow.jpg" alt="ser_legends_of_tomorrow">
				</a>
			</div>

			<div class="col-xs-6 col-sm-4 col-md-2">
				<a href="#" class="thumbnail">
					<img class="img-responsive" src="img/serie/ser_mr_robot.jpg" alt="ser_mr_robot">
				</a>
			</div>

			<div class="col-xs-6 col-sm-4 col-md-2">
				<a href="#" class="thumbnail">
					<img class="img-responsive" src="img/serie/ser_sons_of_anarchy.jpg" alt="ser_sons_of_anarchy">
				</a>
			</div>

			<div class="col-xs-6 col-sm-4 col-md-2">
				<a href="#" class="thumbnail">
					<img class="img-responsive" src="img/serie/ser_supergirl.jpg" alt="ser_supergirl">
				</a>
			</div>

			<div class="col-xs-6 col-sm-4 col-md-2">
				<a href="#" class="thumbnail">
					<img class="img-responsive" src="img/serie/ser_supernatural.jpg" alt="ser_supernatural">
				</a>
			</div>

		</div>
	</div>

	<?php require_once '../rodape.php'; ?>

</body>
</html>
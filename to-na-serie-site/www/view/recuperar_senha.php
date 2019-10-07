<!DOCTYPE html>
<html lang="pt-br">
<head>
	<?php require_once '../cabeca.php'; ?>
    <!--Título e favicon-->
    <title>Tô na Série - Recuperação de senha</title>
</head>
<body>
	<div class="container-fluid padding-top">
		<div class="row">
			<div class="col-sm-6 col-sm-offset-3 panel panel-orange">
				<form action="" method="POST" accept-charset="utf-8">
				
					<div class="row margin-top">
						<div class="col-md-12">
							<a href=""><img class="img-responsive center-block" alt="Tô na Série" src="img/logo_principal.svg"></a>
						</div>
					</div>

					<div class="row">
						<h2 class="col-md-12 text-center">Digite seu e-mail e recupere sua senha.</h2>
					</div>

					<div class="row">
						<div class="form-group col-md-12">
							<label class="control-label">Digite seu e-mail:</label>
							<input type="email" class="form-control" required>
						</div>
					</div>

					<div class="row">
						<div class="form-group col-md-12">
							<button type="submit" class="btn btn-warning pull-right"><span class="fa fa-lightbulb-o" aria-hidden="true"></span> Recuperar</button>
						</div>
					</div>

				</form>
			</div>
		</div>
	</div>
</body>
</html>
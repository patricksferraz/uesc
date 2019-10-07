<!DOCTYPE html>
<html lang="pt-br">
<head>
	<?php require_once '../cabeca.php'; ?>
    <!--Título e favicon-->
    <title>Tô na Série - Recuperação de senha</title>
</head>
<body>
	<div id="tudo">

		<div class="container-fluid padding-top">
			<div class="row">
				<div class="col-sm-4 col-sm-offset-4 panel panel-orange">
					<form action="" method="POST" accept-charset="utf-8">
						<div class="row margin-top">
							<div class="col-md-12">
								<a href=""><img class="img-responsive center-block" alt="Tô na Série" src="img/logo_principal.svg"></a>
							</div>
						</div>

						<div class="row">
							<h2 class="col-md-12 text-center">Alteração de senha</h2>
						</div>

						<div class="row">
							<div class="form-group col-md-12">
								<label class="control-label">Digite sua senha:</label>
								<input type="password" class="form-control" required>
							</div>
							<div class="form-group col-md-12">
								<label class="control-label">Digite a nova senha:</label>
								<input type="password" class="form-control" required>
							</div>
							<div class="form-group col-md-12">
								<label class="control-label">Repita a nova senha:</label>
								<input type="password" class="form-control" required>
							</div>
						</div>

						<div class="row">
							<div class="form-group col-md-12 text-right">
								<button type="submit" class="btn btn-warning"><span class="fa fa-refresh" aria-hidden="true"></span> Alterar</button>
							</div>
						</div>

					</form>
				</div>
			</div>
		</div>

	</div>	
</body>
</html>
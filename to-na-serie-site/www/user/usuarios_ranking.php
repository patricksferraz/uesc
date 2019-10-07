<?php

require_once '../dir_root.php';
require_once __ROOT__.'/php/autoload_class.php';
require_once __ROOT__.'/php/controle_acesso/conexao.php';
require_once __ROOT__.'/php/funs_php.php';
require_once __ROOT__.'/php/controller/class.CTSerie.php';

$p = &$_POST;

$con = con_db_tns();

?>
<!DOCTYPE html>
<html lang="pt-br">
<head>
	<?php require_once '../cabeca.php'; ?>
    <!--Título-->
    <title>Tô na Série - Ranking de Usuários</title>
</head>
<body>

	<?php require_once '../cabecalho.php'; ?>

	<div class="container-fluid padding-top">
		<div class="row">
					
			<?php require_once 'menu_busca_usuario.php'; ?>
			
			<div class="col-sm-3">
				<div class="thumbnail thumbnail-usuario">
					<img src="img/usuario/user.png" alt="Imagem Usuário" class="img-responsive">
					<div class="caption">
						<h3>Nick Name</h3>
						<p>PRÉ VISUALIZAÇÃO DE ALGUNS DADOS DO USUÁRIO</p>
					</div>
				</div>
			</div>


			<div class="panel panel-orange col-sm-9 margin-top">
				<?php

				if ($p && isset($p['tUsuario']))
					$usuario = CTUsuario::selectUsuario($con, $p['tUsuario']);
				else
					$usuario = CTUsuario::selectUsuarios($con);

				if (!$usuario):?>

					<div class="alert alert-danger" role="alert">
						<span class="fa fa-exclamation-circle" aria-hidden="true"></span>
						<span class="sr-only">Erro:</span>
						Nenhum registro encontrado
					</div>

				<?php else:
						
					foreach ($usuario as $usr) {
						echo "<div class='row'>
							<a>
								<div class='panel panel-default'>
									<div class='panel-body'>
									".$usr->getNome()."
									</div>
								</div>
							</a>
						</div>";
				    }

					?>
				<?php endif; ?>	
				
			</div>

		</div>
	</div>

	<?php require_once '../rodape.php'; ?>

</body>
</html>
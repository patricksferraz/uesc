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
    <title>Tô na Série - Perfis de Usuários</title>
</head>
<body>

	<?php require_once '../cabecalho.php'; ?>

	<div class="container-fluid padding-top">
		<div class="row">
					
			<?php require_once 'menu_busca_usuario.php'; 

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
					echo "<div class='col-xs-4 col-md-2'>
						<a href='www/user/perfil/perfil_user_series.php?id=".$usr->getIdUsuario()."' class='thumbnail'>
							<img class='img-responsive' src='img/usuario/admin_ferraz.jpg' alt='ser_game_of_thrones'>
						</a>
					</div>";
			    }

				?>
			<?php endif; ?>			
	
		</div>
	</div>

	<?php
	require_once '../rodape.php'; 
	$con = null;
	?>

</body>
</html>
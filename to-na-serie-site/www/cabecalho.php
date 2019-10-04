<?php
require_once 'dir_root.php';
require_once __ROOT__.'/php/controle_acesso/resgate_sessao.php';
require_once __ROOT__.'/php/controle_acesso/nvl_acesso.php';

$s = &$_SESSION;

if (esta_conectado($s))
{
	$id_usuario = $s['id_usuario'];
	$nvl_acesso = $s['id_nivel_acesso'];
	$apelido = $s['apelido'];
}

?>
<header>
	<!--Navbar-->
    <nav class="navbar navbar-default navbar-fixed-top">
		<div class="container-fluid">

			<div class="navbar-header">
				<button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#navbar-principal" aria-expanded="false">
					<span class="sr-only">Navegação Alternativa</span>
					<span class="icon-bar"></span>
					<span class="icon-bar"></span>
					<span class="icon-bar"></span>
				</button>
				<a class="navbar-brand" href=""><img class="img-responsive" alt="Tô na Série" src="img/logo_principal.svg"></a>
			</div>

			<!--Navbar Principal-->
			<div class="collapse navbar-collapse" id="navbar-principal">
				<!--Menus-->
				<ul class="nav navbar-nav">
					<li><a href="" onclick=""><span class="fa fa-home" aria-hidden="true"></span> Página Inicial</a></li>
					<li><a href="www/serie/series_perfis.php" onclick=""><span class="fa fa-tv" aria-hidden="true"></span> Séries</a></li>
					<li><a href="www/user/usuarios_perfis.php" onclick=""><span class="fa fa-users" aria-hidden="true"></span> Usuários</a></li>
				</ul>

				<ul class="nav navbar-nav navbar-right">

				<?php if (esta_conectado($s)): ?>

					<?php if (eh_administrador($nvl_acesso)): ?>
						
						<li><a href="www/admin_config/analise_estatistica.php" onclick=""><span class="fa fa-gears" aria-hidden="true"></span> Config.Admin</a></li>
						
					<?php endif; ?>					
					
					<li class="dropdown">
						<a href="#" class="dropdown-toggle" data-toggle="dropdown" role="button" aria-haspopup="true" aria-expanded="false"><span class="fa fa-user-circle"></span> <?php echo $apelido; ?> <span class="caret"></span></a>
						<ul class="dropdown-menu">
							<li><a href="www/user/perfil/perfil_user_series.php" onclick=""><span class="fa fa-vcard" aria-hidden="true"></span> Meu Perfil</a></li>
							<li><a href="www/view/alterar_senha.php" onclick=""><span class="fa fa-lock" aria-hidden="true"></span> Alterar senha</a></li>
						</ul>
					</li>
					<li><a href="php/controle_acesso/logout.php" onclick=""><span class="fa fa-sign-out" aria-hidden="true"></span> Logout</a></li>

				<?php else: ?>

					<li><a href="www/view/login.php" onclick=""><span class="fa fa-sign-in" aria-hidden="true"></span> Login</a></li>

				<?php endif; ?>

				</ul>
			</div><!--Fim Navbar Principal-->

		</div>
    </nav><!--Fim Navbar-->
</header><!-- /header -->
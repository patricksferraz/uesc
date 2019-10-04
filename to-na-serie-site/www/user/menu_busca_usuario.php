<?php
require_once __ROOT__.'/php/funs_php.php';

$p = &$_POST;
?>
<div class="nav nav-tabs nav-white col-sm-12">
	<ul class="nav navbar-nav">
		<li><a id="button_usuarios_perfis" href="www/user/usuarios_perfis.php"><span class="fa fa-id-card-o" aria-hidden="true"></span> Perfis</a></li>
		<li><a id="button_usuarios_ranking" href="www/user/usuarios_ranking.php"><span class="fa fa-diamond" aria-hidden="true"></span> Ranking</a></li>
	</ul>
	<form class="navbar-form navbar-right" action="<?php echo $_SERVER['PHP_SELF'] ?>" method="POST" accept-charset="utf-8">
		<div class="input-group">
			<input type="text" name="tUsuario" class="form-control" placeholder="Buscar usuário" value="<?php echo esta_setado($p, 'tUsuario') ?>">
			<span class="input-group-btn">
				<button class="btn btn-default" type="button"><span class="fa fa-search" aria-hidden="true"></span></button>
			</span>
		</div>
	</form>
</div>
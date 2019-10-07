<?php 

require_once __ROOT__.'/php/funs_php.php';
require_once __ROOT__.'/php/controller/class.CTUsuario.php';
require_once __ROOT__.'/php/controller/class.CTNivelAcesso.php';
require_once __ROOT__.'/php/controle_acesso/conexao.php';

$g = &$_GET;

if($g)
	$id = $g['id'];
else
	$id = $_SESSION['id_usuario'];

$con = con_db_tns();

$usr = CTUsuario::selectUsuarioId($con, $id);
$nvl_acesso = CTNivelAcesso::selectNivelAcesso($con, $usr->getIdNivelAcesso());

?>
<div class="col-sm-3">
	<div class="row">
		<div class="col-sm-12">
			<div class="thumbnail thumbnail-usuario panel panel-orange">
				<img src="img/usuario/admin_ferraz.jpg" alt="Imagem Usuário" class="img-responsive">
				<div class="caption">
					<h3><?php echo $nvl_acesso->getNome() ?></h3>
					<p><strong>Usuário:</strong>
					<br><?php echo $usr->getApelido(); ?></p>
					<p><strong>Última conexão:</strong>
					<br>01/06/2017</p>
				</div>
				<div class="list-group">
					<button onclick="location.href = 'www/user/perfil/perfil_user_series.php';" type="button" class="list-group-item"><span class="fa fa-tv" aria-hidden="true"></span> Séries</button>
					<button onclick="location.href = 'www/user/perfil/perfil_user_seguidores.php';" type="button" class="list-group-item"><span class="fa fa-eye" aria-hidden="true"></span> Seguidores</button>
					<button onclick="location.href = 'www/user/perfil/perfil_user_seguindo.php';" type="button" class="list-group-item"><span class="fa fa-address-book" aria-hidden="true"></span> Seguindo</button>
					<button onclick="location.href = 'www/user/perfil/perfil_user_notificacoes.php';" type="button" class="list-group-item"><span class="fa fa-spinner"></span> Notificações</button>
					<button onclick="location.href = 'www/user/perfil/perfil_user_ultimas_atualizacoes.php';" type="button" class="list-group-item"><span class="fa fa-globe" aria-hidden="true"></span> Últimas atualizações</button>
					<button onclick="location.href = 'www/user/perfil/perfil_user_preferencia.php';" type="button" class="list-group-item"><span class="fa fa-gear" aria-hidden="true"></span> Preferências</button>
				</div>
			</div>
		</div>
	</div>							
</div>


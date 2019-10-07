<?php

$s = &$_SESSION;

?>
<div class="col-sm-2">
	<div class="row">
		<div class="col-sm-12">
			<div class="thumbnail thumbnail-usuario panel panel-orange">
				<img src="img/usuario/admin_ferraz.jpg" alt="Imagem Usuário" class="img-responsive">
				<div class="caption">
					<h3><?php echo $s['nome_acesso']; ?></h3>
					<p><strong>Nome:</strong>
					<br><?php echo $s['apelido'] ?></p>
					<p><strong>Última conexão:</strong>
					<br>01/06/2017</p>
				</div>
				<div class="list-group">
					<div class="btn-group" role="group">
						<button type="button" class="list-group-item dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false"><span class="fa fa-pencil-square-o"></span>
						Cadastrar <div class="pull-right"><span class="caret"></span></div>
						</button>
						<ul class="dropdown-menu">
							<li><a href="www/admin_config/cadastro_serie.php"><span class="fa fa-angle-right" aria-hidden="true"></span> Série</a></li>
							<li><a href="www/admin_config/cadastro_usuario.php"><span class="fa fa-angle-right" aria-hidden="true"></span> Usuário</a></li>

							<li role="separator" class="divider"></li>
							<li class="dropdown-header">Informações p/ Séries</li>
							<li><a href="www/admin_config/cadastro_classificacao_etaria.php"><span class="fa fa-angle-right" aria-hidden="true"></span> Classificação Etária</a></li>
							<li><a href="www/admin_config/cadastro_emissora.php"><span class="fa fa-angle-right" aria-hidden="true"></span> Emissora</a></li>
							<li><a href="www/admin_config/cadastro_genero.php"><span class="fa fa-angle-right" aria-hidden="true"></span> Gênero</a></li>
							<li><a href="www/admin_config/cadastro_idioma.php"><span class="fa fa-angle-right" aria-hidden="true"></span> Idioma</a></li>

							<li role="separator" class="divider"></li>
							<li class="dropdown-header">Informações p/ Premiações</li>
							<li><a href="www/admin_config/cadastro_categoria_premio.php"><span class="fa fa-angle-right" aria-hidden="true"></span> Categoria de Prêmios</a></li>
							<li><a href="www/admin_config/cadastro_premiacao.php"><span class="fa fa-angle-right" aria-hidden="true"></span> Premiação</a></li>

							<li role="separator" class="divider"></li>
							<li class="dropdown-header">Outras Informações</li>
							<li><a href="www/admin_config/cadastro_pais.php"><span class="fa fa-angle-right" aria-hidden="true"></span> País de Origem</a></li>
							<li><a href="www/admin_config/cadastro_pessoa.php"><span class="fa fa-angle-right" aria-hidden="true"></span> Pessoa Participante de Série</a></li>
							<li><a href="www/admin_config/cadastro_tipo_participacao.php"><span class="fa fa-angle-right" aria-hidden="true"></span> Tipo de Participação na Série</a></li>
						</ul>
					</div>
					<div class="btn-group" role="group">
						<button type="button" class="list-group-item dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false"><span class="fa fa-search"></span>
						Consultar <div class="pull-right"><span class="caret"></span></div>
						</button>
						<ul class="dropdown-menu">
							<li><a href="www/admin_config/consulta_serie.php"><span class="fa fa-angle-right" aria-hidden="true"></span> Série</a></li>
							<li><a href="www/admin_config/consulta_usuario.php"><span class="fa fa-angle-right" aria-hidden="true"></span> Usuário</a></li>
						</ul>
					</div>
					<button type="button" class="list-group-item" onclick="location.href = 'www/admin_config/notificacoes_administrativas.php'"><span class="fa fa-spinner"></span> Notificações</button>
					<button type="button" class="list-group-item" onclick="location.href = 'www/admin_config/analise_estatistica.php'"><span class="fa fa-line-chart"></span> Estatística</button>
				</div>
			</div>
		</div>
	</div>							
</div>
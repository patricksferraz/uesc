<?php
require_once '../../php/Mobile_Detect.php';
$detect = new Mobile_Detect;
?>
<!DOCTYPE html>
<html lang="pt-br">
<head>
	<?php require_once "../../head.php"; ?>
</head>

<body>

	<?php require_once "../../header.php"; ?>

	<main>
		<div class="container">
			<div class="section">
				<div class="card-panel">

					<label class="right">PERLT team - Versão: 1.0</label>

					<!-- MENU DE JOGO -->
					<div class="container">
						<form action="view/jogo/partida.php" method="POST" accept-charset="utf-8">

							<div class="row">
								<div class="col s12">
									<h4 class="header center">Menu</h4>
									<div class="hr"></div>
								</div>
							</div>

							<?php
							if( $detect->isTablet() ):
							?>

								<div class="card-panel red lighten-2">
									<span class="white-text">Para uma melhor experiência no seu dispositivo, recomendamos ecolher no máximo <strong>12 linhas</strong>.</span>
								</div>

							<?php	
							elseif ( $detect->isMobile() ):
							?>

								<div class="card-panel red lighten-2">
									<span class="white-text">Para uma melhor experiência no seu dispositivo, recomendamos ecolher no máximo <strong>6 linhas</strong>.</span>
								</div>

							<?php
							endif;
							?>

							<div class="row">
								<div class="col m6 s12 center">
									<div class="switch">
										<label>
											1 Jogador
											<input id="multijogador" name="multijogador" type="checkbox">
											<span class="lever"></span>
											2 jogadores
										</label>
									</div>	
								</div>
								<div class="col m6 s12">
									<p class="range-field">
										<input type="range" name="qntLinhas" id="qntLinhas" min="5" max="15" value="5" />
										<label for="qntLinhas">Quantidade de linhas</label>
									</p>
								</div>
							</div>

							<div class="row">
								<div class="col m12">
									<input name="codJogador1" id="codJogador1" type="hidden" value="" readonly>
									<div class="input-field col s11">
										<i class="material-icons prefix">videogame_asset</i>
										<input name="nomeJogador1" id="nomeJogador1" type="text" class="validate" readonly>
										<label for="nomeJogador1">Jogador 1</label>
									</div>
									<div class="input-field col s1">
										<a class="waves-effect waves-light btn-floating modal-trigger" href="#modalJogador1"><i class="material-icons">lock_open</i></a>
									</div>
								</div>
							</div>

							<div class="row oculto">
								<input name="codJogador2" id="codJogador2" type="hidden" value="" readonly>
								<div class="col s12">
									<div class="input-field col s11">
										<i class="material-icons prefix">videogame_asset</i>
										<input name="nomeJogador2" id="nomeJogador2" type="text" class="validate" readonly>
										<label for="nomeJogador2">Jogador 2</label>
									</div>
									<div class="input-field col s1">
										<a class="waves-effect waves-light btn-floating modal-trigger" href="#modalJogador2"><i class="material-icons">lock_open</i></a>
									</div>
								</div>
							</div>

							<div class="row">
								<div class="col s6 center">
									<button onclick="location.href = 'index.php'" class="btn waves-effect waves-light" type="button">Voltar
										<i class="material-icons left">chevron_left</i>
									</button>
								</div>
								<div class="col s6 center">
									<button class="btn waves-effect waves-light" type="submit">Iniciar
										<i class="material-icons right">chevron_right</i>
									</button>
								</div>
							</div>

						</form>
					</div>
					<!-- END-MENU DE JOGO -->

					<!-- MODAL PLAY 1 -->
					<div id="modalJogador1" class="modal">
						<div class="modal-content">
							<div class="row">
								<div class="col s12">
									<h4 class="header center">Para continuar, insira os dados!</h4>
									<div class="hr"></div>
								</div>
							</div>

							<div id="alert-jogador1"></div>

							<div class="container conteudoJogador1">
								<div class="row">
									<div class="input-field col s12">
										<i class="material-icons prefix">account_circle</i>
										<input name="usrJogador1" id="usrJogador1" type="text" class="validate">
										<label for="usrJogador1">Nome do Jogador 1</label>
									</div>
									<div class="input-field col s12">
										<i class="material-icons prefix">vpn_key</i>
										<input name="senhaUsrJogador1" id="senhaUsrJogador1" type="password" class="validate">
										<label for="senhaUsrJogador1">Senha</label>
									</div>
									<div class="col s12">
										<a class="left modal-trigger" href="#modalCadastro">Cadastre-se</a>
										<a href="" class="right">Esqueceu a senha?</a>
									</div>
								</div>
							</div>
						</div>
						<div class="modal-footer conteudoJogador1">
							<button class="btn-flat modal-action modal-close waves-effect waves-light" type="button">Cancelar</button>
							<button onclick="loginJogador(this)" value="loginJogador1" class="btn-flat modal-action waves-effect waves-light" type="button">Confirmar</button>
						</div>
					</div>
					<!-- END-MODAL PLAY 1 -->

					<!-- MODAL PLAY 2 -->
					<div id="modalJogador2" class="modal">
						<div class="modal-content">
							<div class="row">
								<div class="col s12">
									<h4 class="header center">Para continuar, insira os dados!</h4>
									<div class="hr"></div>
								</div>
							</div>

							<div id="alert-jogador2"></div>

							<div class="container conteudoJogador2">
								<div class="row">
									<div class="input-field col s12">
										<i class="material-icons prefix">account_circle</i>
										<input name="usrJogador2" id="usrJogador2" type="text" class="validate">
										<label for="usrJogador2">Nome do Jogador 2</label>
									</div>
									<div class="input-field col s12">
										<i class="material-icons prefix">vpn_key</i>
										<input name="senhaUsrJogador2" id="senhaUsrJogador2" type="password" class="validate">
										<label for="senhaUsrJogador2">Senha</label>
									</div>
									<div class="col s12">
										<a class="left modal-trigger" href="#modalCadastro">Cadastre-se</a>
										<a href="" class="right">Esqueceu a senha?</a>
									</div>
								</div>
							</div>
						</div>
						<div class="modal-footer conteudoJogador2">
							<button class="btn-flat modal-action modal-close waves-effect waves-light" type="button">Cancelar</button>
							<button onclick="loginJogador(this)" value="loginJogador2" class="btn-flat modal-action waves-effect waves-light" type="button">Confirmar</button>
						</div>
					</div>
					<!-- END-MODAL PLAY 2 -->

					<!-- MODAL CADASTRO -->
					<div id="modalCadastro" class="modal">

						<div class="modal-content">
							<div class="row">
								<div class="col s12">
									<h4 class="header center">Cadastre-se para uma melhor experiência!</h4>
									<div class="hr"></div>
								</div>
							</div>

							<div id="alert-cadastro"></div>

							<div class="container conteudoCadastro">
								<div class="row">
									<div class="input-field col s12">
										<i class="material-icons prefix">account_circle</i>
										<input name="nomeUsrCadastro" id="nomeUsrCadastro" type="text" class="validate">
										<label for="nomeUsrCadastro">Nome de usuário</label>
									</div>
									<div class="input-field col s12">
										<i class="material-icons prefix">email</i>
										<input name="emailUsrCadastro" id="emailUsrCadastro" type="email" class="validate">
										<label for="emailUsrCadastro">E-mail</label>
									</div>
									<div class="input-field col s12">
										<i class="material-icons prefix">vpn_key</i>
										<input id="senhaUsrCadastro" type="password" class="validate">
										<label for="senhaUsrCadastro">Senha</label>
									</div>
									<div class="input-field col s12">
										<i class="material-icons prefix">vpn_key</i>
										<input id="rSenhaUsrCadastro" type="password" class="validate">
										<label for="rSenhaUsrCadastro">Repetir senha</label>
									</div>
								</div>
							</div>

						</div>

						<div class="modal-footer conteudoCadastro">
							<button class="btn-flat modal-action modal-close waves-effect waves-light" type="button">Cancelar</button>
							<button onclick="cadastroJogador(this);" value="cadastroJogador" class="btn-flat modal-action waves-effect waves-light" type="button">Cadastrar</button>
						</div>

					</div>
					<!-- END MODAL CADASTRO -->

				</div>
			</div>
		</div>
	</main>

	<?php require_once "../../footer.php"; ?>

</body>
</html>
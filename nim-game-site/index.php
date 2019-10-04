<!DOCTYPE html>
<html lang="pt-br">
<head>
	<?php require_once "head.php"; ?>
</head>

<body>

	<?php require_once "header.php"; ?>

	<main>
		<div class="container">
			<div class="section">
				<div class="card-panel">
					<h2 class="teal-text text-lighten-2">Seja Bem Vindo!</h2>
					<p class="flow-text text-justify">Nim é um jogo matemático de estratégia em que dois jogadores se revezam removendo objetos de montes distintos. Em cada turno, um jogador deve remover pelo menos um objeto e pode remover qualquer número de objetos, desde que todos eles provêm do mesmo monte. O objetivo do jogo é evitar ser o jogador a remover o último objeto.
					Você pode jogar contra um amigo ou contra um computador, a escolha é sua.</p>
					<div class="row">
						<div class="col s6">
							<button onclick="location.href = 'view/jogo/menu.php'" class="btn-large pulse waves-effect waves-light left" type="button">Começe a Jogar</button>
						</div>
						<div class="col s6">
							<button onclick="location.href = 'view/jogo/recorde.php'" class="btn-large waves-effect waves-light right" type="button">Recordes</button>
						</div>
					</div>
				</div>
			</div>
		</div>
	</main>

	<?php require_once "footer.php"; ?>

</body>
</html>

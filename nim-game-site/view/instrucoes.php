<!DOCTYPE html>
<html lang="pt-br">
<head>
	<?php require_once "../head.php"; ?>
</head>

<body>

	<?php require_once "../header.php"; ?>

	<main>
		<div class="container">
			<div class="section">

				<div class="row">
					<div class="col s12">
						<h4 class="header"><blockquote>Instruções</blockquote></h4>
					</div>
					<div class="col s12">
						<div class="card">
							<div class="card-content">
								<span class="card-title text-justify">
									A partida inicia pedindo a quantidade de fileiras de palitos, e em seguida mostra na tela um  diagrama com traços verticais representando as fileiras de palitos. Inicialmente a primeira fileira possui um palito e cada uma das demais fileiras possui um palito a mais que a anterior.<br>
									Em seguida os jogadores, alternadamente, indicam uma fileira e o número de palitos que devem ser removidos dela. Naturalmente, o programa não aceita uma fileira inexistente, ou uma quantidade de palitos maior do que a que está disponível naquele momento. Quando uma jogada válida é apresentada pelo jogador, o programa mostra o diagrama de palitos modificado, removidos os que foram retirados.<br>
									Perde o jogo aquele jogador que for obrigado a retirar o último palito. Caso algum jogador retire todos os palitos da última fileira existente (neste caso a estratégia para vencer seria óbvia), ele deve ser advertido de sua estupidez, e seu oponente é declarado o vencedor da partida.
								</span>
							</div>
						</div>
					</div>
				</div>

				<div class="row">

					<div class="col s12">
						<h5 class="header"><blockquote>DICAS</blockquote></h5>
						<ul class="collapsible popout" data-collapsible="accordion">
							<li class="white">
								<div class="collapsible-header"><i class="material-icons">more</i>Como vencer?</div>
								<div class="collapsible-body"><p class="text-justify flow-text">
									Uma versão de Nim é jogada - e tem importância simbólica - no filme "O Ano Passado em Marienbad" de Alain Resnais, em 1961. Um dos diálogos entre duas das personagens do filme referido relatava:<br>
									- Conheço um jogo em que eu ganho sempre.<br>
									- Se você ganha sempre não é um jogo.<br>
									- É um jogo, mas eu ganho sempre.<br><br>
									A curiosidade deste jogo é o algoritmo que existe para ganhar de seu oponente. Para vencer matematicamente, é preciso ter um conhecimento de números binários, pois é através deles que roda todo algoritmo da vitória. Este algoritmo consiste em fazer uma configuração segura nos palitos de modo que não interessa qual a jogada de seu oponente, você faz novamente a configuração, e acaba sempre vencendo. Mesmo que os dois saibam fazer este algoritmo, o que conseguir começar a desenvolvê-lo, ganha.
								</p></div>
							</li>
						</ul>
					</div>

				</div>

			</div>
		</div>
	</main>

	<?php require_once "../footer.php"; ?>

</body>
</html>

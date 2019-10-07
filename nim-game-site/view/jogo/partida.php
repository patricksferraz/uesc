<?php

$p = &$_POST;

if ($p)
{
	$qntLinhas 	  = $p['qntLinhas'];
	$nomeJogador1 = $p['nomeJogador1'];
	$nomeJogador2 = $p['nomeJogador2'];
	$codJogador1  = $p['codJogador1'];
	$codJogador2  = $p['codJogador2'];

	if(empty($codJogador1))	$nomeJogador1 = 'Anônimo_1';

	if(isset($p['multijogador']))
	{
		$multijogador = $p['multijogador'];
		if(empty($codJogador2)) $nomeJogador2 = 'Anônimo_2';
	}
	else
	{
		$multijogador = '';
		$nomeJogador2 = 'Computador';
		$codJogador2  = 1;
	}
}
else
	header('Location: menu.php');

?>

<!DOCTYPE html>
<html lang="pt-br">
<head>
	<?php require_once "../../head.php"; ?>
</head>

<body onload="inicializa(<?php echo $qntLinhas; ?>, '<?php echo $multijogador; ?>', '<?php echo $codJogador1; ?>', '<?php echo $nomeJogador1; ?>', '<?php echo $codJogador2; ?>', '<?php echo $nomeJogador2; ?>');">

	<?php require_once "../../header.php"; ?>

	<main>
		<div class="container">
			<div class="section">
				<div class="card-panel">
					
					<label class="left"><?php echo $nomeJogador1; ?> [<span id="scoreJogador1"></span>]<br> <?php echo $nomeJogador2; ?> [<span id="scoreJogador2"></span>]</label>
					<label class="right">PERLT team - Versão: 1.0</label>
					
					<div class="container">

						<div class="row">
							<div class="col s12">
								<h4 class="header center">Partida <span id="nPartida">1</span></h4>
								<div class="hr"></div>
							</div>
						</div>

						<div id="telaJogo">
							<?php
							$qntColunas = 1;

							for ($lin = 1; $lin <= $qntLinhas; $lin++, $qntColunas++)
							{
								echo '<div class="row bloco"><span class="col s1">' . $lin . '</span><span class="col s11">';

								for ($col = 1; $col <= $qntColunas; $col++)
								{
									echo '<input class="filled-in" name="bloco" type="checkbox" id="linha_' . $lin . '_' . $col . '" /><label for="linha_' . $lin . '_' . $col . '"></label>';
								}

								echo '</span></div>';
							}
							?>
						</div>

					</div>

					<label id="vezJogador" class="right"></label>

				</div>
			</div>
		</div>
	</main>

	<?php require_once "../../footer.php"; ?>

	<script type="text/javascript" src="js/jogo.js"></script>

</body>
</html>
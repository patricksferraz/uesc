<?php

require_once '../../php/dir_root.php';
require_once '../../php/conexao.php';
require_once __ROOT__.'/php/class.controlador.php';

$con = con_db_jogo_nim();

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

					<h3 class="center">Recordes</h3>
					<div class="hr"></div>

					<?php

					$recorde = Controlador::selectRecordes($con);

					if (!$recorde): ?>

					<h4 class="teal-text text-lighten-2 center">Não existem recordes armazenados</h4>

					<?php else: ?>

						<table class="striped responsive-table">
							<thead>
								<tr>
									<th>Name</th>
									<th>Pontuação</th>
									<!--<th>Modalidade</th>-->
									<th>Qnt. Linhas</th>
									<th>Data</th>
								</tr>
							</thead>

							<tbody>
								<?php
								foreach ($recorde as $rec)
								{
									if ($rec->getIdUsuario() == NULL)
										$nome_usu = "Anônimo";
									else
									{
										$nome_usu = Controlador::selectUsuario($con, (int)$rec->getIdUsuario())->getNome();
									}

									echo "<tr>
									<td>".$nome_usu."</td>
									<td>".$rec->getPontos()."</td>
									<td>".$rec->getQntLinha()."</td>
									<td>".$rec->getData()."</td>
									</tr>";
								}

								$nome_usu = null;
								$recorde  = null;
								?>
							</tbody>
						</table>

					<?php endif; ?>

					<div>
						<br><br>
						<button onclick="location.href = 'index.php'" class="btn waves-effect waves-light" type="button"><i class="material-icons left">chevron_left</i>Voltar</button>
					</div>

				</div>
			</div>
		</div>
	</main>

	<?php require_once "../../footer.php"; ?>

</body>
</html>

<?php
$con = null;
?>
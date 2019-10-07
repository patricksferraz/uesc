<?php

require_once 'cabeca_admin_config.php';
require_once __ROOT__.'/php/controller/class.CTSerie.php';

$s = &$_SESSION;
$p = &$_POST;
$f = &$_FILES;

$id_usuario = $s['id_usuario'];

$con = con_db_tns();

if ($p)
{	
	$dados_serie = CTSerie::validarDadosCadastroSerie($p, $f);
	$obj_serie = new MDSerie($dados_serie);
	$erro = CTSerie::insertUpdateSerie($con, $id_usuario, $obj_serie);
}

?>
<!DOCTYPE html>
<html lang="pt-br">
<head>
	<?php require_once '../cabeca.php'; ?>
    <!--Título-->
    <title>Tô na Série - Cadastro de Série</title>
</head>
<body onload="$('[name = dados-gerais]').click();">

	<?php require_once '../cabecalho.php'; ?>

	<div class="container-fluid padding-top">
		<div class="row">

			<?php require_once 'menu_admin_config.php'; ?>

			<div class="col-sm-10 panel panel-orange margin-top">

				<div class="row">
					<h3 class="col-md-12">Cadastro de Série</h3>
				</div>

				<div class="row">
					<p class="col-md-12 text-danger">* Campos obrigatórios</p>
				</div>

				<div class="row margin-top">
					<div id="alert" class="col-md-12">
					
					<?php if (isset($erro) && !$erro):
					?>

						<div class="alert alert-success" role="alert">
							<span class="fa fa-check-circle" aria-hidden="true"></span>
							<span class="sr-only">Sucesso:</span>
							Dados inseridos com sucesso
						</div>
					
					<?php elseif (isset($erro) && $erro): ?>

						<div class="alert alert-danger" role="alert">
							<?php foreach ($erro as $e): ?>

								<span class="fa fa-exclamation-circle" aria-hidden="true"></span>
								<span class="sr-only">Erro:</span>
								<?php echo $e; ?><br>

							<?php endforeach; ?>
						</div>

					<?php endif; ?>

					</div>
				</div>

				<div class="row">
					<div class="col-md-12">
						<ul id="sub-menu-cadastro-serie" class="nav nav-tabs nav-tabs-sub">
							<li role="presentation"><a name="dados-gerais" onclick="exibirDadosSubMenu('sub-menu-cadastro-serie', this.name);" href="www/admin_config/cadastro_serie.php#">Dados gerais</a></li>
							<li role="presentation"><a name="generos" onclick="exibirDadosSubMenu('sub-menu-cadastro-serie', this.name);" href="www/admin_config/cadastro_serie.php#">Gêneros</a></li>
							<li role="presentation"><a name="direcao" onclick="exibirDadosSubMenu('sub-menu-cadastro-serie', this.name);" href="www/admin_config/cadastro_serie.php#">Direção</a></li>
							<li role="presentation"><a name="elenco" onclick="exibirDadosSubMenu('sub-menu-cadastro-serie', this.name);" href="www/admin_config/cadastro_serie.php#">Elenco</a></li>
							<li role="presentation"><a name="premiacoes" onclick="exibirDadosSubMenu('sub-menu-cadastro-serie', this.name);" href="www/admin_config/cadastro_serie.php#">Premiações</a></li>
							<li role="presentation"><a name="temporadas" onclick="exibirDadosSubMenu('sub-menu-cadastro-serie', this.name);" href="www/admin_config/cadastro_serie.php#">Temporadas</a></li>
							<li role="presentation"><a name="episodios" onclick="exibirDadosSubMenu('sub-menu-cadastro-serie', this.name);" href="www/admin_config/cadastro_serie.php#">Episódios</a></li>
						</ul>
					</div>
				</div>

				<form class="div-oculta" id="dados-gerais" action="<?php echo $_SERVER['PHP_SELF'] ?>" method="POST" accept-charset="utf-8" enctype="multipart/form-data">

					<div class="row">
						<div class="form-group col-md-2">
							<input name="nId" type="hidden" class="form-control" value="<?php echo esta_setado($p, 'nId'); ?>" readonly>
						</div>
					</div>

					<div class="row">
						<div class="form-group col-md-6">
							<label for="rStatus" class="control-label">Status:</label><br>
							<label class="radio-inline">
								<input type="radio" name="rStatus" value="A" <?php if(!($temp = esta_setado($p, 'rStatus')) || $temp == 'A') echo 'checked';?> required> Ativa
							</label>
							<label class="radio-inline">
								<input type="radio" name="rStatus" value="F" <?php if(esta_setado($p, "rStatus") == "F") echo "checked";?>> Finalizada
							</label>
							<label class="radio-inline">
								<input type="radio" name="rStatus" value="C" <?php if(esta_setado($p, "rStatus") == "C") echo "checked";?>> Cancelada
							</label>
						</div>

						<div class="form-group col-md-6">
							<label for="fImg" class="control-label">Capa da Página:</label>
							<input name="fImg" type="file" class="form-control">
						</div>
					</div>

					<div class="row">
						<div class="form-group col-md-6">
							<label for="tTituloOriginal" class="control-label">Título original:</label>
							<input name="tTituloOriginal" type="text" class="form-control" minlength="3" value="<?php echo esta_setado($p, 'tTituloOriginal'); ?>" required>
						</div>

						<div class="form-group col-md-6">
							<label for="tTituloPortugues" class="control-label">Título português:</label>
							<input name="tTituloPortugues" type="text" class="form-control" minlength="3" value="<?php echo esta_setado($p, 'tTituloPortugues'); ?>" required>
						</div>
					</div>

					<div class="row">
						<div class="form-group col-md-4">
							<label for="sEmissora" class="control-label">Emissora:</label>
							<select name="sEmissora" id="sEmissora" class="form-control" required>
								<?php 
								$temp_emissora = esta_setado($p, 'sEmissora');
								if ($temp_emissora): 

									$emissora = CTEmissora::selectEmissora($con, $temp_emissora);
								?>

									<option value="<?php echo $emissora->getIdEmissora();?>"><?php echo $emissora->getSigla(); ?></option>
								
								<?php else: ?>

									<option value=""></option>
								
								<?php endif;
								
								$emissoras = CTEmissora::selectEmissoras($con);
								foreach ($emissoras as $emi) {
									echo "<option value='".$emi->getIdEmissora()."'>".$emi->getSigla()."</option>";
								}

								?>
							</select>
						</div>

						<div class="form-group col-md-4">
							<label for="dDataEstreia" class="control-label">Data Estreia:</label>
							<input name="dDataEstreia" type="date" class="form-control" value="<?php echo esta_setado($p, 'dDataEstreia'); ?>" required>
						</div>

						<div class="form-group col-md-4">
							<label for="dDataFim" class="control-label">Data Fim:</label>
							<input name="dDataFim" type="date" class="form-control" value="<?php echo esta_setado($p, 'dDataFim'); ?>">
						</div>
					</div>

					<div class="row">
						<div class="form-group col-md-4">
							<label for="sClassificacaoIndicativa" class="control-label">Classificação Indicativa:</label>
							<select name="sClassificacaoIndicativa" id="sClassificacaoIndicativa" class="form-control" required>
								<?php 
								$temp_classificacao_etaria = esta_setado($p, 'sClassificacaoIndicativa');
								if ($temp_classificacao_etaria): 

									$classificacao_etaria = CTClassificacaoEtaria::selectClassificacaoEtaria($con, $temp_classificacao_etaria);
								?>

									<option value="<?php echo $classificacao_etaria->getIdClassificacaoEtaria();?>"><?php echo $classificacao_etaria->getDescricao(); ?></option>
								
								<?php else: ?>

									<option value=""></option>
								
								<?php endif;
								
								$classificacoes_etarias = CTClassificacaoEtaria::selectClassificacoesEtarias($con);
								foreach ($classificacoes_etarias as $cle) {
									echo "<option value='".$cle->getIdClassificacaoEtaria()."'>".$cle->getDescricao()."</option>";
								}

								?>
							</select>
						</div>

						<div class="form-group col-md-4">
							<label for="sPais" class="control-label">País:</label>
							<select name="sPais" id="sPais" class="form-control" required>
								<?php 
								$temp_pais = esta_setado($p, 'sPais');
								if ($temp_pais): 

									$pais = CTPais::selectPais($con, $temp_pais);
								?>

									<option value="<?php echo $pais->getIdPais();?>"><?php echo $pais->getNome(); ?></option>
								
								<?php else: ?>

									<option value=""></option>
								
								<?php endif;
								
								$paises = CTPais::selectPaises($con);
								foreach ($paises as $pas) {
									echo "<option value='".$pas->getIdPais()."'>".$pas->getNome()."</option>";
								}

								?>
							</select>
						</div>

						<div class="form-group col-md-4">
							<label for="sIdioma" class="control-label">Idioma:</label>
							<select name="sIdioma" id="sIdioma" class="form-control" required>
								<?php 
								$temp_idioma = esta_setado($p, 'sIdioma');
								if ($temp_idioma): 

									$idioma = CTIdioma::selectIdioma($con, $temp_idioma);
								?>

									<option value="<?php echo $idioma->getIdIdioma();?>"><?php echo $idioma->getNome(); ?></option>
								
								<?php else: ?>

									<option value=""></option>
								
								<?php endif;
								
								$idiomas = CTIdioma::selectIdiomas($con);
								foreach ($idiomas as $idm) {
									echo "<option value='".$idm->getIdIdioma()."'>".$idm->getNome()."</option>";
								}

								?>
							</select>
						</div>
					</div>

					<div class="row">
						<div class="form-group col-md-12">
							<label for="taSinopse" class="control-label">Sinopse:</label>
							<textarea name="taSinopse" class="form-control" rows="5" minlength="30" maxlength="1000" required><?php echo esta_setado($p, 'taSinopse'); ?></textarea>
						</div>
					</div>

					<div class="row">
						<div class="form-group col-md-12 text-right">
							<button type="reset" class="btn btn-warning"><span class="fa fa-minus-circle" aria-hidden="true"></span> Limpar</button>
							<button name="bDadosGerais" type="submit" class="btn btn-warning"><span class="fa fa-save" aria-hidden="true"></span> Salvar</button>
						</div>
					</div>

				</form><!--FIm form dados-gerais-->

				<form class="div-oculta" id="generos" action="<?php echo $_SERVER['PHP_SELF'] ?>" method="POST" accept-charset="utf-8" enctype="multipart/form-data">

					<div class="row">
						<label for="" class="control-label col-md-12">Gênero(s):</label>
						<div class="form-group col-md-4">
							<div class="checkbox">
								<label for="">
									<input type="checkbox" value="">Ação
								</label>
							</div>
							<div class="checkbox">
								<label>
									<input type="checkbox" value="">Chanchada
								</label>
							</div>
							<div class="checkbox">
								<label>
									<input type="checkbox" value="">Comédia romântica
								</label>
							</div>
							<div class="checkbox">
								<label>
									<input type="checkbox" value="">Cult
								</label>
							</div>
							<div class="checkbox">
								<label>
									<input type="checkbox" value="">Drama
								</label>
							</div>
							<div class="checkbox">
								<label>
									<input type="checkbox" value="">Fantasia
								</label>
							</div>
							<div class="checkbox">
								<label>
									<input type="checkbox" value="">Franchise/Séries
								</label>
							</div>
							<div class="checkbox">
								<label>
									<input type="checkbox" value="">Masala
								</label>
							</div>
							<div class="checkbox">
								<label>
									<input type="checkbox" value="">Policial
								</label>
							</div>
							<div class="checkbox">
								<label>
									<input type="checkbox" value="">Romance
								</label>
							</div>
							<div class="checkbox">
								<label>
									<input type="checkbox" value="">Terror (ou horror)
								</label>
							</div>
						</div>
						<div class="form-group col-md-4">
							<div class="checkbox">
								<label>
									<input type="checkbox" value="">Animação
								</label>
							</div>
							<div class="checkbox">
								<label>
									<input type="checkbox" value="">Cinema catástrofe
								</label>
							</div>
							<div class="checkbox">
								<label>
									<input type="checkbox" value="">Comédia dramática
								</label>
							</div>
							<div class="checkbox">
								<label>
									<input type="checkbox" value="">Dança
								</label>
							</div>
							<div class="checkbox">
								<label>
									<input type="checkbox" value="">Espionagem
								</label>
							</div>
							<div class="checkbox">
								<label>
									<input type="checkbox" value="">Faroeste (ou western)
								</label>
							</div>
							<div class="checkbox">
								<label>
									<input type="checkbox" value="">Guerra
								</label>
							</div>
							<div class="checkbox">
								<label>
									<input type="checkbox" value="">Musical
								</label>
							</div>
							<div class="checkbox">
								<label>
									<input type="checkbox" value="">Pornochanchada
								</label>
							</div>
							<div class="checkbox">
								<label>
									<input type="checkbox" value="">Seriado
								</label>
							</div>
							<div class="checkbox">
								<label>
									<input type="checkbox" value="">Trash
								</label>
							</div>
						</div>
						<div class="form-group col-md-4">
							<div class="checkbox">
								<label>
									<input type="checkbox" value="">Aventura
								</label>
							</div>
							<div class="checkbox">
								<label>
									<input type="checkbox" value="">Comédia
								</label>
							</div>
							<div class="checkbox">
								<label>
									<input type="checkbox" value="">Comédia de ação
								</label>
							</div>
							<div class="checkbox">
								<label>
									<input type="checkbox" value="">Documentários
								</label>
							</div>
							<div class="checkbox">
								<label>
									<input type="checkbox" value="">Erótico
								</label>
							</div>
							<div class="checkbox">
								<label>
									<input type="checkbox" value="">Ficção científica
								</label>
							</div>
							<div class="checkbox">
								<label>
									<input type="checkbox" value="">Machinima
								</label>
							</div>
							<div class="checkbox">
								<label>
									<input type="checkbox" value="">Filme noir
								</label>
							</div>
							<div class="checkbox">
								<label>
									<input type="checkbox" value="">Pornográfico
								</label>
							</div>
							<div class="checkbox">
								<label>
									<input type="checkbox" value="">Suspense
								</label>
							</div>
						</div>
					</div>

					<div class="row">
						<div class="form-group col-md-12 text-right">
							<button type="reset" class="btn btn-warning"><span class="fa fa-minus-circle" aria-hidden="true"></span> Limpar</button>
							<button type="submit" class="btn btn-warning"><span class="fa fa-save" aria-hidden="true"></span> Salvar</button>
						</div>
					</div>

				</form><!--Fim form gênero-->

				<form class="div-oculta" id="direcao" action="<?php echo $_SERVER['PHP_SELF'] ?>" method="POST" accept-charset="utf-8" enctype="multipart/form-data">

					<div class="row">
						<label class="control-label col-md-12">Diretor:</label>
						<div class="col-md-6">
							<div class="input-group">
								<input type="text" class="form-control" placeholder="Buscar diretor">
								<span class="input-group-btn">
									<button class="btn btn-default" type="button"><span class="fa fa-search" aria-hidden="true"></span></button>
								</span>
							</div>
						</div>
					</div>

					<div class="row">
						<div class="col-md-12">
							<div class="table-responsive margin-top">
								<table class="table table-hover">
									<thead>
										<tr>
											<th>#</th>
											<th>Nome</th>
										</tr>
									</thead>
									<tbody>
										<tr class="cursor-hand">
											<td>1</td>
											<td>Patrick</td>
										</tr>
										<tr class="cursor-hand">
											<td>2</td>
											<td>Matheus</td>
										</tr>
										<tr class="cursor-hand">
											<td>3</td>
											<td>Jonas</td>
										</tr>
									</tbody>
								</table>
							</div>
						</div>
					</div>

					<div class="row">
						<div class="form-group col-md-12 text-right">
							<button type="reset" class="btn btn-warning"><span class="fa fa-minus-circle" aria-hidden="true"></span> Limpar</button>
							<button type="submit" class="btn btn-warning"><span class="fa fa-save" aria-hidden="true"></span> Salvar</button>
						</div>
					</div>

				</form><!--Fim form direcao-->

				<form class="div-oculta" id="elenco" action="<?php echo $_SERVER['PHP_SELF'] ?>" method="POST" accept-charset="utf-8" enctype="multipart/form-data">

					<div class="row">
						<label class="control-label col-md-12">Ator/Atriz:</label>
						<div class="col-md-6">
							<div class="input-group">
								<input type="text" class="form-control" placeholder="Buscar ator/atriz">
								<span class="input-group-btn">
									<button class="btn btn-default" type="button"><span class="fa fa-search" aria-hidden="true"></span></button>
								</span>
							</div>
						</div>
					</div>

					<div class="row">
						<div class="col-md-12">
							<div class="table-responsive margin-top">
								<table class="table table-hover">
									<thead>
										<tr>
											<th>#</th>
											<th>Nome</th>
											<th>Participação</th>
										</tr>
									</thead>
									<tbody>
										<tr class="cursor-hand" onclick="alterarPagina('www/user/perfil/perfil_user_series.php');">
											<td>1</td>
											<td>Patrick</td>
											<td>Ator principal</td>
										</tr>
										<tr class="cursor-hand" onclick="alterarPagina('www/user/perfil/perfil_user_series.php');">
											<td>2</td>
											<td>Tanya</td>
											<td>Atriz principal</td>
										</tr>
										<tr class="cursor-hand" onclick="alterarPagina('www/user/perfil/perfil_user_series.php');">
											<td>3</td>
											<td>Jonas</td>
											<td>Ator coadjuvante</td>
										</tr>
									</tbody>
								</table>
							</div>
						</div>
					</div>

					<div class="row">
						<div class="form-group col-md-12 text-right">
							<button type="reset" class="btn btn-warning"><span class="fa fa-minus-circle" aria-hidden="true"></span> Limpar</button>
							<button type="submit" class="btn btn-warning"><span class="fa fa-save" aria-hidden="true"></span> Salvar</button>
						</div>
					</div>

				</form><!--Fim form elenco-->

				<form class="div-oculta" id="premiacoes" action="<?php echo $_SERVER['PHP_SELF'] ?>" method="POST" accept-charset="utf-8" enctype="multipart/form-data">

					<div class="row">
						<div class="form-group col-md-12">
							<label class="control-label">Premiações:</label>
							<textarea type="text" rows="3" class="form-control"></textarea>
						</div>
					</div>

					<div class="row">
						<div class="form-group col-md-12 text-right">
							<button type="reset" class="btn btn-warning"><span class="fa fa-minus-circle" aria-hidden="true"></span> Limpar</button>
							<button type="submit" class="btn btn-warning"><span class="fa fa-save" aria-hidden="true"></span> Salvar</button>
						</div>
					</div>

				</form><!--Fim form premiações-->

				<form class="div-oculta" id="temporadas" action="<?php echo $_SERVER['PHP_SELF'] ?>" method="POST" accept-charset="utf-8" enctype="multipart/form-data">

					<div class="row">
						<div class="panel panel-default">
							<div class="panel-body">
							Basic panel example
							</div>
						</div>
					</div>

					<div class="row">
						<div class="form-group col-md-12 text-right">
							<button type="reset" class="btn btn-warning"><span class="fa fa-minus-circle" aria-hidden="true"></span> Limpar</button>
							<button type="submit" class="btn btn-warning"><span class="fa fa-save" aria-hidden="true"></span> Salvar</button>
						</div>
					</div>

				</form><!--FIm form temporadas-->

				<form class="div-oculta" id="episodios" action="<?php echo $_SERVER['PHP_SELF'] ?>" method="POST" accept-charset="utf-8" enctype="multipart/form-data">

					<div class="row">
						<div class="form-group col-md-12">
							<label class="control-label">Episódios:</label>
							<textarea type="text" rows="3" class="form-control"></textarea>
						</div>
					</div>

					<div class="row">
						<div class="form-group col-md-12 text-right">
							<button type="reset" class="btn btn-warning"><span class="fa fa-minus-circle" aria-hidden="true"></span> Limpar</button>
							<button type="submit" class="btn btn-warning"><span class="fa fa-save" aria-hidden="true"></span> Salvar</button>
						</div>
					</div>

				</form><!--Fim form episodios-->
				
			</div>
		
		</div>
	</div>

	<?php 
	require_once '../rodape.php';
	$con = null;
	?>

</body>
</html>

<?php 
					$classificacao_etaria = CTClassificacaoEtaria::selectClassificacoesEtarias($con);

					if ($classificacao_etaria):
				?>
					
					<form action="<?php echo $_SERVER['PHP_SELF'] ?>" method="POST" accept-charset="utf-8">

						<div class="table-responsive">
							<table class="table table-hover">
								<thead>
									<tr>
										<th>ID</th>
										<th>Descrição</th>
										<th>Imagem</th>
										<th></th>
										<th></th>
									</tr>
								</thead>
								<tbody>
									<?php
										
										foreach ($classificacao_etaria as $cle) {
									        echo "<tr onclick=''>
												<td>".$cle->getIdClassificacaoEtaria()."</td>
												<td>".$cle->getDescricao()."</td>
												<td>EXIBIR IMAGEM</td>

												<td><button name='b-edit' value='".$cle->getIdClassificacaoEtaria()."' type='submit' class='btn-link'><span class='fa fa-edit text-primary' aria-hidden='true'></span></button></td>
												<td><button name='b-delete' value='".$cle->getIdClassificacaoEtaria()."' type='submit' class='btn-link'><span class='fa fa-trash-o text-danger' aria-hidden='true'></span></button></td>
											</tr>";
									    }

									?>
								</tbody>
							</table>
						</div>
					</form>

				<?php endif; ?>
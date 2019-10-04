<?php

require_once 'cabeca_admin_config.php';
require_once __ROOT__.'/php/controller/class.CTUsuario.php';

$s = &$_SESSION;
$p = &$_POST;

$id_usuario = $s['id_usuario'];

$con = con_db_tns();


if ($p)
{
	$dados_usuario = CTUsuario::validarDadosCadastroUsuario($p);
	$obj_usuario = new MDUsuario($dados_usuario);
	$erro = CTUsuario::insertUpdateUsuario($con, $id_usuario, $obj_usuario);
}

?>
<!DOCTYPE html>
<html lang="pt-br">
<head>
	<?php require_once '../cabeca.php'; ?>
    <!--Título-->
    <title>Tô na Série - Cadastro de Usuário</title>
</head>
<body>

	<?php require_once '../cabecalho.php'; ?>

	<div class="container-fluid padding-top">
		<div class="row">

			<?php require_once 'menu_admin_config.php'; ?>

			<div class="col-sm-10 panel panel-orange margin-top">
				<form action="<?php echo $_SERVER['PHP_SELF'] ?>" method="POST" accept-charset="utf-8"  enctype="multipart/form-data" onsubmit="return validaFormCadastro();">

					<div class="row">
						<h3 class="col-md-12">Cadastro de Usuário</h3>
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
								Cadastro realizado com sucesso
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
						<div class="form-group col-md-2">
							<input name="nId" type="hidden" class="form-control" value="<?php echo esta_setado($p, 'nId'); ?>" readonly>
						</div>						
					</div>

					<div class="row">
						<div class="form-group col-md-8">
							<label for="tNome" class="control-label">Nome completo <span class="text-danger">*</span>:</label>
							<input name="tNome" type="text" class="form-control" minlength="3" maxlength="75" value="<?php echo esta_setado($p, 'tNome'); ?>" required>
						</div>
						<div class="form-group col-md-4">
							<label for="tApelido" class="control-label">Apelido <span class="text-danger">*</span><span title="Será seu nome de exibição" class="fa fa-info-circle"></span>:</label>
							<input name="tApelido" type="text" class="form-control" minlength="3" maxlength="25" value="<?php echo esta_setado($p, 'tApelido'); ?>" required>
						</div>
					</div>

					<div class="row">
						<div class="form-group col-md-4">
							<label for="sSexo" class="control-label">Sexo:</label>
							<select name="sSexo" class="form-control">

								<?php
								$temp_sexo = esta_setado($p, 'sSexo');
								if ($temp_sexo): ?>

									<option value="<?php echo $temp_sexo ?>">
										<?php switch ($temp_sexo) {
											
											case 'M':
												echo "Masculino";
												break;

											case 'F':
												echo "Feminino";
												break;

											case 'N':
											default:
												echo "Prefiro não informar";
												break;

										} ?>
									</option>

								<?php endif ?>
								<option value="N">Prefiro não informar</option>
								<option value="M">Masculino</option>
								<option value="F">Feminino</option>
							</select>
						</div>
						<div class="form-group col-md-4">
							<label for="dDataNascimento" class="control-label">Data de nascimento <span class="text-danger">*</span>:</label>
							<input name="dDataNascimento" type="date" class="form-control" value="<?php echo esta_setado($p, 'dDataNascimento'); ?>" required>
						</div>
						<div class="form-group col-md-4">
							<label for="sNivelAcesso" class="control-label">Nível de acesso:</label>
							<select name="sNivelAcesso" class="form-control">

								<?php 
								$temp_nivel = esta_setado($p, 'sNivelAcesso');
								if ($temp_nivel): 

									$nivel = CTNivelAcesso::selectNivelAcesso($con, $temp_nivel);
								?>

									<option value="<?php echo $nivel->getIdNivelAcesso();?>"><?php echo $nivel->getNome(); ?></option>
								
								<?php else: ?>

									<option value=""></option>
								
								<?php endif;
								
								$niveis = CTNivelAcesso::selectNiveisAcesso($con);
								foreach ($niveis as $n) {
									echo "<option value='".$n->getIdNivelAcesso()."'>".$n->getNome()."</option>";
								}

								?>
							</select>
						</div>
					</div>

					<fieldset>
						<legend>Contato</legend>

						<div class="row">
							<div class="form-group col-md-6">
								<label for="eEmail" class="control-label">E-mail <span class="text-danger">*</span>:</label>
								<input onchange="campoIgual('Email')" id="eEmail" name="eEmail" type="email" class="form-control" value="<?php echo esta_setado($p, 'eEmail'); ?>" required>
							</div>
							<div class="form-group col-md-6">
								<label for="eRepetirEmail" class="control-label">Repetir e-mail <span class="text-danger">*</span>:</label>
								<input onchange="campoIgual('Email')" id="eRepetirEmail"
								name="eRepetirEmail" type="email" class="form-control" value="<?php echo esta_setado($p, 'eRepetirEmail'); ?>" required>
							</div>
						</div>

						<div class="row">
							<div class="form-group col-md-6">
								<label for="tTelefone" class="control-label">Telefone:</label>
								<input id="tTelefone" name="tTelefone" type="tel" class="form-control" value="<?php echo esta_setado($p, 'tTelefone'); ?>">
							</div>
							<div class="col-md-6">
								<label for="tFacebook" class="control-label">Facebook:</label>
								<div class="input-group">
									<span class="input-group-addon">https://www.facebook.com/</span>
									<input name="tFacebook" type="text" class="form-control" value="<?php echo esta_setado($p, 'tFacebook'); ?>">
								</div>
							</div>
						</div>
					</fieldset>

					<div class="row">
						<div class="form-group col-md-6">
							<label for="pSenha" class="control-label">Senha <span class="text-danger">*</span>:</label>
							<input onchange="campoIgual('Senha')" id="pSenha" name="pSenha" title="Tamanho mínimo de 6 caracteres contendo ao menos um caracter especial, números, letras maiúsculas e minúsculas" minlength="6" pattern="(?=^.{8,}$)((?=.*\d)|(?=.*\W+))(?![.\n])(?=.*[A-Z])(?=.*[a-z]).*$" type="password" class="form-control" value="<?php echo esta_setado($p, 'pSenha'); ?>" required>
						</div>
						<div class="form-group col-md-6">
							<label for="pRepetirSenha" class="control-label">Repetir senha <span class="text-danger">*</span>:</label>
							<input onchange="campoIgual('Senha')" id="pRepetirSenha" name="pRepetirSenha" type="password" class="form-control" value="<?php echo esta_setado($p, 'pRepetirSenha'); ?>" required>
						</div>
					</div>

					<div class="row">
						<div class="form-group col-md-12 text-right">
							<button type="reset" class="btn btn-warning"><span class="fa fa-minus-circle" aria-hidden="true"></span> Limpar</button>
							<button type="submit" class="btn btn-warning"><span class="fa fa-user-plus" aria-hidden="true"></span> Cadastrar</button>
						</div>
					</div>
					
				</form>
			</div>
		
		</div>
	</div>

	<?php
	require_once '../rodape.php';
	$con = null;
	?>

</body>
</html>
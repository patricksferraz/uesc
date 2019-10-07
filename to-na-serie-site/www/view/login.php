<?php
require_once '../../php/controle_acesso/conexao.php';
require_once '../../php/fun_logar.php';
$con = con_db_tns();

$p = &$_POST;

$erro = false;

if ($p)
{
	$login = $p['tLogin'];
	$senha = $p['pSenha'];
	$dado_acesso = logar($login, $senha, $con);

	if(is_array($dado_acesso))
	{
		session_set_cookie_params(0);
		require_once '../../php/controle_acesso/resgate_sessao.php';
		$_SESSION['id_usuario'] = $dado_acesso['usr_id_usuario'];
		$_SESSION['id_nivel_acesso'] = $dado_acesso['usr_id_nivel_acesso'];
		$_SESSION['nome_acesso'] = $dado_acesso['nva_nome'];
		$_SESSION['apelido'] = $dado_acesso['usr_apelido'];
		$_SESSION['agent'] = md5($_SERVER['HTTP_USER_AGENT']);
		header("location: ../index.php");
	} 
	else 
	{
		$erro = true;
	}

}

?>

<!DOCTYPE html>
<html lang="pt-br">
<head>
	<?php require_once '../cabeca.php'; ?>
    <!--Título e favicon-->
    <title>Tô na Série - Login</title>
</head>
<body>
	<div class="container-fluid padding-top">
		<div class="row">
			<div class="col-sm-6 col-sm-offset-3 panel panel-orange">
				
				<div class="row margin-top">
					<div class="col-md-12">
						<a href=""><img class="img-responsive center-block" alt="Tô na Série" src="img/logo_principal.svg"></a>
					</div>
				</div>

				<div class="row">
					<h2 class="col-md-12 text-center">Olá! Para continuar efetue o acesso.</h2>
				</div>

				<form action="<?php echo $_SERVER['PHP_SELF'] ?>" method="POST" accept-charset="utf-8">

				<?php 

					if ($erro)
					{
						echo "<div class='row'>
								<div class='alert alert-danger col-md-12 margin-top text-center' role='alert'>
									<span class='fa fa-exclamation' aria-hidden='true'></span> Login ou Senha incorretos!
								</div>
						</div>";
					}

				?>
				
					<div class="row">
						<div class="form-group col-md-12">
							<label for="tLogin" class="control-label">Apelido/Email:</label>
							<input name="tLogin" type="text" class="form-control" value="<?php if(isset($login)) echo $login ?>" required>
						</div>
					</div>

					<div class="row">
						<div class="form-group col-md-12">
							<label for="pSenha" class="control-label">Senha:</label>
							<input name="pSenha" type="password" class="form-control" value="<?php if(isset($senha)) echo $senha ?>" required>
						</div>
					</div>

					<div class="row">
						<div class="form-group col-md-12">
							<a href="www/view/recuperar_senha.php">Esqueceu a senha?</a>
							<div class="pull-right">
								<button type="button" onclick="location.href = 'www/view/cadastro.php'" class="btn btn-warning"><span class="fa fa-user-plus" aria-hidden="true"></span> Cadastre-se</button>
								<button type="submit" class="btn btn-warning"><span class="fa fa-sign-in" aria-hidden="true"></span> Entrar</button>	
							</div>
						</div>
					</div>

				</form>
					

			</div>
		</div>
	</div>
</body>
</html>
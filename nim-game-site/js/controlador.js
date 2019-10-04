function cadastroJogador (button)
{
	const TAM_MIN_SENHA = 8;
	var flagErro = false;
	var erro   = [];
	var acao   = $(button).val();
	var nome   = $('#nomeUsrCadastro').val();
	var email  = $('#emailUsrCadastro').val();
	var senha  = $('#senhaUsrCadastro').val();
	var rSenha = $('#rSenhaUsrCadastro').val();

	$('#alert-cadastro').html('');
	$('#alert-jogador1').html('');
	$('#alert-jogador2').html('');

	if (nome.length < 3)
	{
		flagErro = true;
		erro.push("Informe um nome de usuário com mais de 3 caracteres");
	}
	
	if (senha.length < TAM_MIN_SENHA)
	{
		flagErro = true;
		erro.push("Senha com menos de 8 caracteres.");
	}
	else if (senha != rSenha)
	{
		flagErro = true;
		erro.push("Senhas não confere");
	}
	
	if (flagErro)
	{
		$('#alert-cadastro').append('<div id="alert" class="card-panel red lighten-3 white-text">');

		$(erro).each(function(index, el) {
			$('#alert').append('<i class="material-icons tiny">info</i> ' + el + '<br>');
		});

		$('#alert-cadastro').append("</div>")
	}
	else
	{
		$.ajax({
	        url: 'php/data.php',
	        type: 'POST',
	        data: {
	        	acao: acao,
	            nome: nome,
	            email: email,
	            senha: senha
	        },
	        beforeSend: function(){
	        	$('#alert-cadastro').html(
					'<div class="preloader-wrapper big active center-block">'
					+	'<div class="spinner-layer spinner-green-only">'
					+		'<div class="circle-clipper left">'
					+			'<div class="circle"></div>'
					+		'</div>'
					+		'<div class="gap-patch">'
					+			'<div class="circle"></div>'
					+		'</div>'
					+		'<div class="circle-clipper right">'
					+			'<div class="circle"></div>'
					+		'</div>'
					+	'</div>'
					+'</div>'
				);
				$('.conteudoCadastro').hide();
	        },
	        success: function( data ) {
	            var dados = $.parseJSON(data);

	            $('#alert-cadastro').html('');
	            $('.conteudoCadastro').show();
	            if (dados.validacao == false)
	            {
	            	$('#alert-cadastro').append('<div id="alert" class="card-panel red lighten-3 white-text">');
					$('#alert').append('<i class="material-icons tiny">info</i> ' + dados.motivo + '<br>');
					$('#alert-cadastro').append("</div>")
	            }
	            else
	            {
	            	$('.conteudoCadastro').html('');
	            	$('#alert-cadastro').append('<div id="alert" class="card-panel green lighten-3 white-text">');
					$('#alert').append('<i class="material-icons tiny">check</i> Usuário criado com sucesso<br>');
					$('#alert-cadastro').append("</div>")

					setTimeout(function(){
						$('#modalCadastro').modal('close');
					}, 2000);
	            }
	        }
	    });
	}
}

function loginJogador (button)
{
	var flagErro = false;
	var erro     = [];
	var acao     = $(button).val();
	var usuario;
	var senha;

	$('#alert-cadastro').html('');
	$('#alert-jogador1').html('');
	$('#alert-jogador2').html('');

	if (acao == 'loginJogador1')
	{
		usuario = $('#usrJogador1').val();
		senha   = $('#senhaUsrJogador1').val();

		if (usuario == '' || senha == '')
		{
			$('#alert-jogador1').append('<div id="alert" class="card-panel red lighten-3 white-text">');
			$('#alert').append('<i class="material-icons tiny">info</i> Favor preencher os dados<br>');
			$('#alert-jogador1').append("</div>");
		}
		else
		{
			acao = 'loginJogador';

			$.ajax({
		        url: 'php/data.php',
		        type: 'POST',
		        data: {
		        	acao: acao,
		        	usuario: usuario,
		            senha: senha
		        },
		        beforeSend: function(){
		        	$('#alert-jogador1').html(
						'<div class="preloader-wrapper big active center-block">'
						+	'<div class="spinner-layer spinner-green-only">'
						+		'<div class="circle-clipper left">'
						+			'<div class="circle"></div>'
						+		'</div>'
						+		'<div class="gap-patch">'
						+			'<div class="circle"></div>'
						+		'</div>'
						+		'<div class="circle-clipper right">'
						+			'<div class="circle"></div>'
						+		'</div>'
						+	'</div>'
						+'</div>'
					);
					$('.conteudoJogador1').hide();
		        },
		        success: function( data ) {
		            var dados = $.parseJSON(data);

		            $('#alert-jogador1').html('');
		            $('.conteudoJogador1').show();
		            if (dados.validacao == false)
		            {
		            	$('#alert-jogador1').append('<div id="alert" class="card-panel red lighten-3 white-text">');
						$('#alert').append('<i class="material-icons tiny">info</i>  Usuário ou senha incorretos<br>');
						$('#alert-jogador1').append("</div>");
		            }
		            else
		            {
		            	$('.conteudoJogador1').html('');
		            	$('#alert-jogador1').append('<div id="alert" class="card-panel green lighten-3 white-text">');
						$('#alert').append('<i class="material-icons tiny">check</i> Login efetuado com sucesso<br>');
						$('#alert-jogador1').append("</div>");

						$('#codJogador1').val(dados.codUsuario);
						$('#nomeJogador1').val(usuario);
						$('#nomeJogador1').prop('readonly', true);
						$("label[for=nomeJogador1]").hide();

						setTimeout(function(){
							$('#modalJogador1').modal('close');
						}, 2000);
		            }
		        }
		    });
		}
	}
	else if (acao == 'loginJogador2')
	{
		usuario = $('#usrJogador2').val();
		senha   = $('#senhaUsrJogador2').val();

		if (usuario == '' || senha == '')
		{
			$('#alert-jogador2').append('<div id="alert" class="card-panel red lighten-3 white-text">');
			$('#alert').append('<i class="material-icons tiny">info</i> Favor preencher os dados<br>');
			$('#alert-jogador2').append("</div>");
		}
		else
		{
			acao = 'loginJogador';

			$.ajax({
		        url: 'php/data.php',
		        type: 'POST',
		        data: {
		        	acao: acao,
		        	usuario: usuario,
		            senha: senha
		        },
		        beforeSend: function(){
		        	$('#alert-jogador2').html(
						'<div class="preloader-wrapper big active center-block">'
						+	'<div class="spinner-layer spinner-green-only">'
						+		'<div class="circle-clipper left">'
						+			'<div class="circle"></div>'
						+		'</div>'
						+		'<div class="gap-patch">'
						+			'<div class="circle"></div>'
						+		'</div>'
						+		'<div class="circle-clipper right">'
						+			'<div class="circle"></div>'
						+		'</div>'
						+	'</div>'
						+'</div>'
					);
					$('.conteudoJogador2').hide();
		        },
		        success: function( data ) {
		            var dados = $.parseJSON(data);

		            $('#alert-jogador2').html('');
		            $('.conteudoJogador2').show();
		            if (dados.validacao == false)
		            {
		            	$('#alert-jogador2').append('<div id="alert" class="card-panel red lighten-3 white-text">');
						$('#alert').append('<i class="material-icons tiny">info</i> Usuário ou senha incorretos<br>');
						$('#alert-jogador2').append("</div>");
		            }
		            else
		            {
		            	$('.conteudoJogador2').html('');
		            	$('#alert-jogador2').append('<div id="alert" class="card-panel green lighten-3 white-text">');
						$('#alert').append('<i class="material-icons tiny">check</i> Login efetuado com sucesso<br>');
						$('#alert-jogador2').append("</div>");

						$('#codJogador2').val(dados.codUsuario);
						$('#nomeJogador2').val(usuario);
						$('#nomeJogador2').prop('readonly', true);
						$("label[for=nomeJogador2]").hide();

						setTimeout(function(){
							$('#modalJogador2').modal('close');
						}, 2000);
		            }
		        }
		    });
		}
	}
}

function graveRecorde (scoreJogador, qntLinhas, codJogador)
{
	$.ajax({
        url: 'php/data.php',
        type: 'POST',
        data: {
        	acao: 'graveRecorde',
        	qntLinhas: qntLinhas,
            codJogador: codJogador,
        	scoreJogador: scoreJogador
        }
    });	
}
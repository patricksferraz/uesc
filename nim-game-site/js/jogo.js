(function($)
{
	var button;
	var inId;
	var endId;

	$(document).on('mouseover', 'label', function(event) {
		button  = $(this).attr('for');
		var aux = (button.lastIndexOf("_")) + 1;
		inId  = button.substring(0, aux);
		endId = button.substring(aux);

		pecaIn(inId, endId);
	})
	.on('mouseout', 'label', function(event) {

		pecaOut(inId, endId);
	
	})
	.on('click', 'label', function(event) {

		pecaClick(inId, endId);

	})

})(jQuery); // end of jQuery name space

var numPartida;
var qntLinhas;
var jogador;
var qntBlocos;
var vezJogador; // 0 para jogador 1; 1 para jogador 2
var scoreJogador;
var codJogador;
var mult;

function inicializa(qtLinhas, multijogador, codJogador1, nomeJogador1, codJogador2, nomeJogador2)
{
	numPartida   = 1;
	vezJogador   = 0;
	scoreJogador = [0, 0];
	qntLinhas    = qtLinhas;
	codJogador   = [codJogador1, codJogador2];
	jogador      = [nomeJogador1, nomeJogador2];
	qntBlocos    = (qntLinhas*(qntLinhas + 1)) >>> 1;

	if (multijogador == '')
		mult = false;
	else
		mult = true;

	$('#scoreJogador1').html(0);
	$('#scoreJogador2').html(0);

	Materialize.toast('Quem começa é: ' + jogador[vezJogador], 2000);
	$('#vezJogador').html('Quem começa é: ' + jogador[vezJogador]);
};

function novaPartida()
{
	var qntColunas = 1;
	var lin, col;
	
	qntBlocos = (qntLinhas*(qntLinhas + 1)) >>> 1;

	numPartida ++;
	$('#nPartida').html(numPartida);
	$('#telaJogo').html('');
	for (lin = 1; lin <= qntLinhas; lin++, qntColunas++)
	{
		$('#telaJogo').append('<div class="row bloco"><span class="col s1">' + lin + '</span><span class="col s11 linha_' + lin + '">');

		for (col = 1; col <= qntColunas; col++)
		{
			$('.linha_' + lin).append('<input value="' + lin + '" class="filled-in" name="bloco" type="checkbox" id="linha_' + lin + '_' + col + '" /><label for="linha_' + lin + '_' + col + '"></label>');
		}

		$('#telaJogo').append('</span></div>');
	}

	Materialize.toast('Quem começa é: ' + jogador[vezJogador], 2000);
	$('#vezJogador').html('Quem começa é: ' + jogador[vezJogador]);

	if (vezJogador == 1 && mult == false)
		jogadaComputador();

};

function finalizaJogo()
{
	var vencedor;

	if (scoreJogador[0] > scoreJogador[1])
		vencedor = jogador[0] + ' foi o vencedor';
	else if (scoreJogador[0] < scoreJogador[1])
		vencedor = jogador[1] + ' foi o vencedor';
	else
		vencedor = 'Houve um empate';

	graveRecorde(scoreJogador, qntLinhas, codJogador);
	
	$('#telaJogo').html(
		'<h4 class="teal-text text-lighten-2 center">Obrigado por jogar!</h4>'
		+'<div class="row">'
		+	'<h5 class="teal-text text-lighten-2 center">' + vencedor + '</h5>'
		+	'<div class="col s12 m6 center">'
		+		'<div class="chip">O jogador \'' + jogador[0] + '\' marcou [' + scoreJogador[0] + '] pontos</div>'
		+	'</div>'
		+	'<div class="col s12 m6 center">'
		+		'<div class="chip">O jogador \'' + jogador[1] + '\' marcou [' + scoreJogador[1] + '] pontos</div>'
		+	'</div>'
		+'</div>'
	);

	setTimeout(function(){
		location.href = 'index.php';
	}, 4000);
}

function pecaIn (lin, col)
{
	var aux = $('#'+ lin + col);
	while(aux.val())
	{
		aux.prop('checked', true);
		col ++;
		aux = $('#'+ lin + col);
	}
};

function pecaOut (lin, col)
{
	var aux = $('#' + lin + col);
	while(aux.val())
	{
		aux.prop('checked', false);
		col ++;
		aux = $('#'+ lin + col);
	}
};

function pecaClick (lin, col)
{
	var aux = $('#'+ lin + col);
	var qntBlocosRemovidos = 0;
	var proxJogador;

	while(aux.val())
	{
		aux.remove();
		$('label[for = ' + lin + col + ']').remove();
		qntBlocosRemovidos ++;
		col ++;
		aux = $('#'+ lin + col);
	}

	proxJogador = (vezJogador + 1) % 2;
	qntBlocos  -= qntBlocosRemovidos;
	
	if (qntBlocos == 0)
		vencedor(proxJogador);
	else if (qntBlocos == 1)
		vencedor(vezJogador);
	else
	{		
		vezJogador = proxJogador;
		Materialize.toast('Quem joga é: ' + jogador[vezJogador], 2000);
		$('#vezJogador').html('Quem joga é: ' + jogador[vezJogador]);

		if (vezJogador == 1 && mult == false)
			jogadaComputador();
	}

}

function jogadaComputador ()
{
	var bloco = 'linha_';
	var bloco_random;
	var lin_random;
	var col_random;
	var flag;

	flag = true;
	while(flag)
	{
		lin_random = Math.floor(Math.random() * qntLinhas) + 1;
		col_random = Math.floor(Math.random() * lin_random) + 1;
		bloco_random = bloco + lin_random + '_';
		if ($('label[for = ' + bloco_random + col_random + ']').length)
		{
			setTimeout(function(){
				pecaClick(bloco_random, col_random);
			}, 2000);
			flag = false;
		}
	}
}

function vencedor (vencedor)
{
	vezJogador = vencedor;
	scoreJogador[vezJogador] += qntLinhas;

	$('#scoreJogador1').html(scoreJogador[0]);
	$('#scoreJogador2').html(scoreJogador[1]);

	Materialize.toast('Quem ganhou foi: ' + jogador[vencedor], 2000);
	$('#vezJogador').html('Quem ganhou foi: ' + jogador[vencedor]);

	$('#telaJogo').html(
		'<h4 class="teal-text text-lighten-2 center">' + jogador[vencedor] + ' foi o vencedor dessa rodada!</h4>'
		+'<div class="row">'
		+	'<div class="col s6">'
		+		'<button onclick="novaPartida()" class="btn-large pulse waves-effect waves-light left" type="button">Jogar novamente</button>'
		+	'</div>'
		+	'<div class="col s6">'
		+		'<button onclick="finalizaJogo()" class="btn-large waves-effect waves-light right" type="button">Finalizar</button>'
		+	'</div>'
		+'</div>'
	);

}
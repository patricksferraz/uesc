$(document).ready(function()
{
  $("#tTelefone").mask("(99) 99999-9999");
});

$(document).ready(function(){
    $(".form-control").focus(function(event) 
    {
    	$(this)
            .siblings(".control-label").addClass("focus-color-label")
            .parent(".input-group").siblings(".control-label").addClass("focus-color-label");
    });
    $(".form-control").blur(function(event) 
    {
    	$(this)
            .siblings(".control-label").removeClass("focus-color-label")
            .parent(".input-group").siblings(".control-label").removeClass("focus-color-label");
    });
});

function alterarConteudoDiv(local, conteudo)
{
    $("#"+local).load(conteudo);
}

//EXCLUIR
function alterarPagina(local)
{
    location.href = local;
}

function exibirDadosSubMenu(sub_menu, name)
{
    $("#"+sub_menu+">li").removeClass("active");
    $("[name="+name+"]").parent().addClass("active");
    $(".div-oculta").hide();
    $("#"+name).show();
}

function campoIgual(campo)
{
    var c_primario, c_secundario;

    switch(campo)
    {
        case "Senha":
            c_primario = "pSenha";
            c_secundario = "pRepetirSenha";
            break;
        case "Email":
            c_primario = "eEmail";
            c_secundario = "eRepetirEmail";
            break;
        default:
            break;
    }

    c_primario = $("#"+c_primario);
    c_secundario = $("#"+c_secundario);

    if (c_primario.val() == c_secundario.val())
    {
        c_primario
            .css("border-color", "#007F00")
            .siblings(".control-label").css("color", "#007F00");
        c_secundario
            .css("border-color", "#007F00")
            .siblings(".control-label").css("color", "#007F00");
    }
    else
    {
        c_primario
            .css("border-color", "#FF0000")
            .siblings(".control-label").css("color", "#FF0000");
        c_secundario
            .css("border-color", "#FF0000")
            .siblings(".control-label").css("color", "#FF0000");
    }
}

function emailIgual()
{
    var email = $("#eEmail").val();
    var rEmail = $("#eRepetirEmail").val();

    if (email == rEmail)
    {
        return true;
    }

    return false;
}

function senhaIgual()
{
    var senha = $("#pSenha").val();
    var rSenha = $("#pRepetirSenha").val();

    if (senha == rSenha)
    {
        return true;
    }

    return false;
}

function validaFormCadastro()
{

    var txtSenha = "", txtEmail = "", valido = true;
    var stxt = "<span class='fa fa-exclamation-circle' aria-hidden='true'></span><span class='sr-only'>Erro:</span> ";

    if (!senhaIgual())
    {
        valido = false;
        txtSenha = stxt+"Favor corrigir a senha<br>";
    }
    if (!emailIgual())
    {
        valido = false;
        txtEmail = stxt+"Favor corrigir o endereço de email";
    }

    if (!valido)
    {
        var txt = "<div class='alert alert-danger' role='alert'>"+txtSenha+txtEmail+"</div>";
        $("#alert").html(txt);
        $('html, body').animate({scrollTop : 0},800);
    }

    return valido;

}
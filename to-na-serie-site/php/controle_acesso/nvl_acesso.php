<?php

function esta_conectado($s)
{
	return isset($s['agent']) && ($s['agent'] == md5($_SERVER['HTTP_USER_AGENT']));
}

function eh_administrador($nvl)
{
	if ($nvl == 0)
	{
		return true;
	}
	return false;
}

function eh_gerente($nvl)
{
	if ($nvl == 1)
	{
		return true;
	}
	return false;
}

function eh_revisor($nvl)
{
	if ($nvl == 2)
	{
		return true;
	}
	return false;
}

function eh_contribuinte($nvl)
{
	if ($nvl == 3)
	{
		return true;
	}
	return false;
}

function eh_editor($nvl)
{
	if ($nvl == 4)
	{
		return true;
	}
	return false;
}

function eh_suporte($nvl)
{
	if ($nvl == 5)
	{
		return true;
	}
	return false;
}

function eh_usuario($nvl)
{
	if ($nvl == 6)
	{
		return true;
	}
	return false;
}

?>
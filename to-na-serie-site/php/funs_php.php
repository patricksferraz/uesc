<?php

function esta_setado($p, $n)
{
	if (isset($p[$n]))
	{
		return $p[$n];
	}
	else
	{
		return null;
	}
}

?>
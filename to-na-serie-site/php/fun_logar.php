<?php

function logar($login, $senha, $con)
{
	try 
	{

		$sql = "SELECT usr.usr_id_usuario, usr.usr_id_nivel_acesso, usr.usr_apelido, usr.usr_senha, nva.nva_nome FROM usr_usuario AS usr INNER JOIN nva_nivel_acesso AS nva ON usr_id_nivel_acesso = nva_id_nivel_acesso WHERE usr_apelido = :login OR usr_email = :login";
		$stmt = $con->prepare($sql);
		$stmt->execute(array(':login' => $login));
		$row = $stmt->fetch(PDO::FETCH_ASSOC);

		$db_senha = $row['usr_senha'];
		$id = $row['usr_id_usuario'];
		$nv = $row['usr_id_nivel_acesso'];
		$ap = $row['usr_apelido'];
		$nn = $row['nva_nome'];

		$stmt = $row = null;

		if ($db_senha == md5($senha))
		{
			return array('usr_id_usuario' => $id, 'usr_id_nivel_acesso' => $nv, 'usr_apelido' => $ap, 'nva_nome' => $nn);
		}

		return false;

	}
	catch (Exception $e) 
	{

		return false;
		
	}
}

?>
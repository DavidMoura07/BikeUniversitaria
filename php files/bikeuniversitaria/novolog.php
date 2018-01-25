<?php
	
	include("conecta.php");
	
	$cartao = $_GET['cartao'];

	$busca = "select idusuarios from usuarios where (cartao like ".$cartao.");";
	$usuario = mysql_query($busca);
	$linhausuario = mysql_fetch_array($usuario);
	$idusuario = $linhausuario["idusuarios"];
	$sql_insert = "insert into log (usuarios_idusuarios) values ('$idusuario')";
	
	if(mysql_query($sql_insert)){
		echo "salvo com sucesso!";
	}else{
		echo "Ocorreu um erro ao salvar no banco de dados!";
	}
	
?>
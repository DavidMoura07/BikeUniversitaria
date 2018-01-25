<?php

	$usuario		=	"root";
	$senha 			=	"";
	$host			=	"localhost";
	$banco			=	"bu";
	
	$conexao		=	mysql_connect($host,$usuario,$senha);
	$selecionabd	=	mysql_select_db($banco,$conexao);
	
	if($conexao){
		echo "Conectado com sucesso!";
	}else{
		echo "A conexao falhou!";
	}
	
?>
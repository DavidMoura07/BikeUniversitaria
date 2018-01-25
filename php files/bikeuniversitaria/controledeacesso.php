<?php
	include("conecta.php");
	$cartao = $_GET['cartao'];
	echo "<br>Cartao: ";
	echo "$cartao";
	$preco = 1.5;
	$busca = "select * from usuarios where (cartao like ".$cartao.");";
	if($usuario = mysql_query($busca)){
		$linhausuario = mysql_fetch_array($usuario);
		
		$idusuario = $linhausuario["idusuarios"];
		echo "<br>ID: ";
		echo "$idusuario";
		$nomeusuario = $linhausuario["nome"];
		echo "<br>Nome: ";
		echo "$nomeusuario";
		$saldousuario = $linhausuario["saldo"];
		echo "<br>Saldo: ";
		echo "$saldousuario";
		
		$queryacessos = "SELECT COUNT(usuarios_idusuarios) AS qtd_acesso FROM log WHERE (CAST(datahora AS DATE) LIKE CURRENT_DATE) AND (usuarios_idusuarios LIKE '".$idusuario."');";
		$acessos = mysql_query($queryacessos);
		$linha_acessos = mysql_fetch_array($acessos);
		$qtd_acessos = $linha_acessos["qtd_acesso"];
		echo "<br> Quantidade de acessos realizados hoje: ";
		echo "$qtd_acessos";
		if(!$qtd_acessos){
			if($saldousuario >= $preco){
				$acesso = 1;
				$saldousuario -= $preco;
				$atualizasaldo = "UPDATE `usuarios` SET `saldo` = '".$saldousuario."' WHERE `usuarios`.`idusuarios` = ".$idusuario.";";
				
				//atualiza o saldo do usuario
				if(mysql_query($atualizasaldo)){
					echo "<br>Saldo atualizado com sucesso!";
				}else{
					echo "<br>Ocorreu um erro ao atualizar saldo!";
				}
				
				//atualiza tabela de log
				$sql_insert = "insert into log (`usuarios_idusuarios`, `saldousuario`) values ('$idusuario','$saldousuario')";
				if(mysql_query($sql_insert)){
					echo "<br>Log atualizado com sucesso!";
				}else{
					echo "<br>Ocorreu um erro ao atualizar Log!";
				}
				
			}else{
				$acesso = 2;
				echo "<br>Falta de saldo";
			}
		}else{
			$acesso = 1;
			//atualiza tabela de log
			$sql_insert = "insert into log (`usuarios_idusuarios`, `saldousuario`) values ('$idusuario','$saldousuario')";
			if(mysql_query($sql_insert)){
				echo "<br>Log atualizado com sucesso!";
			}else{
				echo "<br>Ocorreu um erro ao atualizar Log!";
			}
			echo "<br>log atualizado, saldo nao alterado";
		}
	}else {
		$acesso = 3;
		echo "<br>cartao nao CADASTRADO!";
	}
	$url = "http://192.168.0.16/0001";
	echo "<IFRAME name=arduino src=";
	echo "$url";
	echo " width=100 height=100 frameborder=1 scrolling=auto></IFRAME>";
//acesso==1 PREMITIDO
//acesso==2 NEGADO POR FALTA DE SALDO
//acesso==3 CARTAO NAO CADASTRADO	
?>
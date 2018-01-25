<!DOCTYPE html>
<html>
	<head>
		<meta charset="utf-8">
		<title>Log BU</title>
		

		
	</head>
	<body>
		<center>
		<h1>Log BU</h1>
		
		
		<table>
			
			<tr>
				<td><b>ID</b></td>
				<td><b>Nome</b></td>
				<td><b>CPF</b></td>
				<td><b>Matricula</b></td>
				<td><b>Cartao</b></td>
				<td><b>Email</b></td>
				<td><b>Telefone</b></td>
				<td><b>Data e Hora</b></td>
				<td><b>Saldo</b></td>
				
			<?php
				include("conecta.php");
				echo $_POST['nome']; // print João da Silva
				echo $_POST['email'];
				$cor = 0;
				$buscalog = "SELECT * FROM `log` ORDER BY datahora DESC;";
				$resultlog = mysql_query($buscalog);
				while($linhalog = mysql_fetch_array($resultlog)){
					$buscausuario = "SELECT * FROM `usuarios` WHERE (idusuarios LIKE ".$linhalog["usuarios_idusuarios"].");";
					$resultusuario = mysql_query($buscausuario);
					$linhausuario = mysql_fetch_array($resultusuario);
					
					if($cor == 0){
						echo "<tr bgcolor=\"#B0E0E6\">";
						$cor = 1;
					}else{
						echo "<tr bgcolor=\"#E0FFFF\">";
						$cor = 0;
					}
							echo '<td>'.$linhausuario["idusuarios"].'</td>';
							echo '<td>'.$linhausuario["nome"].'</td>';
							echo '<td>'.$linhausuario["CPF"].'</td>';
							echo '<td>'.$linhausuario["matricula"].'</td>';
							echo '<td>'.$linhausuario["cartao"].'</td>';
							echo '<td>'.$linhausuario["email"].'</td>';
							echo '<td>'.$linhausuario["telefone"].'</td>';
							echo '<td>'.date('d/m/Y - H:i:s', strtotime($linhalog["datahora"])).'</td>';
							echo '<td>'."R$ ".$linhalog["saldousuario"].'</td>';
						echo '</tr>';
						
				}

			?>
			
			
		</table>
		</center>
	</body>
</html>
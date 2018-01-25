<!DOCTYPE html>
<html>
	<head>
		<meta charset="utf-8">
		<title>Log BU</title>

	</head>
	<body>
		<center>
		<h1><a href="log.php">Log BU</a></h1>


		<table>
			<tr>
				<td><b>ID</b></td>
				<td><b>Nome</b></td>
				<td><b>Matricula</b></td>
				<td><b>Cartao</b></td>
				<td><b>Email</b></td>
				<td><b>Telefone</b></td>
				<td><b>Data e Hora (yyyy-mm-dd)<br/> De &nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp Até </b></td>
				<td><b>Saldo <br/> (= > < >= <=)</b></td>
				<td><b>Ordenar por</b></td>
			</tr>

			<form action="log.php" name="formulario" method="get">
				<tr>
					<td><input type="text" id="usuarios_idusuarios" name="usuarios_idusuarios" size="1px"/></td>
					<td><input type="text" id="nome" name="nome" size="30px"/></td>
					<td><input type="text" id="matricula" name="matricula" size="10px"/></td>
					<td><input type="text" id="cartao" name="cartao" size="10px"/></td>
					<td><input type="text" id="email" name="email" size="20px"/></td>
					<td><input type="text" id="telefone" name="telefone" size="10px"/></td>
					<td><input type="text" id="datahoraini" name="datahoraini" size="10px"/>
					<input type="text" id="datahorafim" name="datahorafim" size="10px"/></td>
					<td><input type="text" id="saldousuario" name="saldousuario" size="10spx"/></td>
					<td>
						<select name="orderby">
						 <option value="usuarios_idusuarios">ID</option>
						 <option value="nome">Nome</option>
						 <option value="matricula">Matricula</option>
						 <option value="cartao">Cartao</option>
						 <option value="email">Email</option>
						 <option value="telefone">Telefone</option>
						 <option value="datahora">Data Hora</option>
						 <option value="saldousuario">Saldo</option>
						 <option selected="Escolha:" value="">Escolha: </option>
						</select>
					</td>
					<td><input type="submit" value="Buscar"/></td>
				</tr>
			</form>
			<?php
				include("conecta.php");
				$cor = 0;

				if (empty($_SERVER['QUERY_STRING']))//caso nao seja passado nada via get
				{
     			$buscalog = "SELECT * FROM `log` ORDER BY datahora DESC;";
				}else //caso receba dados via get
				{
					$flag = 0; //0->WHERE 1->AND
					$buscalog = "SELECT * FROM `log`";
					if (!empty($_GET['usuarios_idusuarios']))
					{
						$buscalog .= " WHERE usuarios_idusuarios = ".$_GET['usuarios_idusuarios'];
						$flag = 1;
					}
					if (!empty($_GET['datahoraini']) && !empty($_GET['datahorafim']))
					{
						if($flag == 0)
						{
							$buscalog .= " WHERE DATE(datahora) BETWEEN DATE('".$_GET['datahoraini']."') AND DATE('".$_GET['datahorafim']."')";
							$flag = 1;
						}else {
							$buscalog .= " AND DATE(datahora) BETWEEN DATE('".$_GET['datahoraini']."') AND DATE('".$_GET['datahorafim']."')";
						}

					}
					if (!empty($_GET['saldousuario']))
					{
						if($flag == 0)
						{
							$buscalog .= " WHERE saldousuario ".$_GET['saldousuario'];
							$flag =1;
						}else {
							$buscalog .= " AND saldousuario ".$_GET['saldousuario'];
						}
					}
					$orderby = 0;
					if($_GET['orderby'] == "usuarios_idusuarios" || $_GET['orderby'] == "datahora" || $_GET['orderby'] == "saldousuario")
					{
						$buscalog .= " ORDER BY ".$_GET['orderby']." DESC";
						$orderby = 1;
					}else {
						$buscalog .= " ORDER BY datahora DESC";
					}
				}
				echo "<br><b>LOG: </b>".$buscalog;


				$resultlog = mysql_query($buscalog);
				while($linhalog = mysql_fetch_array($resultlog))
				{
					$buscausuario = "SELECT * FROM `usuarios` WHERE idusuarios = ".$linhalog["usuarios_idusuarios"];
					if (!empty($_SERVER['QUERY_STRING']))//caso nao seja passado nada via get
					{
						if (!empty($_GET['nome'])) $buscausuario .= " AND nome LIKE \"".$_GET['nome']."\"";
						if (!empty($_GET['matricula'])) $buscausuario .= " AND matricula LIKE \"".$_GET['matricula']."\"";
						if (!empty($_GET['cartao'])) $buscausuario .= " AND cartao LIKE \"".$_GET['cartao']."\"";
						if (!empty($_GET['email'])) $buscausuario .= " AND email LIKE \"".$_GET['email']."\"";
						if (!empty($_GET['telefone'])) $buscausuario .= " AND telefone LIKE \"".$_GET['telefone']."\"";
						if($orderby == 0 && !empty($_GET['orderby'])) $buscausuario .= " ORDER BY ".$_GET['orderby']." DESC";
					}

					$resultusuario = mysql_query($buscausuario);
					$linhausuario = mysql_fetch_array($resultusuario);
					if(!$linhausuario)continue;

					if($cor == 0)
					{
						echo "<tr bgcolor=\"#B0E0E6\">";
						$cor = 1;
					}else
					{
						echo "<tr bgcolor=\"#E0FFFF\">";
						$cor = 0;
					}
							echo '<td>'.$linhausuario["idusuarios"].'</td>';
							echo '<td>'.$linhausuario["nome"].'</td>';
							echo '<td>'.$linhausuario["matricula"].'</td>';
							echo '<td>'.$linhausuario["cartao"].'</td>';
							echo '<td>'.$linhausuario["email"].'</td>';
							echo '<td>'.$linhausuario["telefone"].'</td>';
							echo '<td>'.date('d/m/Y - H:i:s', strtotime($linhalog["datahora"])).'</td>';
							echo '<td>'."R$ ".$linhalog["saldousuario"].'</td>';
						echo '</tr>';

				}
				echo "<br><b>USUARIOS: </b>".$buscausuario;
			?>


		</table>
		</center>
	</body>
</html>

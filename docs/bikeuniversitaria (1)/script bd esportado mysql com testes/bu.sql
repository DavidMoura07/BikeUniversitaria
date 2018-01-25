-- phpMyAdmin SQL Dump
-- version 4.5.1
-- http://www.phpmyadmin.net
--
-- Host: 127.0.0.1
-- Generation Time: 06-Out-2016 às 12:36
-- Versão do servidor: 10.1.10-MariaDB
-- PHP Version: 5.5.30

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `bu`
--

-- --------------------------------------------------------

--
-- Estrutura da tabela `log`
--

CREATE TABLE `log` (
  `idlog` int(10) UNSIGNED NOT NULL,
  `usuarios_idusuarios` int(10) UNSIGNED NOT NULL,
  `datahora` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_hungarian_ci;

--
-- Extraindo dados da tabela `log`
--

INSERT INTO `log` (`idlog`, `usuarios_idusuarios`, `datahora`) VALUES
(1, 1, '2016-10-05 06:45:33'),
(2, 2, '2016-10-05 06:50:33'),
(3, 2, '2016-10-05 23:35:25');

-- --------------------------------------------------------

--
-- Estrutura da tabela `usuarios`
--

CREATE TABLE `usuarios` (
  `idusuarios` int(10) UNSIGNED NOT NULL,
  `cartao` varchar(20) COLLATE utf8_hungarian_ci NOT NULL,
  `nome` varchar(50) COLLATE utf8_hungarian_ci NOT NULL,
  `matricula` decimal(10,0) NOT NULL,
  `senha` char(32) COLLATE utf8_hungarian_ci NOT NULL,
  `email` varchar(100) COLLATE utf8_hungarian_ci NOT NULL,
  `telefone` varchar(15) COLLATE utf8_hungarian_ci DEFAULT NULL,
  `saldo` float UNSIGNED DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_hungarian_ci;

--
-- Extraindo dados da tabela `usuarios`
--

INSERT INTO `usuarios` (`idusuarios`, `cartao`, `nome`, `matricula`, `senha`, `email`, `telefone`, `saldo`) VALUES
(1, '01139152', 'DAVID DE MOURA MARQUES', '2014100674', '0702', 'mouradavid8@gmail.com', '27996307860', 10),
(2, '01234567', 'DENER SILVA', '2015100123', 'DENERBOY', 'dener_silva@gmail.com', '2733337070', 12.5);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `log`
--
ALTER TABLE `log`
  ADD PRIMARY KEY (`idlog`),
  ADD UNIQUE KEY `idlog_UNIQUE` (`idlog`),
  ADD KEY `fk_log_usuarios_idx` (`usuarios_idusuarios`);

--
-- Indexes for table `usuarios`
--
ALTER TABLE `usuarios`
  ADD PRIMARY KEY (`idusuarios`),
  ADD UNIQUE KEY `idusuarios_UNIQUE` (`idusuarios`),
  ADD UNIQUE KEY `cartao_UNIQUE` (`cartao`),
  ADD UNIQUE KEY `matricula_UNIQUE` (`matricula`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `log`
--
ALTER TABLE `log`
  MODIFY `idlog` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;
--
-- AUTO_INCREMENT for table `usuarios`
--
ALTER TABLE `usuarios`
  MODIFY `idusuarios` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;
--
-- Constraints for dumped tables
--

--
-- Limitadores para a tabela `log`
--
ALTER TABLE `log`
  ADD CONSTRAINT `fk_log_usuarios` FOREIGN KEY (`usuarios_idusuarios`) REFERENCES `usuarios` (`idusuarios`) ON DELETE NO ACTION ON UPDATE NO ACTION;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;

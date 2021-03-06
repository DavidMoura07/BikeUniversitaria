-- MySQL Script generated by MySQL Workbench
-- 10/05/16 23:00:56
-- Model: New Model    Version: 1.0
-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

-- -----------------------------------------------------
-- Schema bu
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema bu
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `bu` DEFAULT CHARACTER SET utf8 COLLATE utf8_hungarian_ci ;
USE `bu` ;

-- -----------------------------------------------------
-- Table `bu`.`usuarios`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `bu`.`usuarios` (
  `idusuarios` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `cartao` VARCHAR(20) NOT NULL,
  `nome` VARCHAR(50) NOT NULL,
  `matricula` DECIMAL(10,0) NOT NULL,
  `senha` CHAR(32) NOT NULL,
  `email` VARCHAR(100) NOT NULL,
  `telefone` VARCHAR(15) NULL,
  `saldo` FLOAT UNSIGNED NULL,
  PRIMARY KEY (`idusuarios`),
  UNIQUE INDEX `idusuarios_UNIQUE` (`idusuarios` ASC),
  UNIQUE INDEX `cartao_UNIQUE` (`cartao` ASC),
  UNIQUE INDEX `matricula_UNIQUE` (`matricula` ASC))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `bu`.`log`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `bu`.`log` (
  `idlog` INT UNSIGNED NOT NULL AUTO_INCREMENT,
  `usuarios_idusuarios` INT UNSIGNED NOT NULL,
  `datahora` DATETIME NOT NULL,
  PRIMARY KEY (`idlog`),
  INDEX `fk_log_usuarios_idx` (`usuarios_idusuarios` ASC),
  UNIQUE INDEX `idlog_UNIQUE` (`idlog` ASC),
  CONSTRAINT `fk_log_usuarios`
    FOREIGN KEY (`usuarios_idusuarios`)
    REFERENCES `bu`.`usuarios` (`idusuarios`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;

CREATE DATABASE db_jogo_nim;

USE db_jogo_nim;

CREATE TABLE usu_usuario (
    usu_id_usuario int not null,
    usu_nome varchar(50) not null,
    usu_email varchar(75),
    usu_senha varchar(50) not null,
    usu_data_criacao date,
    CONSTRAINT pk_usu PRIMARY KEY (usu_id_usuario),
    CONSTRAINT un_usu_nome UNIQUE (usu_nome)
) Engine = InnoDB;

CREATE TABLE rec_recorde (
    rec_id_recorde int not null,
    rec_pontos int,
    rec_qnt_linha int,
    rec_data date,
    rec_id_usuario int,
    CONSTRAINT pk_rec PRIMARY KEY (rec_id_recorde)
) Engine = InnoDB;

INSERT INTO usu_usuario (usu_id_usuario, usu_nome, usu_email, usu_senha, usu_data_criacao) VALUES (1, 'Computador', null, '3hf03uKUT9AFa4vAt4FEdpe32c5SGHiKUy288gz', null);
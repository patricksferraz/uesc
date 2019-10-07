# CRIAÇÃO DA VIEW PARA DW

USE db_biblioteca;

CREATE OR REPLACE VIEW view_dw_biblioteca AS
SELECT Devolucao.id_emprestimo AS dev_id_emprestimo,
  Devolucao.data_devolucao AS dev_data,
  Devolucao.horario_devolucao AS  dev_horario,
  Devolucao.id_funcionario AS dev_id_funcionario,
  Emprestimo.id AS emp_id,
  Emprestimo.data_emprestimo AS emp_data_emprestimo,
  Emprestimo.horario_emprestimo AS emp_horario_emprestimo,
  Emprestimo.data_retorno AS emp_data_retorno,
  Emprestimo.id_usuario AS emp_id_usuario,
  Emprestimo.id_obra AS emp_id_obra,
  Emprestimo.id_funcionario AS emp_id_funcionario,
  Funcionario.id AS fun_id,
  Funcionario.matricula AS fun_matricula,
  Funcionario.senha AS fun_senha,
  Funcionario.nome AS fun_nome,
  Funcionario.cargo AS fun_cargo,
  Obra.id AS obr_id,
  Obra.titulo AS obr_titulo,
  Obra.ano AS obr_ano,
  Obra.tipo AS obr_tipo,
  Obra.assunto AS obr_assunto,
  Obra.quantidade_exemplares AS obr_quantidade_exemplares,
  Obra.preco_exemplar AS obr_preco_exemplar,
  Obra.nome_editora AS obr_nome_editora,
  Obra.cidade_editora AS obr_cidade_editora,
  Obra.nomes_autor AS obr_nomes_autor,
  Reserva.id AS res_id,
  Reserva.data_reserva AS res_data_reserva,
  Reserva.horario_reserva AS res_horario_reserva,
  Reserva.data_retirada AS res_data_retirada,
  Reserva.id_usuario AS res_id_usuario,
  Reserva.id_obra AS res_id_obra,
  Usuario.id AS usu_id,
  Usuario.matricula AS usu_matricula,
  Usuario.senha AS usu_senha,
  Usuario.nome AS usu_nome,
  Usuario.cpf AS usu_cpf,
  Usuario.telefone AS usu_telefone,
  Usuario.data_nascimento AS usu_data_nascimento,
  Usuario.end_cep AS usu_end_cep,
  Usuario.end_logradouro AS usu_end_logradouro,
  Usuario.end_numero AS usu_end_numero,
  Usuario.end_complemento AS usu_end_complemento,
  Usuario.end_bairro AS usu_end_bairro,
  Usuario.end_cidade AS usu_end_cidade,
  Usuario.end_uf AS usu_end_uf
FROM db_biblioteca.Emprestimo Emprestimo
  INNER JOIN db_biblioteca.Devolucao Devolucao
  ON Emprestimo.id = Devolucao.id_emprestimo
  INNER JOIN db_biblioteca.Funcionario Funcionario
  ON Emprestimo.id_funcionario = Funcionario.id
  INNER JOIN db_biblioteca.Obra Obra
  ON Emprestimo.id_obra = Obra.id
  INNER JOIN db_biblioteca.Usuario Usuario
  ON Emprestimo.id_usuario = Usuario.id
  INNER JOIN db_biblioteca.Reserva Reserva
  ON Usuario.id = Reserva.id_usuario;

# CRIAÇÃO DO DW

CREATE DATABASE dw_biblioteca;

# CRIAÇÃO DAS DIMENSÕES E FATO

CREATE TABLE IF NOT EXISTS dw_biblioteca.dim_obra (
  id int NOT NULL AUTO_INCREMENT COMMENT '',
  codObra INT NULL COMMENT '',
  titulo varchar(150) NULL COMMENT '',
  ano int NULL COMMENT '',
  tipo varchar(50) NULL COMMENT '',
  assunto varchar(50) NULL COMMENT '',
  nome_editora varchar(50) NULL COMMENT '',
  cidade_editora varchar(50) NULL COMMENT '',
  nomes_autor varchar(50) NULL COMMENT '',
  CONSTRAINT pk_dim_obra PRIMARY KEY (id) COMMENT ''
) ENGINE = InnoDB;

CREATE TABLE IF NOT EXISTS dw_biblioteca.dim_funcionario (
  id int NOT NULL AUTO_INCREMENT COMMENT '',
  codFuncionario INT NULL COMMENT '',
  matricula varchar(50) NULL COMMENT '',
  nome varchar(50) NULL COMMENT '',
  cargo varchar(50) NULL COMMENT '',
  CONSTRAINT pk_dim_funcionario PRIMARY KEY (id) COMMENT ''
) ENGINE = InnoDB;

CREATE TABLE IF NOT EXISTS dw_biblioteca.dim_usuario (
  id INT NOT NULL AUTO_INCREMENT COMMENT '',
  codUsuario INT NULL COMMENT '',
  matricula VARCHAR(50) NULL COMMENT '',
  nome VARCHAR(50) NULL COMMENT '',
  cpf VARCHAR(50) NULL COMMENT '',
  telefone VARCHAR(50) NULL COMMENT '',
  data_nascimento DATE NULL COMMENT '',
  end_cep VARCHAR(50) NULL COMMENT '',
  end_logradouro VARCHAR(50) NULL COMMENT '',
  end_numero INT NULL COMMENT '',
  end_complemento VARCHAR(50) NULL COMMENT '',
  end_bairro VARCHAR(50) NULL COMMENT '',
  end_cidade VARCHAR(50) NULL COMMENT '',
  end_uf VARCHAR(50) NULL COMMENT '',
  CONSTRAINT pk_usuario PRIMARY KEY (id) COMMENT ''
) ENGINE = InnoDB;

CREATE TABLE IF NOT EXISTS dw_biblioteca.dim_data (
  id INT NOT NULL AUTO_INCREMENT COMMENT '',
  data_emprestimo date NULL COMMENT '',
  dia_emprestimo int NULL COMMENT '',
  mes_emprestimo int NULL COMMENT '',
  ano_emprestimo int NULL COMMENT '',
  semana_emprestimo int NULL COMMENT '',
  dia_semana_emprestimo int NULL COMMENT '',
  horario_emprestimo time NULL COMMENT '',
  hora_emprestimo int NULL COMMENT '',
  data_retorno date NULL COMMENT '',
  dia_retorno int NULL COMMENT '',
  mes_retorno int NULL COMMENT '',
  ano_retorno int NULL COMMENT '',
  semana_retorno int NULL COMMENT '',
  dia_semana_retorno int NULL COMMENT '',
  data_devolucao date NULL COMMENT '',
  dia_devolucao int NULL COMMENT '',
  mes_devolucao int NULL COMMENT '',
  ano_devolucao int NULL COMMENT '',
  semana_devolucao int NULL COMMENT '',
  dia_semana_devolucao int NULL COMMENT '',
  horario_devolucao time NULL COMMENT '',
  hora_devolucao int NULL COMMENT '',
  CONSTRAINT pk_dim_data PRIMARY KEY (id) COMMENT ''
) ENGINE = InnoDB;

CREATE TABLE IF NOT EXISTS dw_biblioteca.fat_biblioteca (
  id INT NOT NULL AUTO_INCREMENT COMMENT '',
  id_dim_usuario INT NULL COMMENT '',
  id_dim_obra INT NULL COMMENT '',
  id_dim_funcionario INT NULL COMMENT '',
  id_dim_data INT NULL COMMENT '',
  obra_devolvida BOOLEAN NULL COMMENT '',
  preco_obra DECIMAL(12,2) NULL COMMENT '',
  quantidade_obra INT NULL COMMENT '',
  total_preco_obra DECIMAL(32,2) NULL COMMENT '',
  CONSTRAINT pk_fat_biblioteca PRIMARY KEY (id) COMMENT '',
  CONSTRAINT fk_fat_biblioteca_dim_usuario FOREIGN KEY (id_dim_usuario)
    REFERENCES dim_usuario (id),
  CONSTRAINT fk_fat_biblioteca_dim_obra FOREIGN KEY (id_dim_obra)
    REFERENCES dim_obra (id),
  CONSTRAINT fk_fat_biblioteca_dim_funcionario FOREIGN KEY (id_dim_funcionario)
    REFERENCES dim_funcionario (id),
  CONSTRAINT fk_fat_biblioteca_dim_data FOREIGN KEY (id_dim_data)
    REFERENCES dim_data (id)
) ENGINE = InnoDB;

# INSERTS DW

# Obra
INSERT INTO dw_biblioteca.dim_obra (codObra, titulo, ano, tipo, assunto, nome_editora, cidade_editora, nomes_autor)
SELECT obr_id, obr_titulo, obr_ano, obr_tipo, obr_assunto, obr_nome_editora, obr_cidade_editora, obr_nomes_autor
FROM db_biblioteca.view_dw_biblioteca;

# Funcionario
INSERT INTO dw_biblioteca.dim_funcionario (codFuncionario, matricula, nome, cargo)
SELECT fun_id, fun_matricula, fun_nome, fun_cargo
FROM db_biblioteca.view_dw_biblioteca;

# Usuário
INSERT INTO dw_biblioteca.dim_usuario (codUsuario, matricula, nome, cpf, telefone, data_nascimento, end_cep, end_logradouro, end_numero, end_complemento, end_bairro, end_cidade, end_uf)
SELECT usu_id, usu_matricula, usu_nome, usu_cpf, usu_telefone, usu_data_nascimento, usu_end_cep, usu_end_logradouro, usu_end_numero, usu_end_complemento, usu_end_bairro, usu_end_cidade, usu_end_uf
FROM db_biblioteca.view_dw_biblioteca;

# Datas
INSERT INTO dw_biblioteca.dim_data (data_emprestimo, dia_emprestimo, mes_emprestimo, ano_emprestimo, semana_emprestimo, dia_semana_emprestimo, horario_emprestimo, hora_emprestimo, data_retorno, dia_retorno, mes_retorno, ano_retorno, semana_retorno, dia_semana_retorno, data_devolucao, dia_devolucao, mes_devolucao, ano_devolucao, semana_devolucao, dia_semana_devolucao, horario_devolucao, hora_devolucao)
SELECT emp_data_emprestimo, DAY(emp_data_emprestimo), MONTH(emp_data_emprestimo), YEAR(emp_data_emprestimo), WEEKOFYEAR(emp_data_emprestimo), DAYOFWEEK(emp_horario_emprestimo), emp_horario_emprestimo, HOUR(emp_horario_emprestimo), emp_data_retorno, DAY(emp_data_retorno), MONTH(emp_data_retorno), YEAR(emp_data_retorno), WEEKOFYEAR(emp_data_retorno), DAYOFWEEK(emp_data_retorno), dev_data, DAY(dev_data), MONTH(dev_data), YEAR(dev_data), WEEKOFYEAR(dev_data), DAYOFWEEK(dev_data), dev_horario, HOUR(dev_horario)
FROM db_biblioteca.view_dw_biblioteca;

# Fato
INSERT INTO dw_biblioteca.fat_biblioteca (obra_devolvida, preco_obra, quantidade_obra, total_preco_obra)
SELECT IF(dev_data <> NULL, true, false), obr_preco_exemplar, obr_quantidade_exemplares, obr_preco_exemplar*obr_quantidade_exemplares
FROM view_dw_biblioteca;

UPDATE dw_biblioteca.fat_biblioteca SET id_dim_usuario = id, id_dim_obra = id, id_dim_funcionario = id, id_dim_data = id;

# Atualização devoluções
UPDATE dw_biblioteca.fat_biblioteca SET obra_devolvida = 1 WHERE (fat_biblioteca.id % 2 = 0);
UPDATE dw_biblioteca.dim_data SET data_devolucao = NULL,
  dia_devolucao = NULL, mes_devolucao = NULL, ano_devolucao = NULL,
  semana_devolucao = NULL, dia_semana_devolucao = NULL, horario_devolucao = NULL,
  hora_devolucao = NULL
WHERE dim_data.id IN  (SELECT fat_biblioteca.id FROM fat_biblioteca WHERE obra_devolvida = 0);
DROP DATABASE IF EXISTS hospital;
CREATE DATABASE hospital;

USE hospital;

DROP TABLE IF EXISTS Medico;
CREATE TABLE Medico(
  id   INTEGER     NOT NULL AUTO_INCREMENT,
  nome VARCHAR(50) NOT NULL,
  sexo CHAR        NOT NULL,
  crm  INTEGER     NOT NULL,
  nacionalidade VARCHAR(30) NOT NULL,
  dtNasc DATE NOT NULL,
  dtAdmiss DATE NOT NULL,
  dtFormatura DATE NOT NULL,
  PRIMARY KEY (id)
);

SELECT * FROM Medico;

DROP TABLE IF EXISTS Enfermeiro;
CREATE TABLE Enfermeiro(
  id   INTEGER     NOT NULL AUTO_INCREMENT,
  nome VARCHAR(50) NOT NULL,
  sexo CHAR        NOT NULL,
  coren  INTEGER     NOT NULL,
  nacionalidade VARCHAR(30) NOT NULL,
  dtNasc DATE NOT NULL,
  dtAdmiss DATE NOT NULL,
  dtFormatura DATE NOT NULL,
  PRIMARY KEY (id)
);

SELECT * FROM Enfermeiro;

DROP TABLE IF EXISTS Auxiliar;
CREATE TABLE Auxiliar(
  id   INTEGER     NOT NULL AUTO_INCREMENT,
  nome VARCHAR(50) NOT NULL,
  sexo CHAR        NOT NULL,
  coren  INTEGER     NOT NULL,
  nacionalidade VARCHAR(30) NOT NULL,
  dtNasc DATE NOT NULL,
  dtAdmiss DATE NOT NULL,
  dtFormatura DATE NOT NULL,
  PRIMARY KEY (id)
);

SELECT * FROM Auxiliar;

DROP TABLE IF EXISTS Procedimento;
CREATE TABLE Procedimento(
  id INTEGER NOT NULL AUTO_INCREMENT,
  codigo INTEGER NOT NULL,
  descricao VARCHAR(100) NOT NULL,
  valor DECIMAL(10, 2) NOT NULL,
  PRIMARY KEY (id)
);

SELECT * FROM Procedimento;

DROP TABLE IF EXISTS Especialidade;
CREATE TABLE Especialidade(
  id INTEGER NOT NULL AUTO_INCREMENT,
  codigo INTEGER NOT NULL,
  descricao VARCHAR(100) NOT NULL,
  PRIMARY KEY (id)
);

SELECT * FROM Especialidade;

DROP TABLE IF EXISTS Equipamento;
CREATE TABLE Equipamento(
  id INTEGER NOT NULL AUTO_INCREMENT,
  codigo INTEGER NOT NULL,
  descricao VARCHAR(100) NOT NULL,
  valor DECIMAL(10, 2) NOT NULL,
  PRIMARY KEY (id)
);

SELECT * FROM Equipamento;

DROP TABLE IF EXISTS Tombo;
CREATE TABLE Tombo(
  id INTEGER NOT NULL AUTO_INCREMENT,
  id_equipamento INTEGER NOT NULL,
  codigoTombo VARCHAR(10) NOT NULL,
  PRIMARY KEY (id),
  FOREIGN KEY (id_equipamento) REFERENCES Equipamento(id)
);

SELECT * FROM Tombo;

DROP TABLE IF EXISTS Material;
CREATE TABLE Material(
  id INTEGER NOT NULL AUTO_INCREMENT,
  codigo INTEGER NOT NULL,
  descricao VARCHAR(100) NOT NULL,
  valor DECIMAL(10, 2) NOT NULL,
  PRIMARY KEY (id)
);

SELECT * FROM Material;


DROP TABLE IF EXISTS MaterialProcedimento;
CREATE TABLE MaterialProcedimento(
  id INTEGER NOT NULL AUTO_INCREMENT,
  id_material INTEGER NOT NULL,
  id_procedimento INTEGER NOT NULL,
  PRIMARY KEY (id),
  FOREIGN KEY (id_material) REFERENCES Material(id),
  FOREIGN KEY (id_procedimento) REFERENCES Procedimento(id)
);

SELECT * FROM MaterialProcedimento;

DROP TABLE IF EXISTS EquipamentoProcedimento;
CREATE TABLE EquipamentoProcedimento(
  id INTEGER NOT NULL AUTO_INCREMENT,
  id_equipamento INTEGER NOT NULL,
  id_procedimento INTEGER NOT NULL,
  PRIMARY KEY (id),
  FOREIGN KEY (id_equipamento) REFERENCES Equipamento(id),
  FOREIGN KEY (id_procedimento) REFERENCES Procedimento(id)
);

SELECT * FROM EquipamentoProcedimento;


DROP PROCEDURE IF EXISTS insert_equipamento;
DELIMITER $$
CREATE PROCEDURE insert_equipamento(IN pCodigo INT, IN pDescricao VARCHAR(100), IN pValor DECIMAL(10, 2))
BEGIN
  INSERT INTO Equipamento (codigo, descricao, valor) VALUES (pCodigo, pDescricao, pValor);
END $$
DELIMITER ;

DROP PROCEDURE IF EXISTS get_equipamento_by_code;
DELIMITER $$
CREATE PROCEDURE get_equipamento_by_code(IN pCodigo INT)
BEGIN
  SELECT * FROM Equipamento WHERE codigo = pCodigo;
END $$
DELIMITER ;

DROP PROCEDURE IF EXISTS insert_tombo;
DELIMITER $$
CREATE PROCEDURE insert_tombo(IN pId_equipamento INT, IN pCodigoTombo VARCHAR(10))
BEGIN
  INSERT INTO Tombo (id_equipamento, codigoTombo) VALUES (pId_equipamento, pCodigoTombo);
END $$
DELIMITER ;

DROP PROCEDURE IF EXISTS get_tombo_by_code;
DELIMITER $$
CREATE PROCEDURE get_tombo_by_code(IN pCodigoTombo VARCHAR(10))
BEGIN
  SELECT Tombo.codigoTombo, E.codigo codigoEquipamento FROM Tombo INNER JOIN Equipamento E ON Tombo.id_equipamento = E.id WHERE codigoTombo = pCodigoTombo;
END $$
DELIMITER ;

DROP PROCEDURE IF EXISTS insert_especialidade;
DELIMITER $$
CREATE PROCEDURE insert_especialidade(IN pCodigo INT, IN pDescricao VARCHAR(100))
BEGIN
  INSERT INTO Especialidade (codigo, descricao) VALUES (pCodigo, pDescricao);
END $$
DELIMITER ;

DROP PROCEDURE IF EXISTS get_especialidade_by_code;
DELIMITER $$
CREATE PROCEDURE get_especialidade_by_code(IN pCodigo INT)
BEGIN
  SELECT * FROM Especialidade WHERE codigo = pCodigo;
END $$
DELIMITER ;

DROP PROCEDURE IF EXISTS get_especialidade_by_description;
DELIMITER $$
CREATE PROCEDURE get_especialidade_by_description(IN pDescricao VARCHAR(100))
BEGIN
  SELECT * FROM Especialidade WHERE descricao = pDescricao;
END $$
DELIMITER ;

DROP PROCEDURE IF EXISTS insert_medico;
DELIMITER $$
CREATE PROCEDURE insert_medico(IN pNome VARCHAR(50), IN pSexo CHAR, IN pCrm INT, IN pNacionalidade VARCHAR(30), IN pDtNasc DATE, IN pDtAdmiss DATE, IN pDtFormatura DATE )
BEGIN
  INSERT INTO Medico (nome, sexo, crm, nacionalidade, dtNasc, dtAdmiss, dtFormatura) VALUES (pNome, pSexo, pCrm, pNacionalidade, pDtNasc, pDtAdmiss, pDtFormatura);
END $$
DELIMITER ;

DROP PROCEDURE IF EXISTS insert_enfermeiro;
DELIMITER $$
CREATE PROCEDURE insert_enfermeiro(IN pNome VARCHAR(50), IN pSexo CHAR, IN pCoren INT, IN pNacionalidade VARCHAR(30), IN pDtNasc DATE, IN pDtAdmiss DATE, IN pDtFormatura DATE )
BEGIN
  INSERT INTO Enfermeiro (nome, sexo, coren, nacionalidade, dtNasc, dtAdmiss, dtFormatura) VALUES (pNome, pSexo, pCoren, pNacionalidade, pDtNasc, pDtAdmiss, pDtFormatura);
END $$
DELIMITER ;

DROP PROCEDURE IF EXISTS insert_auxiliar;
DELIMITER $$
CREATE PROCEDURE insert_auxiliar(IN pNome VARCHAR(50), IN pSexo CHAR, IN pCoren INT, IN pNacionalidade VARCHAR(30), IN pDtNasc DATE, IN pDtAdmiss DATE, IN pDtFormatura DATE )
BEGIN
  INSERT INTO Auxiliar (nome, sexo, coren, nacionalidade, dtNasc, dtAdmiss, dtFormatura) VALUES (pNome, pSexo, pCoren, pNacionalidade, pDtNasc, pDtAdmiss, pDtFormatura);
END $$
DELIMITER ;

DROP PROCEDURE IF EXISTS get_medico_by_code;
DELIMITER $$
CREATE PROCEDURE get_medico_by_code(IN pCrm INT)
BEGIN
  SELECT id, nome, crm, sexo, nacionalidade, DATE_FORMAT(dtNasc,'%d/%m/%Y') AS dataNasc, DATE_FORMAT(dtAdmiss,'%d/%m/%Y') AS dataAdmiss, DATE_FORMAT(dtFormatura,'%d/%m/%Y') AS dataFormatura FROM Medico WHERE crm = pCrm;
END $$
DELIMITER ;

DROP PROCEDURE IF EXISTS get_enfermeiro_by_code;
DELIMITER $$
CREATE PROCEDURE get_enfermeiro_by_code(IN pCoren INT)
BEGIN
  SELECT id, nome, coren, sexo, nacionalidade, DATE_FORMAT(dtNasc,'%d/%m/%Y') AS dataNasc, DATE_FORMAT(dtAdmiss,'%d/%m/%Y') AS dataAdmiss, DATE_FORMAT(dtFormatura,'%d/%m/%Y') AS dataFormatura FROM Enfermeiro WHERE coren = pCoren;
END $$
DELIMITER ;

DROP PROCEDURE IF EXISTS get_auxiliar_by_code;
DELIMITER $$
CREATE PROCEDURE get_auxiliar_by_code(IN pCoren INT)
BEGIN
  SELECT id, nome, coren, sexo, nacionalidade, DATE_FORMAT(dtNasc,'%d/%m/%Y') AS dataNasc, DATE_FORMAT(dtAdmiss,'%d/%m/%Y') AS dataAdmiss, DATE_FORMAT(dtFormatura,'%d/%m/%Y') AS dataFormatura FROM Auxiliar WHERE coren = pCoren;
END $$
DELIMITER ;

DROP PROCEDURE IF EXISTS get_medico_by_name;
DELIMITER $$
CREATE PROCEDURE get_medico_by_name(IN pNome VARCHAR(50))
BEGIN
  SELECT id, nome, crm, sexo, nacionalidade, DATE_FORMAT(dtNasc,'%d/%m/%Y') AS dataNasc, DATE_FORMAT(dtAdmiss,'%d/%m/%Y') AS dataAdmiss, DATE_FORMAT(dtFormatura,'%d/%m/%Y') AS dataFormatura FROM Medico WHERE nome = pNome;
END $$
DELIMITER ;

DROP PROCEDURE IF EXISTS get_enfermeiro_by_name;
DELIMITER $$
CREATE PROCEDURE get_enfermeiro_by_name(IN  pNome VARCHAR(50))
BEGIN
  SELECT id, nome, coren, sexo, nacionalidade, DATE_FORMAT(dtNasc,'%d/%m/%Y') AS dataNasc, DATE_FORMAT(dtAdmiss,'%d/%m/%Y') AS dataAdmiss, DATE_FORMAT(dtFormatura,'%d/%m/%Y') AS dataFormatura FROM Enfermeiro WHERE  nome = pNome;
END $$
DELIMITER ;

DROP PROCEDURE IF EXISTS get_auxiliar_by_name;
DELIMITER $$
CREATE PROCEDURE get_auxiliar_by_name(IN  pNome VARCHAR(50))
BEGIN
  SELECT id, nome, coren, sexo, nacionalidade, DATE_FORMAT(dtNasc,'%d/%m/%Y') AS dataNasc, DATE_FORMAT(dtAdmiss,'%d/%m/%Y') AS dataAdmiss, DATE_FORMAT(dtFormatura,'%d/%m/%Y') AS dataFormatura FROM Auxiliar WHERE  nome = pNome;
END $$
DELIMITER ;

DROP PROCEDURE IF EXISTS insert_material;
DELIMITER $$
CREATE PROCEDURE insert_material(IN pCodigo INT, IN pDescricao VARCHAR(100), IN pValor DECIMAL(10, 2))
BEGIN
  INSERT INTO Material (codigo, descricao, valor) VALUES (pCodigo, pDescricao, pValor);
END $$
DELIMITER ;

DROP PROCEDURE IF EXISTS get_material_by_code;
DELIMITER $$
CREATE PROCEDURE get_material_by_code(IN pCodigo INT)
BEGIN
  SELECT * FROM Material WHERE codigo = pCodigo;
END $$
DELIMITER ;

DROP PROCEDURE IF EXISTS insert_procedimento;
DELIMITER $$
CREATE PROCEDURE insert_procedimento(IN pCodigo INT, IN pDescricao VARCHAR(100), IN pValor DECIMAL(10, 2))
BEGIN
  INSERT INTO Procedimento (codigo, descricao, valor) VALUES (pCodigo, pDescricao, pValor);
END $$
DELIMITER ;

DROP PROCEDURE IF EXISTS get_procedimento_by_code;
DELIMITER $$
CREATE PROCEDURE get_procedimento_by_code(IN pCodigo INT)
BEGIN
  SELECT * FROM Procedimento WHERE codigo = pCodigo;
END $$
DELIMITER ;

DROP PROCEDURE IF EXISTS get_procedimento_by_description;
DELIMITER $$
CREATE PROCEDURE get_procedimento_by_description(IN pDescricao VARCHAR(100))
BEGIN
  SELECT * FROM Procedimento WHERE descricao = pDescricao;
END $$
DELIMITER ;

DROP PROCEDURE IF EXISTS insert_materialProcedimento;
DELIMITER $$
CREATE PROCEDURE insert_materialProcedimento(IN pId_material INT, IN pId_procedimento INT)
BEGIN
  INSERT INTO MaterialProcedimento (id_material, id_procedimento) VALUES (pId_material, pId_procedimento);
END $$
DELIMITER ;

DROP PROCEDURE IF EXISTS get_materialProcedimento_by_codigoProcedimento;
DELIMITER $$
CREATE PROCEDURE get_materialProcedimento_by_codigoProcedimento(IN pCodigo INT)
BEGIN
  SELECT Material.*, Procedimento.codigo codigoProcedimento FROM Material INNER JOIN MaterialProcedimento MP ON Material.id = MP.id_material INNER JOIN procedimento ON MP.id_procedimento = Procedimento.id WHERE Procedimento.codigo = pCodigo ORDER BY MP.id;
END $$
DELIMITER ;

DROP PROCEDURE IF EXISTS insert_equipamentoProcedimento;
DELIMITER $$
CREATE PROCEDURE insert_equipamentoProcedimento(IN pId_equipamento INT, IN pId_procedimento INT)
BEGIN
  INSERT INTO EquipamentoProcedimento (id_equipamento, id_procedimento) VALUES (pId_equipamento, pId_procedimento);
END $$
DELIMITER ;

DROP PROCEDURE IF EXISTS get_equipamentoProcedimento_by_codigoProcedimento;
DELIMITER $$
CREATE PROCEDURE get_equipamentoProcedimento_by_codigoProcedimento(IN pCodigo INT)
BEGIN
  SELECT Equipamento.*, P.codigo codigoProcedimento FROM Equipamento INNER JOIN EquipamentoProcedimento E ON Equipamento.id = E.id_equipamento INNER JOIN Procedimento P ON E.id_procedimento = P.id WHERE P.codigo = pCodigo ORDER BY E.id;
END $$
DELIMITER ;
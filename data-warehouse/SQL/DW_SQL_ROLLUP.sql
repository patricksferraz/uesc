## ------------------ ROLLUP ----------------------

-- EMPRESTIMOS DE OBRAS - CONTRAÇÃO
SELECT obr.titulo, data.data_emprestimo, data.ano_emprestimo, data.mes_emprestimo,
  data.semana_emprestimo, data.dia_emprestimo, count(obr.titulo) AS 'Total de emprestimos'
FROM dw_biblioteca.dim_obra obr, dw_biblioteca.dim_data data, dw_biblioteca.fat_biblioteca bib
WHERE bib.id_dim_obra = obr.id AND bib.id_dim_data = data.id
GROUP BY obr.titulo, data.data_emprestimo, data.ano_emprestimo, data.mes_emprestimo,
  data.semana_emprestimo, data.dia_emprestimo WITH ROLLUP;

SELECT obr.titulo, data.data_emprestimo, data.ano_emprestimo, data.mes_emprestimo,
  data.semana_emprestimo, count(obr.titulo) AS 'Total de emprestimos'
FROM dw_biblioteca.dim_obra obr, dw_biblioteca.dim_data data, dw_biblioteca.fat_biblioteca bib
WHERE bib.id_dim_obra = obr.id AND bib.id_dim_data = data.id
GROUP BY obr.titulo, data.data_emprestimo, data.ano_emprestimo, data.mes_emprestimo,
  data.semana_emprestimo WITH ROLLUP;

SELECT obr.titulo, data.data_emprestimo, data.ano_emprestimo, data.mes_emprestimo, count(obr.titulo) AS 'Total de emprestimos'
FROM dw_biblioteca.dim_obra obr, dw_biblioteca.dim_data data, dw_biblioteca.fat_biblioteca bib
WHERE bib.id_dim_obra = obr.id AND bib.id_dim_data = data.id
GROUP BY obr.titulo, data.data_emprestimo, data.ano_emprestimo, data.mes_emprestimo WITH ROLLUP;

SELECT obr.titulo, data.data_emprestimo, data.ano_emprestimo, count(obr.titulo) AS 'Total de emprestimos'
FROM dw_biblioteca.dim_obra obr, dw_biblioteca.dim_data data, dw_biblioteca.fat_biblioteca bib
WHERE bib.id_dim_obra = obr.id AND bib.id_dim_data = data.id
GROUP BY obr.titulo, data.data_emprestimo, data.ano_emprestimo WITH ROLLUP;

SELECT obr.titulo, IFNULL(data.data_emprestimo, 'Total geral'), count(obr.titulo) AS 'Total de emprestimos'
FROM dw_biblioteca.dim_obra obr, dw_biblioteca.dim_data data, dw_biblioteca.fat_biblioteca bib
WHERE bib.id_dim_obra = obr.id AND bib.id_dim_data = data.id
GROUP BY obr.titulo, data.data_emprestimo WITH ROLLUP;

-- EMPRESTIMOS DE OBRAS - EXPANSÃO
SELECT obr.titulo,
  IFNULL(data.ano_emprestimo, 'Total geral') AS 'ano_emprestimo',
  count(obr.titulo) AS 'Total de emprestimos'
FROM dw_biblioteca.dim_obra obr, dw_biblioteca.dim_data data, dw_biblioteca.fat_biblioteca bib
WHERE bib.id_dim_obra = obr.id AND bib.id_dim_data = data.id
GROUP BY obr.titulo, data.ano_emprestimo WITH ROLLUP;

SELECT obr.titulo,
  IFNULL(data.ano_emprestimo, 'Total geral') AS 'ano_emprestimo',
  IFNULL(data.mes_emprestimo, 'Total ano') AS 'mes_emprestimo',
  count(obr.titulo) AS 'Total de emprestimos'
FROM dw_biblioteca.dim_obra obr, dw_biblioteca.dim_data data, dw_biblioteca.fat_biblioteca bib
WHERE bib.id_dim_obra = obr.id AND bib.id_dim_data = data.id
GROUP BY obr.titulo, data.ano_emprestimo, data.mes_emprestimo WITH ROLLUP;

SELECT obr.titulo,
  IFNULL(data.ano_emprestimo, 'Total geral') AS 'ano_emprestimo',
  IFNULL(data.mes_emprestimo, 'Total ano') AS 'mes_emprestimo',
  IFNULL(data.semana_emprestimo, 'Total mes') AS 'semana_emprestimo',
  count(obr.titulo) AS 'Total de emprestimos'
FROM dw_biblioteca.dim_obra obr, dw_biblioteca.dim_data data, dw_biblioteca.fat_biblioteca bib
WHERE bib.id_dim_obra = obr.id AND bib.id_dim_data = data.id
GROUP BY obr.titulo, data.ano_emprestimo, data.mes_emprestimo,
  data.semana_emprestimo, data.dia_emprestimo WITH ROLLUP;

SELECT obr.titulo,
  IFNULL(data.ano_emprestimo, 'Total geral') AS 'ano_emprestimo',
  IFNULL(data.mes_emprestimo, 'Total ano') AS 'mes_emprestimo',
  IFNULL(data.semana_emprestimo, 'Total mes') AS 'semana_emprestimo',
  IFNULL(data.dia_emprestimo, 'Total semana') AS 'dia_emprestimo',
  count(obr.titulo) AS 'Total de emprestimos'
FROM dw_biblioteca.dim_obra obr, dw_biblioteca.dim_data data, dw_biblioteca.fat_biblioteca bib
WHERE bib.id_dim_obra = obr.id AND bib.id_dim_data = data.id
GROUP BY obr.titulo, data.ano_emprestimo, data.mes_emprestimo,
  data.semana_emprestimo, data.dia_emprestimo WITH ROLLUP;

###############################################################################

-- EMPRESTIMOS POR CLIENTES - CONTRAÇÃO
SELECT usu.nome, IFNULL(data.data_emprestimo, 'Total geral') AS 'data_emprestimo', data.ano_emprestimo,
  data.mes_emprestimo, data.semana_emprestimo, data.dia_emprestimo, SUM(bib.preco_obra) AS 'Total dos livros reservados'
FROM dw_biblioteca.dim_usuario usu, dw_biblioteca.dim_data data, dw_biblioteca.fat_biblioteca bib
WHERE bib.id_dim_usuario = usu.id AND bib.id_dim_data = data.id
GROUP BY usu.nome, data.data_emprestimo, data.ano_emprestimo, data.mes_emprestimo,
  data.semana_emprestimo, data.dia_emprestimo WITH ROLLUP;

SELECT usu.nome, IFNULL(data.data_emprestimo, 'Total geral') AS 'data_emprestimo', data.ano_emprestimo,
  data.mes_emprestimo, data.semana_emprestimo, SUM(bib.preco_obra) AS 'Total dos livros reservados'
FROM dw_biblioteca.dim_usuario usu, dw_biblioteca.dim_data data, dw_biblioteca.fat_biblioteca bib
WHERE bib.id_dim_usuario = usu.id AND bib.id_dim_data = data.id
GROUP BY usu.nome, data.data_emprestimo, data.ano_emprestimo, data.mes_emprestimo,
  data.semana_emprestimo WITH ROLLUP;

SELECT usu.nome, IFNULL(data.data_emprestimo, 'Total geral') AS 'data_emprestimo', data.ano_emprestimo,
  data.mes_emprestimo, SUM(bib.preco_obra) AS 'Total dos livros reservados'
FROM dw_biblioteca.dim_usuario usu, dw_biblioteca.dim_data data, dw_biblioteca.fat_biblioteca bib
WHERE bib.id_dim_usuario = usu.id AND bib.id_dim_data = data.id
GROUP BY usu.nome, data.data_emprestimo, data.ano_emprestimo, data.mes_emprestimo WITH ROLLUP;

SELECT usu.nome, IFNULL(data.data_emprestimo, 'Total geral') AS 'data_emprestimo', data.ano_emprestimo,
  SUM(bib.preco_obra) AS 'Total dos livros reservados'
FROM dw_biblioteca.dim_usuario usu, dw_biblioteca.dim_data data, dw_biblioteca.fat_biblioteca bib
WHERE bib.id_dim_usuario = usu.id AND bib.id_dim_data = data.id
GROUP BY usu.nome, data.data_emprestimo, data.ano_emprestimo WITH ROLLUP;

SELECT usu.nome, IFNULL(data.data_emprestimo, 'Total geral') AS 'data_emprestimo',
  SUM(bib.preco_obra) AS 'Total dos livros reservados'
FROM dw_biblioteca.dim_usuario usu, dw_biblioteca.dim_data data, dw_biblioteca.fat_biblioteca bib
WHERE bib.id_dim_usuario = usu.id AND bib.id_dim_data = data.id
GROUP BY usu.nome, data.data_emprestimo WITH ROLLUP;

-- EMPRESTIMOS POR CLIENTES - EXPANSÃO
SELECT usu.nome,
  IFNULL(data.ano_emprestimo, 'Total geral') AS 'ano_emprestimo', SUM(bib.preco_obra) AS 'Total dos livros reservados'
FROM dw_biblioteca.dim_usuario usu, dw_biblioteca.dim_data data, dw_biblioteca.fat_biblioteca bib
WHERE bib.id_dim_usuario = usu.id AND bib.id_dim_data = data.id
GROUP BY usu.nome, data.ano_emprestimo WITH ROLLUP;

SELECT usu.nome,
  IFNULL(data.ano_emprestimo, 'Total geral') AS 'ano_emprestimo',
  IFNULL(data.mes_emprestimo, 'Total ano') AS 'mes_emprestimo',
  SUM(bib.preco_obra) AS 'Total dos livros reservados'
FROM dw_biblioteca.dim_usuario usu, dw_biblioteca.dim_data data, dw_biblioteca.fat_biblioteca bib
WHERE bib.id_dim_usuario = usu.id AND bib.id_dim_data = data.id
GROUP BY usu.nome, data.ano_emprestimo, data.mes_emprestimo WITH ROLLUP;

SELECT usu.nome,
  IFNULL(data.ano_emprestimo, 'Total geral') AS 'ano_emprestimo',
  IFNULL(data.mes_emprestimo, 'Total ano') AS 'mes_emprestimo',
  IFNULL(data.semana_emprestimo, 'Total mes') AS 'semana_emprestimo',
  SUM(bib.preco_obra) AS 'Total dos livros reservados'
FROM dw_biblioteca.dim_usuario usu, dw_biblioteca.dim_data data, dw_biblioteca.fat_biblioteca bib
WHERE bib.id_dim_usuario = usu.id AND bib.id_dim_data = data.id
GROUP BY usu.nome, data.data_emprestimo, data.ano_emprestimo, data.mes_emprestimo,
  data.semana_emprestimo WITH ROLLUP;

SELECT usu.nome,
  IFNULL(data.ano_emprestimo, 'Total geral') AS 'ano_emprestimo',
  IFNULL(data.mes_emprestimo, 'Total ano') AS 'mes_emprestimo',
  IFNULL(data.semana_emprestimo, 'Total mes') AS 'semana_emprestimo',
  IFNULL(data.dia_emprestimo, 'Total dia') AS 'dia_emprestimo',
  SUM(bib.preco_obra) AS 'Total dos livros reservados'
FROM dw_biblioteca.dim_usuario usu, dw_biblioteca.dim_data data, dw_biblioteca.fat_biblioteca bib
WHERE bib.id_dim_usuario = usu.id AND bib.id_dim_data = data.id
GROUP BY usu.nome, data.data_emprestimo, data.ano_emprestimo, data.mes_emprestimo,
  data.semana_emprestimo, data.dia_emprestimo WITH ROLLUP;
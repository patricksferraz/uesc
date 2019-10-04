-- CROSSTAB

USE dw_biblioteca;

-- Movimentação anual
DELIMITER //
DROP PROCEDURE IF EXISTS movimentacaoAnual //
CREATE PROCEDURE movimentacaoAnual(
  IN ano_movimentacao int
  )
  BEGIN
    SELECT usr.nome, usr.matricula,
      GROUP_CONCAT((CASE dat.ano_emprestimo WHEN ano_movimentacao
        THEN obr.codObra ELSE NULL END)) AS 'Empréstimos no Período',
      GROUP_CONCAT((CASE dat.ano_retorno WHEN ano_movimentacao
        THEN obr.codObra ELSE NULL END)) AS 'Retornos no Período',
      GROUP_CONCAT((CASE dat.ano_devolucao WHEN ano_movimentacao
        THEN obr.codObra ELSE NULL END)) AS 'Devoluções no Período'
    FROM dim_usuario usr, dim_obra obr, dim_data dat, fat_biblioteca fat
    WHERE usr.id = fat.id_dim_usuario AND obr.id = fat.id_dim_obra AND
      dat.id = fat.id_dim_data
    GROUP BY usr.nome, usr.matricula;
  END //
DELIMITER ;

#CALL movimentacaoAnual(2003);

-- Cargos funcionários
DELIMITER //
DROP PROCEDURE IF EXISTS cargosFuncionarios //
CREATE PROCEDURE cargosFuncionarios()
  BEGIN
    SELECT fun.cargo, GROUP_CONCAT(fun.id) AS 'Funcionários'
    FROM dim_funcionario fun
    GROUP BY fun.cargo;
  END //
DELIMITER ;

#CALL cargosFuncionarios();

-- Aniversarios mes
DELIMITER //
DROP PROCEDURE IF EXISTS aniversariosMes //
CREATE PROCEDURE aniversariosMes()
  BEGIN
    SELECT MONTH(usr.data_nascimento),
      GROUP_CONCAT(usr.id) AS 'Aniversariantes'
    FROM dim_usuario usr
    GROUP BY MONTH(usr.data_nascimento);
  END //
DELIMITER ;

#CALL aniversariosMes();

#################################################################################

-- PIVOT
DELIMITER //
DROP   PROCEDURE IF EXISTS Pivot //
CREATE PROCEDURE Pivot(
    IN tbl_name VARCHAR(99),       -- table name (or db.tbl)
    IN base_cols VARCHAR(99),      -- column(s) on the left, separated by commas
    IN pivot_col VARCHAR(64),      -- name of column to put across the top
    IN tally_col VARCHAR(64),      -- name of column to SUM up
    IN where_clause VARCHAR(99),   -- empty string or "WHERE ..."
    IN order_by VARCHAR(99)        -- empty string or "ORDER BY ..."; usually the base_cols
    )
    DETERMINISTIC
    SQL SECURITY INVOKER
BEGIN
    -- Find the distinct values
    -- Build the SUM()s
    SET @subq = CONCAT('SELECT DISTINCT ', pivot_col, ' AS val ',
                    ' FROM ', tbl_name, ' ', where_clause, ' ORDER BY 1');
    -- select @subq;

    SET @cc1 = "CONCAT('SUM(IF(&p = ', &v, ', &t, 0)) AS ', &v)";
    SET @cc2 = REPLACE(@cc1, '&p', pivot_col);
    SET @cc3 = REPLACE(@cc2, '&t', tally_col);
    -- select @cc2, @cc3;
    SET @qval = CONCAT("'\"', val, '\"'");
    -- select @qval;
    SET @cc4 = REPLACE(@cc3, '&v', @qval);
    -- select @cc4;

    SET SESSION group_concat_max_len = 10000;   -- just in case
    SET @stmt = CONCAT(
            'SELECT  GROUP_CONCAT(', @cc4, ' SEPARATOR ",\n")  INTO @sums',
            ' FROM ( ', @subq, ' ) AS top');
    -- select @stmt;
    PREPARE _sql FROM @stmt;
    EXECUTE _sql;                      -- Intermediate step: build SQL for columns
    DEALLOCATE PREPARE _sql;
    -- Construct the query and perform it
    SET @stmt2 = CONCAT(
            'SELECT ',
                base_cols, ',\n',
                @sums,
                ',\n SUM(', tally_col, ') AS Total'
            '\n FROM ', tbl_name, ' ',
            where_clause,
            ' GROUP BY ', base_cols,
            '\n WITH ROLLUP',
            '\n', order_by
        );
    -- select @stmt2;                    -- The statement that generates the result
    PREPARE _sql FROM @stmt2;
    EXECUTE _sql;                     -- The resulting pivot table ouput
    DEALLOCATE PREPARE _sql;
    -- For debugging / tweaking, SELECT the various @variables after CALLing.
END;
//
DELIMITER ;

CALL Pivot('dw_biblioteca.fat_biblioteca', 'id_dim_obra', 'obra_devolvida',
           'preco_obra', '', '');
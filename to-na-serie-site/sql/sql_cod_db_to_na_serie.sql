#drop database db_to_na_serie;

create database db_to_na_serie;

use db_to_na_serie;

create table nva_nivel_acesso (
	nva_id_nivel_acesso int not null,
    nva_nome varchar(25) not null,
    primary key (nva_id_nivel_acesso)
) ENGINE=INNODB;

#ver viabilidade de endereço
create table usr_usuario (
	usr_id_usuario int not null,
    usr_id_nivel_acesso int not null,
	usr_nome varchar(75) not null,
    usr_apelido varchar(25) not null,
    usr_sexo char(1) not null,
    usr_data_nascimento date not null,
    usr_email varchar(50) not null,
    usr_telefone varchar(25),
    usr_facebook varchar(25),
    usr_senha varchar(50) not null,
    usr_status bool not null,#0 = usuário banido 1 = ativo
    usr_nome_imagem varchar(100),
    usr_tamanho_imagem varchar(25),
    usr_tipo_imagem varchar(25),
    usr_imagem longblob,
    usr_validacao_cadastro bool not null,#0 = validar email 1 = email validado
    usr_data_cadastro timestamp not null,
    usr_id_usuario_cadastrou int not null,
    primary key (usr_id_usuario),
    constraint un_email unique (usr_email),
    constraint un_apelido unique (usr_apelido),
    constraint fk_usr__usuario foreign key (usr_id_usuario_cadastrou)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE,
    constraint fk_usr__nivel_acesso foreign key (usr_id_nivel_acesso)
    references nva_nivel_acesso (nva_id_nivel_acesso) ON DELETE CASCADE
) ENGINE=INNODB;

create table adu_alteracao_dados_usuario (
	adu_id_usuario int not null,
    adu_data_alteracao timestamp not null,
    adu_id_usuario_alterou int not null,
    primary key (adu_id_usuario, adu_data_alteracao, adu_id_usuario_alterou),
    constraint fk_adu__usuario foreign key (adu_id_usuario)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE,
    constraint fk_adu__usuario_alterou foreign key (adu_id_usuario_alterou)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE
) ENGINE=INNODB;

create table emi_emissora (
	emi_id_emissora int not null,
    emi_nome varchar(50) not null,
    emi_sigla varchar(25) not null,
    emi_pagina_oficial varchar(50),
    emi_data_cadastro timestamp not null,
    emi_id_usuario_cadastrou int not null,
    primary key (emi_id_emissora),
    constraint un_nome unique (emi_nome),
    constraint fk_emi__usuario foreign key (emi_id_usuario_cadastrou)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE
) ENGINE=INNODB;

create table idm_idioma (
	idm_id_idioma int not null,
    idm_nome varchar(50) not null,
    idm_data_cadastro timestamp not null,
    idm_id_usuario_cadastrou int not null,
    primary key (idm_id_idioma),
    constraint un_nome unique (idm_nome),
    constraint fk_idm__usuario foreign key (idm_id_usuario_cadastrou)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE
) ENGINE=INNODB;

create table pas_pais (
	pas_id_pais int not null,
    pas_nome varchar(50) not null,
    pas_nome_imagem varchar(100) not null,
    pas_tamanho_imagem varchar(25) not null,
    pas_tipo_imagem varchar(25) not null,
    pas_imagem mediumblob not null,
    pas_data_cadastro timestamp not null,
    pas_id_usuario_cadastrou int not null,
    primary key (pas_id_pais),
    constraint un_nome unique (pas_nome),
    constraint fk_pas__usuario foreign key (pas_id_usuario_cadastrou)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE
) ENGINE=INNODB;

create table ctp_categoria_premio (
	ctp_id_categoria_premio int not null,
    ctp_nome varchar(50) not null,
    ctp_data_cadastro timestamp not null,
    ctp_id_usuario_cadastrou int not null,
    primary key (ctp_id_categoria_premio),
    constraint un_nome unique (ctp_nome),
    constraint fk_ctp__usuario foreign key (ctp_id_usuario_cadastrou)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE
) ENGINE=INNODB;

create table pes_pessoa (
	pes_id_pessoa int not null,
    pes_nome varchar(75) not null,
    pes_id_pais int not null,
    pes_data_cadastro timestamp not null,
    pes_id_usuario_cadastrou int not null,
    primary key (pes_id_pessoa),
    constraint un_pessoa unique (pes_nome, pes_id_pais),
    constraint fk_pes__usuario foreign key (pes_id_usuario_cadastrou)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE,
    constraint fk_pes__pais foreign key (pes_id_pais)
    references pas_pais (pas_id_pais) ON DELETE CASCADE
) ENGINE=INNODB;

create table tpp_tipo_participacao (
	tpp_id_tipo_participacao int not null,
    tpp_nome varchar(50) not null,
    tpp_data_cadastro timestamp not null,
    tpp_id_usuario_cadastrou int not null,
    primary key (tpp_id_tipo_participacao),
    constraint un_nome unique (tpp_nome),
    constraint fk_tpp__usuario foreign key (tpp_id_usuario_cadastrou)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE
) ENGINE=INNODB;

create table prm_premiacao (
	prm_id_premiacao int not null,
    prm_nome varchar(50) not null,
    prm_sigla varchar(25),
    prm_id_pais int not null,
    prm_descricao varchar(500),
    prm_data_cadastro timestamp not null,
    prm_id_usuario_cadastrou int not null,
    primary key (prm_id_premiacao),
    constraint un_nome unique (prm_nome),
    constraint fk_prm__pais foreign key (prm_id_pais)
    references pas_pais (pas_id_pais) ON DELETE CASCADE,
    constraint fk_prm__usuario foreign key (prm_id_usuario_cadastrou)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE
) ENGINE=INNODB;

create table gnr_genero (
	gnr_id_genero int not null,
    gnr_nome varchar(25) not null,
    gnr_data_cadastro timestamp not null,
    gnr_id_usuario_cadastrou int not null,
    primary key (gnr_id_genero),
    constraint un_nome unique (gnr_nome),
    constraint fk_gnr__usuario foreign key (gnr_id_usuario_cadastrou)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE
) ENGINE=INNODB;

create table gpu_genero_preferencia_usuario (
	gpu_id_usuario int not null,
    gpu_id_genero int not null,
    gpu_data_cadastro timestamp not null,
    gpu_nivel_preferencia int,#talvez não seja necessária
    primary key (gpu_id_usuario, gpu_id_genero),
    constraint fk_gpu__usuario foreign key (gpu_id_usuario)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE,
    constraint fk_gpu__genero foreign key (gpu_id_genero)
    references gnr_genero (gnr_id_genero) ON DELETE CASCADE
) ENGINE=INNODB;

create table cle_classificacao_etaria (
	cle_id_classificacao_etaria int not null,
    cle_descricao varchar(50) not null,
    cle_nome_imagem varchar(100) not null,
    cle_tamanho_imagem varchar(25) not null,
    cle_tipo_imagem varchar(25) not null,
    cle_imagem mediumblob not null,
    cle_data_cadastro timestamp not null,
    cle_id_usuario_cadastrou int not null,
    primary key (cle_id_classificacao_etaria),
    constraint un_descricao unique (cle_descricao),
    constraint fk_cle__usuario foreign key (cle_id_usuario_cadastrou)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE
) ENGINE=INNODB;

create table ser_serie (
	ser_id_serie int not null,
    ser_titulo_original varchar(75) not null,
    ser_titulo_portugues varchar(75) not null,
    ser_data_estreia date not null,
    ser_data_fim date,
    ser_id_emissora int not null,
    ser_id_pais int not null,
    ser_id_idioma int not null,
    ser_id_classificacao_etaria int not null,
    ser_sinopse varchar(1000) not null,
    ser_nome_imagem varchar(100),
    ser_tamanho_imagem varchar(25),
    ser_tipo_imagem varchar(25),
    ser_imagem_cabecalho longblob,
    ser_data_cadastro timestamp not null,
    ser_status char(1) not null,
    ser_id_usuario_cadastrou int not null,
    ser_validacao_cadastro bool not null,
    ser_data_validacao timestamp,
    ser_id_usuario_validou int,
    primary key (ser_id_serie),
    constraint un_titulo unique (ser_titulo_original, ser_titulo_portugues),
    constraint fk_ser__emisora foreign key (ser_id_emissora)
    references emi_emissora (emi_id_emissora) ON DELETE CASCADE,
    constraint fk_ser__pais foreign key (ser_id_pais)
    references pas_pais (pas_id_pais) ON DELETE CASCADE,
    constraint fk_ser__idioma foreign key (ser_id_idioma)
    references idm_idioma (idm_id_idioma) ON DELETE CASCADE,
    constraint fk_ser__classificacao_etaria foreign key (ser_id_classificacao_etaria)
    references cle_classificacao_etaria (cle_id_classificacao_etaria) ON DELETE CASCADE,
    constraint fk_ser__usuario_cadastrou foreign key (ser_id_usuario_cadastrou)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE,
    constraint fk_ser__usuario_validou foreign key (ser_id_usuario_validou)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE
) ENGINE=INNODB;

create table ads_alteracao_dados_serie (
	ads_id_serie int not null,
    ads_data_alteracao timestamp not null,
    ads_id_usuario_alterou int not null,
    primary key (ads_id_serie, ads_data_alteracao, ads_id_usuario_alterou),
    constraint fk_ads__serie foreign key (ads_id_serie)
    references ser_serie (ser_id_serie) ON DELETE CASCADE,
    constraint fk_ads__usuario_alterou foreign key (ads_id_usuario_alterou)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE
) ENGINE=INNODB;

create table tps_temporada_serie (
	tps_id_serie int not null,
    tps_id_temporada_serie int not null,
    tps_data_inicio date not null,
    tps_data_fim date,
    tps_descricao varchar(1000),
    tps_nome_imagem varchar(100) not null,
    tps_tamanho_imagem varchar(25) not null,
    tps_tipo_imagem varchar(25) not null,
    tps_imagem longblob not null,
    tps_nome_video varchar(100),
    tps_tamanho_video varchar(25),
    tps_tipo_video varchar(25),
    tps_video longblob,
    tps_data_cadastro timestamp not null,
    tps_id_usuario_cadastrou int not null,
    tps_validacao_cadastro bool not null,
    tps_data_validacao timestamp,
    tps_id_usuario_validou int,
    primary key (tps_id_serie, tps_id_temporada_serie),
    constraint fk_tps__serie foreign key (tps_id_serie)
    references ser_serie (ser_id_serie) ON DELETE CASCADE,
    constraint fk_tps__usuario_cadastrou foreign key (tps_id_usuario_cadastrou)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE,
    constraint fk_tps__usuario_validou foreign key (tps_id_usuario_validou)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE
) ENGINE=INNODB;

#VERIFICA AVALIAÇÕES
create table ets_episodio_temporada_serie (
	ets_id_serie int not null,
    ets_id_temporada_serie int not null,
    ets_id_episodio_temporada_serie int not null,
    ets_titulo_original varchar(75) not null,
    ets_titulo_portugues varchar(75) not null,
    ets_data_exibicao_usa date not null,
    ets_data_exibicao_bra date not null,
    ets_sinopse varchar(1000) not null,
    ets_data_cadastro timestamp not null,
    ets_id_usuario_cadastrou int not null,
    ets_validacao_cadastro bool not null,
    ets_data_validacao timestamp,
    ets_id_usuario_validou int,
    primary key (ets_id_serie, ets_id_temporada_serie, ets_id_episodio_temporada_serie),
    constraint fk_ets__temporada_serie foreign key (ets_id_serie, ets_id_temporada_serie)
    references tps_temporada_serie (tps_id_serie, tps_id_temporada_serie) ON DELETE CASCADE,
    constraint fk_ets__usuario_cadastrou foreign key (ets_id_usuario_cadastrou)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE,
    constraint fk_ets__usuario_validou foreign key (ets_id_usuario_validou)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE
) ENGINE=INNODB;

create table cms_comentario_serie (
	cms_id_serie int not null,
    cms_id_usuario_comentou int not null,
    cms_data_comentario timestamp not null,
    cms_mensagem varchar(255) not null,
    cms_validacao_mensagem bool not null,
    cms_data_validacao timestamp,
    cms_id_usuario_validou int,
    primary key (cms_id_serie, cms_id_usuario_comentou, cms_data_comentario),
    constraint fk_cms__serie foreign key (cms_id_serie)
    references ser_serie (ser_id_serie) ON DELETE CASCADE,
    constraint fk_cms__usuario_comentou foreign key (cms_id_usuario_comentou)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE,
    constraint fk_cms__usuario_validou foreign key (cms_id_usuario_validou)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE
) ENGINE=INNODB;

create table csa_comentario_serie_auditado (
	csa_id_serie int not null,
    csa_id_usuario_comentou int not null,
    csa_data_comentario timestamp not null,
    csa_mensagem varchar(255) not null,
    csa_descricao_motivo varchar(50) not null,
    csa_data_auditoria timestamp not null,
    csa_id_usuario_auditou int not null,
    primary key (csa_id_serie, csa_id_usuario_comentou, csa_data_comentario),
    constraint fk_csa__serie foreign key (csa_id_serie)
    references ser_serie (ser_id_serie) ON DELETE CASCADE,
    constraint fk_csa__usuario_comentou foreign key (csa_id_usuario_comentou)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE,
    constraint fk_csa__usuario_auditou foreign key (csa_id_usuario_auditou)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE
) ENGINE=INNODB;

create table rcs_resposta_comentario_serie (
	rcs_id_serie int not null,
    rcs_id_usuario_comentou int not null,
    rcs_data_comentario timestamp not null,
    rcs_id_usuario_respondeu int not null,
    rcs_data_resposta timestamp not null,
    rcs_mensagem varchar(255) not null,
    rcs_validacao_mensagem bool not null,
    rcs_data_validacao timestamp,
    rcs_id_usuario_validou int,
    primary key (rcs_id_serie, rcs_id_usuario_comentou, rcs_data_comentario, rcs_id_usuario_respondeu, rcs_data_resposta),
    constraint fk_rcs__comentario_serie foreign key (rcs_id_serie, rcs_id_usuario_comentou, rcs_data_comentario)
    references cms_comentario_serie (cms_id_serie, cms_id_usuario_comentou, cms_data_comentario) ON DELETE CASCADE,
    constraint fk_rcs__usuario_respondeu foreign key (rcs_id_usuario_respondeu)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE,
    constraint fk_rcs__usuario_validou foreign key (rcs_id_usuario_validou)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE
) ENGINE=INNODB;

create table rca_comentario_serie_auditado (
	rca_id_serie int not null,
    rca_id_usuario_comentou int not null,
    rca_data_comentario timestamp not null,
    rca_mensagem varchar(255) not null,
    rca_descricao_motivo varchar(50) not null,
    rca_data_auditoria timestamp not null,
    rca_id_usuario_auditou int not null,
    primary key (rca_id_serie, rca_id_usuario_comentou, rca_data_comentario),
    constraint fk_rca__serie foreign key (rca_id_serie)
    references ser_serie (ser_id_serie) ON DELETE CASCADE,
    constraint fk_rca__usuario_comentou foreign key (rca_id_usuario_comentou)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE,
    constraint fk_rca__usuario_auditou foreign key (rca_id_usuario_auditou)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE
) ENGINE=INNODB;

create table gns_genero_serie (
	gns_id_serie int not null,
    gns_id_genero int not null,
    gns_data_cadastro timestamp not null,
    gns_id_usuario_cadastrou int not null,
    gns_validacao_cadastro bool not null,
    gns_data_validacao timestamp,
    gns_id_usuario_validou int,
    primary key (gns_id_serie, gns_id_genero),
    constraint fk_gns__serie foreign key (gns_id_serie)
    references ser_serie (ser_id_serie) ON DELETE CASCADE,
    constraint fk_gns__genero foreign key (gns_id_genero)
    references gnr_genero (gnr_id_genero) ON DELETE CASCADE,
    constraint fk_gns__usuario_cadastrou foreign key (gns_id_usuario_cadastrou)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE,
    constraint fk_gns__usuario_validou foreign key (gns_id_usuario_validou)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE
) ENGINE=INNODB;

create table pds_producao_serie (
	pds_id_serie int not null,
    pds_id_tipo_participacao int not null,
    pds_id_pessoa int not null,
    pds_data_cadastro timestamp not null,
    pds_id_usuario_cadastrou int not null,
    pds_validacao_cadastro bool not null,
    pds_data_validacao timestamp,
    pds_id_usuario_validou int,
    primary key (pds_id_serie, pds_id_tipo_participacao, pds_id_pessoa),
    constraint fk_pds__serie foreign key (pds_id_serie)
    references ser_serie (ser_id_serie) ON DELETE CASCADE,
    constraint fk_pds__tipo_participacao foreign key (pds_id_tipo_participacao)
    references tpp_tipo_participacao (tpp_id_tipo_participacao) ON DELETE CASCADE,
    constraint fk_pds__pessoa foreign key (pds_id_pessoa)
    references pes_pessoa (pes_id_pessoa) ON DELETE CASCADE,
    constraint fk_pds__usuario_cadastrou foreign key (pds_id_usuario_cadastrou)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE,
    constraint fk_pds__usuario_validou foreign key (pds_id_usuario_validou)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE
) ENGINE=INNODB;

create table prs_premiacao_serie (
	prs_id_serie int not null,
    prs_ano date not null,
    prs_id_premiacao int not null,
    prs_id_categoria_premio int not null,
	prs_resultado bool not null,
    prs_data_cadastro timestamp not null,
    prs_id_usuario_cadastrou int not null,
    prs_validacao_cadastro bool not null,
    prs_data_validacao timestamp,
    prs_id_usuario_validou int,
    primary key (prs_id_serie, prs_ano, prs_id_premiacao, prs_id_categoria_premio),
    constraint fk_prs__serie foreign key (prs_id_serie)
    references ser_serie (ser_id_serie) ON DELETE CASCADE,
    constraint fk_prs__premiacao foreign key (prs_id_premiacao)
    references prm_premiacao (prm_id_premiacao) ON DELETE CASCADE,
    constraint fk_prs__categoria foreign key (prs_id_categoria_premio)
    references ctp_categoria_premio (ctp_id_categoria_premio) ON DELETE CASCADE,
    constraint fk_prs__usuario_cadastrou foreign key (prs_id_usuario_cadastrou)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE,
    constraint fk_prs__usuario_validou foreign key (prs_id_usuario_validou)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE
) ENGINE=INNODB;

create table nps_nomeacao_premiacao_serie (
	nps_id_serie int not null,
    nps_ano date not null,
    nps_id_premiacao int not null,
    nps_id_categoria_premio int not null,
    nps_id_pessoa int not null,
    nps_data_cadastro timestamp not null,
    nps_id_usuario_cadastrou int not null,
    nps_validacao_cadastro bool not null,
    nps_data_validacao timestamp,
    nps_id_usuario_validou int,
    primary key (nps_id_serie, nps_ano, nps_id_premiacao, nps_id_categoria_premio, nps_id_pessoa),
    constraint fk_nps__premiacao_serie foreign key (nps_id_serie, nps_ano, nps_id_premiacao, nps_id_categoria_premio)
    references prs_premiacao_serie (prs_id_serie, prs_ano, prs_id_premiacao, prs_id_categoria_premio) ON DELETE CASCADE,
    constraint fk_nps__pessoa foreign key (nps_id_pessoa)
    references pes_pessoa (pes_id_pessoa) ON DELETE CASCADE,
    constraint fk_nps__usuario_cadastrou foreign key (nps_id_usuario_cadastrou)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE,
    constraint fk_nps__usuadio_validou foreign key (nps_id_usuario_validou)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE
) ENGINE=INNODB;

create table seu_serie_usuario (
	seu_id_serie int not null,
    seu_id_usuario int not null,
    seu_data_adicao timestamp not null,
    #talvez data da ultima visualização
    primary key (seu_id_serie, seu_id_usuario),
    constraint fk_seu__serie foreign key (seu_id_serie)
    references ser_serie (ser_id_serie) ON DELETE CASCADE,
    constraint fk_seu__usuario foreign key (seu_id_usuario)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE
) ENGINE=INNODB;

#COnsultar atualizações atraves das datas de adição de serie e adião se episodio
create table sgu_seguidor_usuario (
	sgu_id_usuario_seguidor int not null,
    sgu_id_usuario_seguido int not null,
    sgu_data_solicitacao timestamp not null,
	sgu_validacao_solicitacao bool not null,
    sgu_data_validacao timestamp,
    primary key (sgu_id_usuario_seguidor, sgu_id_usuario_seguido),
    constraint fk_sgu__usuario_seguidor foreign key (sgu_id_usuario_seguidor)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE,
    constraint fk_sgu__usuario_seguido foreign key (sgu_id_usuario_seguido)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE
) ENGINE=INNODB;

create table eau_episodio_assistido_usuario (
	eau_id_serie int not null,
    eau_id_temporada_serie int not null,
    eau_id_episodio_temporada_serie int not null,
    eau_id_usuario int not null,
    eau_avaliacao int,
    eau_observacoes varchar(1000),
    eau_data_visualizacao timestamp not null,
    primary key (eau_id_serie, eau_id_temporada_serie, eau_id_episodio_temporada_serie, eau_id_usuario),
    constraint fk_eau__episodio_temporada_serie foreign key (eau_id_serie, eau_id_temporada_serie, eau_id_episodio_temporada_serie)
    references ets_episodio_temporada_serie (ets_id_serie, ets_id_temporada_serie, ets_id_episodio_temporada_serie) ON DELETE CASCADE,
    constraint fk_eau__usuario foreign key (eau_id_usuario)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE
) ENGINE=INNODB;

create table mtb_motivo_ban(
	mtb_id_motivo_ban int not null,
    mtb_nome varchar(50) not null,
    mtb_dias_penalidade int(3) not null,
    primary key (mtb_id_motivo_ban)
) ENGINE=INNODB;

create table pnu_punicao_usuario (
	pnu_id_usuario int not null,
    pnu_id_motivo_ban int not null,
    pnu_data_inicio_punicao date not null,
    pnu_data_fim_punicao date not null,
    pnu_descricao varchar(255) not null,
    primary key (pnu_id_usuario, pnu_id_motivo_ban, pnu_data_inicio_punicao),
    constraint fk_pnu__usuario foreign key (pnu_id_usuario)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE,
    constraint fk_pnu__motivo_ban foreign key (pnu_id_motivo_ban)
    references mtb_motivo_ban (mtb_id_motivo_ban) ON DELETE CASCADE
) ENGINE=INNODB;

create table htl_historico_login (
	htl_id_usuario int not null,
    htl_data_login timestamp not null,
    htl_data_logout timestamp not null,
    htl_ip_login varchar(25) not null,
    htl_user_agent varchar(75) not null,
    primary key (htl_id_usuario, htl_data_login),
    constraint fk_htl__usuario foreign key (htl_id_usuario)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE
) ENGINE=INNODB;

create table hvu_historico_visualizacao_usuario (
	hvu_id_usuario_visitado int not null,
    hvu_id_usuario_visitante int not null,
    hvu_data_visualizacao timestamp not null,
    primary key (hvu_id_usuario_visitado, hvu_id_usuario_visitante),
    constraint fk_hvu__usuario_visitado foreign key (hvu_id_usuario_visitado)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE,
    constraint fk_hvu__usuario_visitante foreign key (hvu_id_usuario_visitante)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE
) ENGINE=INNODB;

create table hvs_historico_visualizacao_serie (
	hvs_id_serie int not null,
    hvs_id_usuario int not null,
    hvu_data_visualizacao timestamp not null,
    primary key (hvs_id_serie, hvs_id_usuario),
    constraint fk_hvs__serie foreign key (hvs_id_serie)
    references ser_serie (ser_id_serie) ON DELETE CASCADE,
    constraint fk_hvs__usuario foreign key (hvs_id_usuario)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE
) ENGINE=INNODB;

create table sra_serie_recomendada_amigo (
    sra_id_serie int not null,
    sra_id_usuario_recomendou int not null,
    sra_id_usuario_recomendado int not null,
    sra_data_recomendacao timestamp not null,
    sra_aceitacao_recomendacao bool not null,
    sra_data_aceitacao timestamp,
    primary key (sra_id_serie, sra_id_usuario_recomendou, sra_id_usuario_recomendado),
    constraint fk_sra__serie foreign key (sra_id_serie)
    references ser_serie (ser_id_serie) ON DELETE CASCADE,
    constraint fk_sra__usuario_recomendou foreign key (sra_id_usuario_recomendou)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE,
    constraint fk_sra__usuario_recomendado foreign key (sra_id_usuario_recomendado)
    references usr_usuario (usr_id_usuario) ON DELETE CASCADE
) ENGINE=INNODB;

######################Cadastro de níveis de acesso########################
/***/
insert into nva_nivel_acesso (nva_id_nivel_acesso, nva_nome) values (0, 'Administrador');
insert into nva_nivel_acesso (nva_id_nivel_acesso, nva_nome) values (1, 'Gerente');
insert into nva_nivel_acesso (nva_id_nivel_acesso, nva_nome) values (2, 'Revisor');
insert into nva_nivel_acesso (nva_id_nivel_acesso, nva_nome) values (3, 'Contribuinte');
insert into nva_nivel_acesso (nva_id_nivel_acesso, nva_nome) values (4, 'Editor');
insert into nva_nivel_acesso (nva_id_nivel_acesso, nva_nome) values (5, 'Suporte');
insert into nva_nivel_acesso (nva_id_nivel_acesso, nva_nome) values (6, 'Usuario');
/***/


#####################Cadastro do administrador inicial#####################
/***/
insert into usr_usuario
	(usr_id_usuario,
    usr_id_nivel_acesso,
    usr_nome,
    usr_apelido,
    usr_sexo,
	usr_data_nascimento,
    usr_email,
    usr_telefone,
    usr_facebook,
    usr_senha,
    usr_status,
    usr_data_cadastro,
    usr_id_usuario_cadastrou,
    usr_validacao_cadastro)
    values (0, 0, 'Administrador', 'ADM', 'M', '1990-01-01', 'admin@tonaserie.com.br',
    null, null, '202cb962ac59075b964b07152d234b70', 1, '2017-07-27', 0, 1);
/***/
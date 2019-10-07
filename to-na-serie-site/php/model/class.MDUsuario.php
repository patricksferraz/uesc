<?php

/**
* 
*/
class MDUsuario
{
	private $id_usuario;
    private $id_nivel_acesso;
    private $nome;
    private $apelido;
    private $sexo;
    private $data_nascimento;
    private $email;
    private $telefone;
    private $facebook;
    private $senha;
    private $status;
    private $nome_imagem;
    private $tamanho_imagem;
    private $tipo_imagem;
    private $imagem;
    private $validacao_cadastro;
    private $data_cadastro;
    private $id_usuario_cadastrou;
	
	function __construct($array)
	{
		$this->id_usuario = $array[0];
		$this->id_nivel_acesso = $array[1];
        $this->nome = $array[2];
        $this->apelido = $array[3];
        $this->sexo = $array[4];
        $this->data_nascimento = $array[5];
		$this->email = $array[6];
		$this->telefone = $array[7];
		$this->facebook = $array[8];
		$this->senha = $array[9];
		$this->status = $array[10];
		$this->nome_imagem = $array[11];
		$this->tamanho_imagem = $array[12];
		$this->tipo_imagem = $array[13];
		$this->imagem = $array[14];
		$this->validacao_cadastro = $array[15];
        $this->data_cadastro = $array[16];
        $this->id_usuario_cadastrou = $array[17];
    }

    /**
     * @return mixed
     */
    public function getIdUsuario()
    {
        return $this->id_usuario;
    }

    /**
     * @param mixed $id_usuario
     *
     * @return self
     */
    public function setIdUsuario($id_usuario)
    {
        $this->id_usuario = $id_usuario;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getIdNivelAcesso()
    {
        return $this->id_nivel_acesso;
    }

    /**
     * @param mixed $id_nivel_acesso
     *
     * @return self
     */
    public function setIdNivelAcesso($id_nivel_acesso)
    {
        $this->id_nivel_acesso = $id_nivel_acesso;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getNome()
    {
        return $this->nome;
    }

    /**
     * @param mixed $nome
     *
     * @return self
     */
    public function setNome($nome)
    {
        $this->nome = $nome;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getApelido()
    {
        return $this->apelido;
    }

    /**
     * @param mixed $apelido
     *
     * @return self
     */
    public function setApelido($apelido)
    {
        $this->apelido = $apelido;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getSexo()
    {
        return $this->sexo;
    }

    /**
     * @param mixed $sexo
     *
     * @return self
     */
    public function setSexo($sexo)
    {
        $this->sexo = $sexo;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getDataNascimento()
    {
        return $this->data_nascimento;
    }

    /**
     * @param mixed $data_nascimento
     *
     * @return self
     */
    public function setDataNascimento($data_nascimento)
    {
        $this->data_nascimento = $data_nascimento;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getEmail()
    {
        return $this->email;
    }

    /**
     * @param mixed $email
     *
     * @return self
     */
    public function setEmail($email)
    {
        $this->email = $email;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getTelefone()
    {
        return $this->telefone;
    }

    /**
     * @param mixed $telefone
     *
     * @return self
     */
    public function setTelefone($telefone)
    {
        $this->telefone = $telefone;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getFacebook()
    {
        return $this->facebook;
    }

    /**
     * @param mixed $facebook
     *
     * @return self
     */
    public function setFacebook($facebook)
    {
        $this->facebook = $facebook;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getSenha()
    {
        return $this->senha;
    }

    /**
     * @param mixed $senha
     *
     * @return self
     */
    public function setSenha($senha)
    {
        $this->senha = $senha;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getStatus()
    {
        return $this->status;
    }

    /**
     * @param mixed $status
     *
     * @return self
     */
    public function setStatus($status)
    {
        $this->status = $status;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getNomeImagem()
    {
        return $this->nome_imagem;
    }

    /**
     * @param mixed $nome_imagem
     *
     * @return self
     */
    public function setNomeImagem($nome_imagem)
    {
        $this->nome_imagem = $nome_imagem;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getTamanhoImagem()
    {
        return $this->tamanho_imagem;
    }

    /**
     * @param mixed $tamanho_imagem
     *
     * @return self
     */
    public function setTamanhoImagem($tamanho_imagem)
    {
        $this->tamanho_imagem = $tamanho_imagem;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getTipoImagem()
    {
        return $this->tipo_imagem;
    }

    /**
     * @param mixed $tipo_imagem
     *
     * @return self
     */
    public function setTipoImagem($tipo_imagem)
    {
        $this->tipo_imagem = $tipo_imagem;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getImagem()
    {
        return $this->imagem;
    }

    /**
     * @param mixed $imagem
     *
     * @return self
     */
    public function setImagem($imagem)
    {
        $this->imagem = $imagem;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getValidacaoCadastro()
    {
        return $this->validacao_cadastro;
    }

    /**
     * @param mixed $validacao_cadastro
     *
     * @return self
     */
    public function setValidacaoCadastro($validacao_cadastro)
    {
        $this->validacao_cadastro = $validacao_cadastro;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getDataCadastro()
    {
        return $this->data_cadastro;
    }

    /**
     * @param mixed $data_cadastro
     *
     * @return self
     */
    public function setDataCadastro($data_cadastro)
    {
        $this->data_cadastro = $data_cadastro;

        return $this;
    }

    /**
     * @return mixed
     */
    public function getIdUsuarioCadastrou()
    {
        return $this->id_usuario_cadastrou;
    }

    /**
     * @param mixed $id_usuario_cadastrou
     *
     * @return self
     */
    public function setIdUsuarioCadastrou($id_usuario_cadastrou)
    {
        $this->id_usuario_cadastrou = $id_usuario_cadastrou;

        return $this;
    }
}

?>
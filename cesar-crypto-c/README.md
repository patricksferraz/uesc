# Criptografia Uesc

Este repositório contém os projetos/atividades desenvolvidos na disciplinas Criptografia durante a graduação no curso Ciência da Computação na Universidade Estadual de Santa Cruz

## Descrição

Todos algoritmos desenvolvidos são executados por linha de comando

## Projetos desenvolvidos

* cifraCesar
* redeFeistel

## Cifra de César

A criptografia é um conjunto de técnicas utilizadas para cifrar uma informação deixando-a protegida e impedindo que terceiros não à utilize. A Cifra de César é uma criptografia  monoalfabética e uma das mais antigas e conhecidas. Apesar de atualmente ser considerada trivial, conta a história que ela possibilitou a Júlio César enviar mensagens cifradas para seus generais, através de um sistema simples de substituição, no qual cada letra da mensagem original era trocada pela letra que se situa k (César utilizava k = 3) posições a sua frente, ou seja, cada letra “A” era substituída pela “D”, “B” por “E” e assim sucessivamente.

**Seguindo a estratégia de César, o algoritmo criptografa somente "letras", quaisquer outros caracteres não serão cifrados tendo como saída sua própria representação**

### Compilação

```
$ gcc cifraCesar.c -o cifraCesar
```

### Execução

```
$ ./cifraCesar 'n' nomeArq.txt
```

* 'n' deve ser um número inteiro, caso contrário o programa retornar uma mensagem de erro

### Entradas inválidas

* Diferente de três argumentos

```
$ ./cifraCesar n
$ ./cifraCesar n nomeArq.txt n
```

* Arquivos inexistentes

_p.ex Supondo a existência de somente um arquivo nomeado como "mensagem.txt", a execução abaixo retornará uma mensagem de erro_

```
$ ./cifraCesar 3 outroNome.txt
```

## Referências

* [Wikipédia - Cifra César](https://pt.wikipedia.org/wiki/Cifra_de_César)

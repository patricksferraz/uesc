# Criptografia Uesc

Este repositório contém os projetos/atividades desenvolvidos na disciplinas Criptografia durante a graduação no curso Ciência da Computação na Universidade Estadual de Santa Cruz

## Descrição

Todos algoritmos desenvolvidos são executados por linha de comando

## Rede de Feistel

Na criptografia, uma cifra de Feistel é uma estrutura simétrica usada na construção de cifras de bloco, o nome é uma homenagem ao físico e criptógrafo alemão Horst Feistel, que foi o pioneiro na pesquisa enquanto trabalhava na IBM (EUA); esta cifra é comumente conhecida como rede de Feistel. Uma grande quantidade das cifras de bloco utilizam este esquema, incluindo o Data Encryption Standard (DES). A rede de Feistel segue a permutação básica da Imagem 1.

![Permutação Básica](https://github.com/patricksferraz/uesc_criptografia/blob/master/img/feistel.jpg)

#### Cifrando
As entradas do algoritmo são blocos de texto plano de comprimento 2x bits e um chave K. O bloco de texto plano é dividido em duas partes, L0 e R0. Essas metades passam por n rodadas de processamento e então se combinam para produzir o bloco de texto cifrado. Cada rodada “r” recebe como entrada Lr-1 e Rr-1, derivadas da rodada anterior, assim como uma sub-chave Kr, derivada da chave geral K. Essas sub-chave são diferentes de K entre si pois são geradas a partir de K com um algoritmo de geração de chaves. As iterações possuem todas a mesma estrutura. Uma substituição é realizada na metade esquerda dos dados, por meio da aplicação de uma função F (round function) na metade direita dos dados com a chave e então obtendo-se o XOR da saída desta função e da metade esquerda dos dados. Adicionalmente, uma permutação é realizada invertendo-se as duas partes dos dados.

#### Decifrando
O processo de descriptografia de uma cifra de Feistel é igual à criptografia. Usa-se, nesse caso, o texto cifrado como entrada do algoritmo, e as sub-chave Kn em ordem reversa.

#### Permutação dos blocos

Para ambos processos (criptografia e descriptografia), o algoritmo executa uma permutação P e permutação inversa P^{-1} no bloco (neste caso de 8Bytes), de acordo com a Imagem 2 e 3.

![Permutação Realizada nos Blocos](https://github.com/patricksferraz/uesc_criptografia/blob/master/img/permutacao.jpg)

Sendo assim, percebe-se a permutação em que, na Imagem 2, o bit 58 foi permutado para o primeiro bit, 50 para o segundo bit, 7 para último bit e assim por diante. Enquanto que na Imagem 3 (permutação inversa), o bit 40 foi permutado para o primeiro bit, 8 para o segundo bit, 25 para o último bit, etc.

#### Modos de Operação

##### ECB - Electronic COde Book Mode

##### CBC - Cipher Block Chaining

#### Observações

* A pasta contendo o código modularizado está incompleto, falta conectar todos módulos no documento raiz (desP.c)
* A pasta contendo o código NÃO modularizado está completo, porém falta organizar o código e retirar as modularização mínima existente.

### Compilação

```
$ gcc redeFeistel.c -o redeFeistel
```

### Execução

```
$ ./redeFeistel nomeArq.txt 'operacao' 'key' [-cbc]
```

* A execução acima irá gerar um arquivo binário 'file.fn'
* Necessário definir o arquivo que deseja cifrar no lugar de 'nomeArq.txt'
* 'operacao' deve ser '-c' para cifrar ou '-d' para decifrar
* [-cbc] altera o modo de operação padrão ECB - Electronic Code Book Mode p/ CBC - Cipher Block Chaining
* 'key' é a chave de criptografia e deve ser substituída por uma chave de 8 Bytes

### Entradas inválidas

* Chaves diferentes de 8Bytes

```
$ ./redeFeistel nomeArq.txt -c abcdefg
```

* Maior que cinco e menor que quatro argumentos

```
$ ./redeFeistel nomeArq.txt -c
$ ./redeFeistel nomeArq.txt -c key8Bytes [-cbc] n
```

* Operações inválidas

```
$ ./redeFeistel mensagem.txt -w k
```

**'-w' não é uma operação válida**

* Arquivos inexistentes

_p.ex Supondo a existência de somente um arquivo nomeado como "mensagem.txt", a execução abaixo retornará uma mensagem de erro_

```
$ ./redeFeistel outroNome.txt -c k
```

## Referências

* [Script Brasil](https://www.scriptbrasil.com.br/forum/topic/171660-conversor-de-caracteres-para-binário/)
* [Wikipédia - Cifra Feistel](https://pt.wikipedia.org/wiki/Cifra_Feistel)

# Computação Gráfica Uesc

Este repositório contém os projetos desenvolvidos na disciplina Computação Gráfica durante a graduação no curso Ciência da Computação na Universidade Estadual de Santa Cruz

## Descrição

Todos algoritmos

## Projetos desenvolvidos

* gamePong

## Game Pong

Pong é o primeiro videogame lucrativo da história, dando origem a um novo setor da indústria. Não possuía gráficos espetaculares ou jogabilidade excelente, mas foi de importância fundamental na história do videogame. Foi criado por Nolan Bushnell e Ted Dabney na forma de um console ligado a um monitor, movido a moedas. A primeira instalação em um bar de San Francisco, Califórnia, mostrou aos dois a possibilidade de lucro da criação. Assim, em 27 de Junho de 1972, a empresa Atari foi fundada.

### Recursos utilizados

* Sistema Operacional Linux OpenSuse Leap 42.2
* Compilador gcc
* Necessário a instalação das bibliotecas do OpenGL, freeglut e ferramenta para gcc
```
$ sudo zypper in Mesa-devel freeglut-devel MesaGLw-devel build-essential
```

### Compilação

```
$ gcc -lglut -lGLU -lGL gamePong.cpp -o gamePong
```

### Execução

```
$ ./gamePong
```

## Referências

* [Wikipédia - Pong](https://pt.wikipedia.org/wiki/Pong)

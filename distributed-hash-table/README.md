# Distributed Hash Table - DHT

O Projeto

Desenvolver um esquema DHT para compartilhamento de arquivos (esqueça o índice: cada peer armazenará os arquivos mesmo).

Em cada computador haverá uma pequena interface permitindo as seguintes opções.
a) Iniciar uma DHT
b) Inserir-se na DHT (para isso ele terá que conhecer o IP de alguma máquina já inserida)
Inserir-se na DHT implica em calcular seu Hash, localizar seu lugar e dividir as responsabilidades
c) Inserir um arquivo na DHT
O sistema deve encontrar o peer que deve ser responsável pelo arquivo e então o arquivo é enviado para este peer
d) Localizar um arquivo
O sistema deve calcular o Hash do arquivo e localizar o peer que o armazena. Então o arquivo é transferido

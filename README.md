# vigenere

Aluno: Lucas de Almeida Bandeira Macedo - 19/0047089

2021/2 - Unb - Professor Gondim

Primeiro Trabalho de Segurança Computacional, baseado na cifra de Vigenere

## Como executar

Primeiramente, compile o arquivo main.cpp . Nele estão todas as funções que o trabalho existe: codificar, decodificar e desvendar cifra.

O projeto funciona por linha de comando. Existem 3 comandos possíveis:

- `-h`
- `-c <path_relativo> <chave_de_cifra>`
- `-d <path_relativo> <chave_de_cifra>`
- `-a <path_relativo>`

Onde `-h` representa o help, mostrando os comandos disponíveis, `-c` representa "cifrar", `-d` representa "decifrar", e `-a` realiza um ataque a cifra. Ao realizar um ataque, você deverá manualmente informar um tamanho de chave de cifra, dada a tabela de opções.

Todos os outputs serão arquivos e estarão na pasta em que o programa for executado.

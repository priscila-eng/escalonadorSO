# SO - Escalonador 

### Matrículas/Alunos:

- 170105067 Hyago Gabriel Oliveira Figueiredo
- 180076272 Jonas de Souza Fagundes
- 190094699 Priscila Rodrigues
- 190113219 Maria Eduarda Alves de Sousa

### Clonar repo:

```
git clone https://github.com/priscila-eng/escalonadorSO.git
```

## COMO RODAR:

#### Utilizar os próximos comandos no root da pasta do trabalho

- Para compilar o programa
  ```
  make
  ```
- Para compilar e rodar o trabalho com número de cores = 2
  ```
  make exec
  ```
- Para limpas objetos e saídas anteriores
  ```
  make clean
  ```

  **IMPORTANTE QUE NÃO HAJA MUDANÇA NOS DIRETÓRIOS PARA UM BOM FUNCIONAMENTO DO PROGRAMA**

*OBS:* Há dois passos para testar os executáveis "teste15" e "teste30".
- O primeiro deles é alterar o define no [.c](./src/testeXX.c) para ``#define CLI_TEST 1`` 
  - Dessa forma, não há tentativa de troca de sinais entre os processos. **O envio para a lista de mensagens continua.**

- Utilizar os seguintes comandos, também no path do executável (raiz do projeto):
  ```
  ./testeXX 15 1
  ```
  ```
  ./testeXX 30 1
  ```
  ``./testeXX <Tempo> <Índice>``

## Saída do Programa:

O escalonador imprime tanto o makespan, como o tempo de execução de cada processo. 


## Indicações da plataforma utilizada:
- Compilador: GCC
- Sistema Operacional: Unix
- Ambiente utilizado para programar: Visual Studio Code

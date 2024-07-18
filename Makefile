CC = gcc
CFLAGS = 

# Lista de arquivos fonte a serem compilados
SOURCES = escalonador.c testeXX.c leitor.c readfile.c

# Gera uma lista de nomes de executáveis correspondentes aos arquivos fonte
EXECUTABLES = escalonador testeXX leitor

# Regra padrão: compila todos os executáveis
all: $(EXECUTABLES)

# Regra específica para compilar o escalonador
escalonador: escalonador.c readfile.c removeDependencia.c
	@$(CC) $(CFLAGS) escalonador.c readfile.c removeDependencia.c -o escalonador

# Regra específica para compilar o testeXX
testeXX: testeXX.c
	@$(CC) $(CFLAGS) testeXX.c -o testeXX

# Regra específica para compilar o leitor
leitor: leitor.c
	@$(CC) $(CFLAGS) leitor.c -o leitor

exec:
	@make --no-print-directory
	@./escalonador 2

# Alvo para limpar arquivos gerados
clean:
	@rm -f $(EXECUTABLES)

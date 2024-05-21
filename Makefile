CC = gcc
CFLAGS = 

# Lista de arquivos fonte a serem compilados
SOURCES = escalonador.c teste15.c teste30.c

# Gera uma lista de nomes de executáveis correspondentes aos arquivos fonte
EXECUTABLES = $(SOURCES:.c=)

# Regra padrão: compila todos os executáveis
all: $(EXECUTABLES)

# Regra genérica para compilar um arquivo .c em um executável
%: %.c
	@ $(CC) $(CFLAGS) $< -o $@

# Alvo para limpar arquivos gerados
clean:
	@ rm -f $(EXECUTABLES)

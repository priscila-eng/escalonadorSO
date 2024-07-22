# Compilador e flags
CC = gcc
CFLAGS = -Wall -g -Iinclude

# Diretórios
SRC_DIR = src
OBJ_DIR = obj

# Executáveis
EXECUTABLES = escalonador testeXX

# Arquivos fonte e objetos para o escalonador
ESCALONADOR_SRC = $(SRC_DIR)/escalonador.c $(SRC_DIR)/readfile.c $(SRC_DIR)/trataDependencia.c $(SRC_DIR)/fila.c
ESCALONADOR_OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(ESCALONADOR_SRC))

# Arquivos fonte e objetos para o testeXX
TESTEXX_SRC = $(SRC_DIR)/testeXX.c
TESTEXX_OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(TESTEXX_SRC))

# Regra padrão
all: $(EXECUTABLES)

# Regra para compilar o escalonador
escalonador: $(ESCALONADOR_OBJ)
	@ $(CC) $(CFLAGS) -o $@ $^

# Regra para compilar o testeXX
testeXX: $(TESTEXX_OBJ)
	@ $(CC) $(CFLAGS) -o $@ $^

# Regra para compilar arquivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@ $(CC) $(CFLAGS) -c -o $@ $<

# Limpeza
clean:
	@ rm -rf $(OBJ_DIR)/*.o $(EXECUTABLES)

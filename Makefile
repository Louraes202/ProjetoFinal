# Nome do compilador
CC = gcc

# Flags de compilação (opcional colocar -Wall -Wextra -g etc.)
CFLAGS = -Wall -Wextra -std=c11

# Diretivas para informar onde procurar ficheiros .h
INCLUDES = -Iinclude

# Lista de ficheiros fonte (sem o caminho, pois usaremos paths no build)
SRCS = src/main.c src/data_structures.c src/read_files.c src/operations.c

# Lista de ficheiros objeto (substituindo .c por .o)
OBJS = $(SRCS:.c=.o)

# Nome do executável final
TARGET = programa

########################################################################
# Regra principal (target default), é o que acontece se chamarmos apenas `make`
########################################################################
all: $(TARGET)

########################################################################
# Como construir o executável "programa" a partir dos objetos
########################################################################
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

########################################################################
# Regra genérica para construir ficheiros .o a partir de .c
# diz que cada .o depende do .c correspondente e de possíveis headers
########################################################################
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

########################################################################
# Limpeza (remove objetos e o executável)
########################################################################
clean:
	rm -f $(OBJS) $(TARGET)

########################################################################
# "phony targets" são alvos que não correspondem a um ficheiro real
########################################################################
.PHONY: all clean

# Nome do projeto
PROJ_NAME=escalonador

# Lib que serão usadas
INCLUDE_LIB=lib
C_SOURCE=$(wildcard $(INCLUDE_LIB)/*.c)
C_SOURCE+=$(wildcard source/*.c)

# Include .h do projeto
INCLUDE_INCLUDES=includes
H_SOURCE=$(INCLUDE_INCLUDES)/*.h

# Arquivos objetos
# Substitui o final dos arquivos .c por .o
OBJ=$(subst .c,.o,$(C_SOURCE))
# Compilador
CC=gcc

# Diretivas de compilação
LD_FLAGS=-c -I$(INCLUDE_LIB) -L$(INCLUDE_INCLUDES) -W -Wall -ansi -pedantic -std=c99 -pthread


all: $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	$(CC) -pthread -o $@ $^

%.o: %.c %.h
	$(CC) $(LD_FLAGS) -o $@ $<

main.o: main.c
	$(CC) $(LD_FLAGS) -o $@ $<

clean:
	rm -rf lib/*.o source/*.o *.o $(PROJ_NAME) *~
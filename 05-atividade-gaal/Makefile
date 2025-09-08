# Nome do compilador que vamos usar
CC = gcc

# Flags para o compilador:
# -Wall e -Wextra: Mostram todos os avisos importantes, ajuda a escrever código melhor.
# -pedantic: Garante que o código segue o padrão C estritamente.
# -Iinclude: Diz ao compilador para procurar arquivos .h na pasta "include".
CFLAGS = -Wall -Wextra -Iinclude -pedantic

# Flags para o linker:
# -lm: Liga a biblioteca de matemática (libm), necessária para sqrt, atan2, etc.
LDFLAGS = -lm

# Lista de todos os arquivos de código fonte (.c)
SRCS = src/main.c src/coordenadas.c

# O nome do programa executável que queremos criar
TARGET = gaal_converter

all: $(TARGET)

# Regra para criar o programa executável (TARGET)
# Ele "depende" dos arquivos de código fonte (SRCS). Se algum .c mudar, ele será recompilado.
$(TARGET): $(SRCS)
	$(CC) $(SRCS) $(CFLAGS) -o $(TARGET) $(LDFLAGS)

# Regra "clean": serve para limpar os arquivos gerados pela compilação.
clean:
	rm -f $(TARGET)
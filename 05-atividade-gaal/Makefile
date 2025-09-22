# Nome do compilador que vamos usar
CC = gcc

# Flags para o compilador:
# -Wall e -Wextra: Mostram todos os avisos importantes, ajuda a escrever código melhor.
# -pedantic: Garante que o código segue o padrão C estritamente.
# -Iinclude: Diz ao compilador para procurar arquivos .h na pasta "include".
CFLAGS = -Wall -Wextra -Iinclude -pedantic `pkg-config --cflags sdl2 SDL2_ttf`

# Flags para o linker:
# -lm: Liga a biblioteca de matemática (libm), necessária para sqrt, atan2, etc.
# SDL2 e SDL2_ttf: Bibliotecas para interface gráfica
LDFLAGS = -lm `pkg-config --libs sdl2 SDL2_ttf`

# Lista de todos os arquivos de código fonte (.c)
SRCS = src/main.c src/coordenadas.c src/sdl_interface.c

# O nome do programa executável que queremos criar
TARGET = gaal_converter

all: $(TARGET)

# Regra para criar o programa executável (TARGET)
# Ele "depende" dos arquivos de código fonte (SRCS). Se algum .c mudar, ele será recompilado.
$(TARGET): $(SRCS)
	$(CC) $(SRCS) $(CFLAGS) -o $(TARGET) $(LDFLAGS)

# Versão apenas console (sem SDL2)
console: src/main.c src/coordenadas.c
	$(CC) src/main.c src/coordenadas.c -Wall -Wextra -Iinclude -pedantic -DCONSOLE_ONLY -o gaal_converter_console -lm

# Regra "clean": serve para limpar os arquivos gerados pela compilação.
clean:
	rm -f $(TARGET) gaal_converter_console

# Regra para instalar dependências SDL2 (Ubuntu/Debian)
install-deps:
	sudo apt update
	sudo apt install libsdl2-dev libsdl2-ttf-dev

# Regra para verificar se as dependências estão instaladas
check-deps:
	@echo "Verificando dependências SDL2..."
	@pkg-config --exists sdl2 && echo "SDL2: ✓" || echo "SDL2: ✗ (execute 'make install-deps')"
	@pkg-config --exists SDL2_ttf && echo "SDL2_ttf: ✓" || echo "SDL2_ttf: ✗ (execute 'make install-deps')"

.PHONY: all clean install-deps check-deps console
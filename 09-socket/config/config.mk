# config/config.mk
# Configurações globais de compilação
# Compartilhado por todo o projeto

# Compilador e Linker
CC = gcc
AR = ar
RANLIB = ranlib

# Diretórios relativos
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin
INCLUDE_DIR = include

# Flags de Compilação
# -Wall -Wextra: Ativa avisos adicionais
# -O2: Otimização nível 2
# -g: Símbolos de debug
# -std=c11: Padrão C11
# -I$(INCLUDE_DIR): Inclui headers públicos
CFLAGS = -Wall -Wextra -O2 -g -std=c11 -I$(INCLUDE_DIR)

# Flags para o Linker
LDFLAGS = -lm

# Flags para limpeza
RM = rm -rf
MKDIR = mkdir -p

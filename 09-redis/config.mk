# config.mk
# Definições globais de compilação

# Compilador e Linker
CC = gcc
AR = ar
RANLIB = ranlib

# Flags de Compilação
# -I../../include: Permite incluir headers públicos como <common.h>
CFLAGS = -Wall -Wextra -O2 -g -std=c11 -I../../include

# Flags para o Linker (estático)
LDFLAGS =
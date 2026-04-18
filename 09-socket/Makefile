# Makefile (Raiz)
# Coordena compilação de todo o projeto

include config/config.mk

.PHONY: all clean build help test

all: build

build: build-network build-utils build-client build-server build-client-exec
	@echo "[BUILD] Compilação concluída!"

build-network:
	@echo "[BUILD] Compilando módulos de rede..."
	$(MAKE) -C src/network

build-utils: build-network
	@echo "[BUILD] Compilando utilitários..."
	$(MAKE) -C src/utils

build-client: build-utils
	@echo "[BUILD] Compilando biblioteca de cliente..."
	$(MAKE) -C src/client

build-server: build-utils
	@echo "[BUILD] Compilando servidor..."
	$(MAKE) -C cmd/server

build-client-exec: build-client
	@echo "[BUILD] Compilando cliente HTTP..."
	$(MAKE) -C cmd/client

run: build
	@echo "[RUN] Iniciando servidor..."
	$(BIN_DIR)/server

run-client: build
	@echo "[RUN] Iniciando cliente HTTP..."
	$(BIN_DIR)/client --help

clean:
	@echo "[CLEAN] Limpando artefatos..."
	$(RM) $(BUILD_DIR)
	@echo "[CLEAN] Limpeza concluída!"

help:
	@echo "Comandos disponíveis:"
	@echo "  make build         - Compila todo o projeto (server + client)"
	@echo "  make all           - Alias para 'make build'"
	@echo "  make run           - Compila e executa o servidor"
	@echo "  make run-client    - Compila e exibe help do cliente"
	@echo "  make clean         - Remove artefatos compilados"
	@echo "  make help          - Exibe esta mensagem"
	@echo ""
	@echo "Exemplos de uso do cliente:"
	@echo "  make build && ./build/bin/client -h 127.0.0.1 -p 8080 -r /"
	@echo "  ./build/bin/client --help"

# Compilador a ser usado
CC = gcc
# Flags de compilação: -Wall (mostra todos os warnings) é seu melhor amigo!
CFLAGS = -Wall -Wextra -std=c99

# O alvo 'all' é o padrão. Ele compilará os programas que especificarmos.
all: task2 task3

# Regra para compilar o task2
task2: src/02_process_info.c
	$(CC) $(CFLAGS) -o task2 src/02_process_info.c

# Regra para compilar o task3
task3: src/03_fork_basic.c
	$(CC) $(CFLAGS) -o task3 src/03_fork_basic.c

# Regra 'clean' para apagar os arquivos compilados
clean:
	rm -f task2 task3

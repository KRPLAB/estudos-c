# Variáveis
CC = gcc
CFLAGS = -Wall -Werror -pedantic -Iinclude
TARGET = triangulacao_gauss
OBJS = main.o matriz.o triangulacao.o
HEADERS = include/matriz.h include/triangulacao_gauss.h
SRC_DIR = src
INC_DIR = include

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) -lm

main.o: $(SRC_DIR)/main.c $(HEADERS)
	$(CC) -c $(SRC_DIR)/main.c -o main.o $(CFLAGS)

matriz.o: $(SRC_DIR)/matriz.c $(HEADERS)
	$(CC) -c $(SRC_DIR)/matriz.c -o matriz.o $(CFLAGS)

triangulacao.o: $(SRC_DIR)/triangulacao_gauss.c $(HEADERS)
	$(CC) -c $(SRC_DIR)/triangulacao_gauss.c -o triangulacao.o $(CFLAGS)

clean:
	rm -f *.o $(TARGET)
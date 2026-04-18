# cmd/server/Makefile
# Compilação do servidor HTTP

include ../../config/config.mk

# Caminhos corrigidos
ROOT_BUILD_DIR = ../../build
SRCS = main.c
OBJS = $(ROOT_BUILD_DIR)/obj/cmd/server/$(SRCS:.c=.o)
TARGET = $(ROOT_BUILD_DIR)/bin/server

# Referências às bibliotecas compartilhadas
LIBS = $(ROOT_BUILD_DIR)/.network.a $(ROOT_BUILD_DIR)/.utils.a

all: $(LIBS) $(TARGET)

$(TARGET): $(OBJS) $(LIBS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $@ $(LDFLAGS)

$(ROOT_BUILD_DIR)/obj/cmd/server/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(ROOT_BUILD_DIR)/obj/cmd

.PHONY: all clean

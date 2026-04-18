# cmd/client/Makefile
# Compilação do cliente HTTP

include ../../config/config.mk

# Caminhos corrigidos
ROOT_BUILD_DIR = ../../build
SRCS = main.c
OBJS = $(ROOT_BUILD_DIR)/obj/cmd/client/$(SRCS:.c=.o)
TARGET = $(ROOT_BUILD_DIR)/bin/client

# Referências às bibliotecas compartilhadas
LIBS = $(ROOT_BUILD_DIR)/.client.a

all: $(LIBS) $(TARGET)

$(TARGET): $(OBJS) $(LIBS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $@ $(LDFLAGS)

$(ROOT_BUILD_DIR)/obj/cmd/client/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(ROOT_BUILD_DIR)/obj/cmd/client

.PHONY: all clean

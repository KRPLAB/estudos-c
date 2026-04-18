# src/network/Makefile
# Compilação da biblioteca de rede

include ../../config/config.mk

# Caminhos corrigidos
ROOT_BUILD_DIR = ../../build
SRCS = server.c
OBJS = $(ROOT_BUILD_DIR)/obj/network/$(SRCS:.c=.o)
TARGET = $(ROOT_BUILD_DIR)/.network.a

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	$(AR) rcs $@ $^
	$(RANLIB) $@

$(ROOT_BUILD_DIR)/obj/network/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(ROOT_BUILD_DIR)/obj/network

.PHONY: all clean

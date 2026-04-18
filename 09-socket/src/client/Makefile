# src/client/Makefile
# Compilação da biblioteca de cliente HTTP

include ../../config/config.mk

# Caminhos corrigidos
ROOT_BUILD_DIR = ../../build
SRCS = client.c
OBJS = $(ROOT_BUILD_DIR)/obj/client/$(SRCS:.c=.o)
TARGET = $(ROOT_BUILD_DIR)/.client.a

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	$(AR) rcs $@ $^
	$(RANLIB) $@

$(ROOT_BUILD_DIR)/obj/client/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(ROOT_BUILD_DIR)/obj/client

.PHONY: all clean

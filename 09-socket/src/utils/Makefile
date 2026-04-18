# src/utils/Makefile
# Compilação da biblioteca de utilidades

include ../../config/config.mk


# Caminhos corrigidos
ROOT_BUILD_DIR = ../../build
SRCS = utils.c cJSON.c
OBJS = $(ROOT_BUILD_DIR)/obj/utils/$(SRCS:.c=.o)
TARGET = $(ROOT_BUILD_DIR)/.utils.a

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	$(AR) rcs $@ $^
	$(RANLIB) $@

$(ROOT_BUILD_DIR)/obj/utils/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(ROOT_BUILD_DIR)/obj/utils

.PHONY: all clean

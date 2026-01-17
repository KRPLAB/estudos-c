# lib/basic/Makefile
include ../../config.mk

LIB = libbasic.a
OBJS = log.o  # Adicionaremos mais objetos aqui futuramente

all: $(LIB)

$(LIB): $(OBJS)
	$(AR) rcs $@ $(OBJS)

clean:
	rm -f $(OBJS) $(LIB)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
include ../../config.mk

LIB = libnetwork.a
OBJS = server.o

all: $(LIB)

$(LIB): $(OBJS)
	$(AR) rcs $@ $(OBJS)

clean:
	rm -f $(OBJS) $(LIB)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
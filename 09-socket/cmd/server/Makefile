# cmd/server/Makefile
include ../../config.mk

TARGET = redis-server
OBJS = main.o

# Bibliotecas necessárias (caminho relativo)
LIBS = ../../lib/basic/libbasic.a ../../lib/network/libnetwork.a

all: $(TARGET)

$(TARGET): $(OBJS) $(LIBS)
	$(CC) $(OBJS) $(LIBS) -o $@ $(LDFLAGS)

clean:
	rm -f $(OBJS) $(TARGET) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
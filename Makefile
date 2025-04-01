.POSIX:

include config.mk

SOURCES = main.c socket.c http.c utils.c file.c

all: hermes

hermes: $(SOURCES:.c=.o)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f hermes *.o

.PHONY: all clean

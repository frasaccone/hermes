.POSIX:

include config.mk

SOURCES = hermes.c socket.c http.c utils.c

hermes: $(SOURCES:.c=.o)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f hermes *.o

.PHONY: clean

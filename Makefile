.POSIX:

include config.mk

SOURCES = main.c socket.c http.c utils.c file.c

all: hermes

options:
	@echo "CC         = ${CC}"
	@echo "CFLAGS     = ${CFLAGS}"
	@echo "PREFIX     = ${PREFIX}"
	@echo "MANPREFIX  = ${MANPREFIX}"

hermes: $(SOURCES:.c=.o)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f hermes *.o

install: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f hermes $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/hermes
	mkdir -p $(DESTDIR)$(MANPREFIX)/man1
	cp -f hermes.1 $(DESTDIR)$(MANPREFIX)/man1
	chmod 644 $(DESTDIR)$(MANPREFIX)/man1/hermes.1

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/hermes
	rm -f $(DESTDIR)$(PREFIX)/man1/hermes.1

.PHONY: all options clean install uninstall

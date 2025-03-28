.POSIX:

include config.mk

hermes: hermes.o
	$(CC) $(CFLAGS) -o $@ $^

hermes.o: hermes.c
	$(CC) $(CFLAGS) -c $<

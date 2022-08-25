CC = gcc
LIB = -lcurses

wttr: wttr.c
	$(CC) wttr.c -o wttr $(LIB)

install:
	cp wttr /usr/bin

uninstall:
	rm -f /usr/bin/wttr

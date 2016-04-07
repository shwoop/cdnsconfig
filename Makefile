PREFIX =
BINDIR = ${PREFIX}/bin
DESTDIR =

CC = gcc
CFLAGS = -g -std=gnu99 -Os -Wall -Wextra

SUIDROOT = cdnsconfig

all: ${SUIDROOT}

cdnsconfig: cdnsconfig.o

clean:
	rm -f -- ${SUIDROOT} tags *.o

install: ${SUIDROOT}
	mkdir -p ${DESTDIR}${BINDIR}
	install -g root -m 4755 -o root -s ${SUIDROOT} ${DESTDIR}${BINDIR}

tags:
	ctags -R

.PHONY: all clean install tags

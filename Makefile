# You'll probably have to change these.
CFLAGS=-Wall $(shell pkg-config --cflags libsecret-1)
LDLIBS=$(shell pkg-config --libs libsecret-1)

PREFIX:=/usr/local

.PHONY: all clean

all: secret-unlock secret-lock secret-check

clean:
	rm secret-unlock
	rm secret-lock
	rm secret-check

install:
	install -t $(PREFIX)/bin secret-lock
	install -t $(PREFIX)/bin secret-unlock
	install -t $(PREFIX)/bin secret-check

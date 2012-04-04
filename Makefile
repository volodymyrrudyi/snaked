
LIBS = $(shell pkg-config --libs libevent)
CFLAGS = $(shell pkg-config --cflags libevent)
CFLAGS += -Werror -Wall -std=c99


SOURCES = src/snake-player.c src/snake-section.c src/main.c src/snake-field.c src/snake-game.c src/snake-server.c
all: $(SOURCES)
	gcc $(CFLAGS) $(SOURCES) $(LIBS) -o bin/snaked

clean:
	rm bin/snaked

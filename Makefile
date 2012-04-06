CFLAGS += -Werror -Wall -std=c99 -I include
LIBS = -lpthread

SOURCES = src/snake-player.c src/snake-section.c src/main.c src/snake-field.c src/snake-game.c src/snake-server.c lib/snake-proto.c
all: $(SOURCES)
	gcc $(CFLAGS) $(SOURCES) $(LIBS) -o bin/snaked

clean:
	rm bin/snaked

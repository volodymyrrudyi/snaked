CFLAGS = -Werror -Wall -std=c99

SOURCES = src/player.c src/snake-section.c src/main.c src/field.c src/game.c
all: $(SOURCES)
	gcc $(CFLAGS) $(SOURCES) -o bin/snaked

clean:
	rm bin/snaked

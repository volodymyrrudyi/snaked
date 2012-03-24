CLFAGS = -Werror -Wall --std=C99

all: $(SOURCES)
	gcc $(CFLAGS) $(SOURCES) -o bin/snaked

clean:
	rm bin/snaked

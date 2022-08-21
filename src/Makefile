all: build

clean:
	rm ../build/*

build:
	gcc -Wall -Wextra -Werror graph.c structs.c polish_notation.c parse.c draw.c -o ../build/graph

run: build
	leaks --quiet --atExit -- ./../build/graph

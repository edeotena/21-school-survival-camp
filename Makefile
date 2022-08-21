all:
	gcc -Wall -Wextra -Werror src/graph.c src/structs.c src/polish_notation.c src/parse.c src/draw.c -o build/graph

clean:
	rm build/*

build:
	gcc -Wall -Wextra -Werror src/graph.c src/structs.c src/polish_notation.c src/parse.c src/draw.c -o build/graph

run: build
	leaks --quiet --atExit -- ./build/graph

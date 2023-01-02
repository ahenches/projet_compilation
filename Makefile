flags=-Wall -g


DetMin: main.c 
	gcc $(flags) $^ -o $@

flags=-Wall -g


DetMin: main.c afn.o afd.o
	gcc $(flags) $^ -o $@

automate.o: afn.c afd.c
	gcc $^ -c $@

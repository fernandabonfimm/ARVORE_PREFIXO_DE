CC=g++
outfile = out

main: main.o ARVORE_PREFIXO.o
	$(CC) main.o ARVORE_PREFIXO.o -o $(outfile)
main.o: main.cpp
	$(CC) -c main.cpp -o main.o
superTrunfo.o: ARVORE_PREFIXO.cpp
	$(CC) -c ARVORE_PREFIXO.cpp -o ARVORE_PREFIXO.o
clean:
	rm *.o $(outfile)

debug: CC+= -g
debug: main
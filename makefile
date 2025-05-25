all: compila executa clean
compila: main.o grafo.o 
	gcc main.o grafo.o -o trabalho -lm
main.o: main.c
	gcc -c main.c
grafo.o: grafo.c
	gcc -c grafo.c
executa:
	./trabalho
clean:
	rm main.o grafo.o trabalho

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

int main(int argc, char *argv[]){

	int numVertices = 0, aux = 0, temp = 0, numArestas = 0;
	float comprimentoMinimo = 0;
	char arquivo[50];
	
	printf("Digite o nome do arquivo de entrada: ");
	scanf("%s", arquivo); 
	
	FILE *arq = fopen(arquivo, "r");
	
	if(arq == NULL){
		perror("Erro ao abrir o arquivo");
		return EXIT_FAILURE;
	}
	
	if((fscanf(arq, "%d", &numVertices)) == -1) {
		printf("Arquivo vazio\n");
		exit(0);
	}

	int x[numVertices];
        int y[numVertices];

        for(int i = 0; i < numVertices; i++){
          fscanf(arq, "%d %d", &x[i], &y[i]);
        }
        fclose(arq);

        float **matriz = criaMatriz(numVertices);
        alocaMatriz(matriz, numVertices);
        zeraMatriz(matriz, numVertices);
        preencheMatriz(matriz, x, y, numVertices);
  
        numArestas = (numVertices * (numVertices - 1)) / 2;
        Aresta arestas[numArestas];
        criaListaArestas(matriz, arestas, numVertices);

        comprimentoMinimo = kruskal(arestas, numArestas, numVertices);
        printf("%.2f\n", comprimentoMinimo);
}

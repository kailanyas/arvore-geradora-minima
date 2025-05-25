#ifndef GRAFO_H
#define GRAFO_H

typedef struct aresta{
    int u, v;
    float peso;
}Aresta;

typedef struct subconjunto{
    int pais, tamanho;
}Subconjunto;

float **criaMatriz(int numVertices);

void alocaMatriz(float **matriz, int numVertices);

void zeraMatriz(float **matriz, int numVertices);

void imprimeMatriz(float **matriz, int numVertices);

float calculaDistancia(int x1, int y1, int x2, int y2);

void preencheMatriz(float **matriz, int x[], int y[], int numVertices);

void criaListaArestas(float **matriz, Aresta arestas[], int numVertices);

int encontrar(Subconjunto subconjuntos[], int i);

void união(Subconjunto subconjuntos[], int x, int y);

void troca(Aresta *a, Aresta *b);

void bubbleSort(Aresta *arestas, int numArestas);

float kruskal(Aresta arestas[], int numArestas, int numVertices);

#endif

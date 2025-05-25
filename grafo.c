#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "grafo.h"

// criando matriz de adjacência
float **criaMatriz(int numVertices){
    float **matriz = malloc(numVertices * sizeof(float*));
    return matriz;
}

void alocaMatriz(float **matriz, int numVertices){
    int i;
    for(i = 0; i < numVertices; i++){
        matriz[i] = malloc(numVertices * sizeof(float));
    }
}

void zeraMatriz(float **matriz, int numVertices){
    int i, j;
    for(i = 0; i < numVertices; i++){
        for(j = 0; j < numVertices; j++){
            matriz[i][j] = 0;
        }
    }
}

// função que imprime a matriz (feita para testes)
void imprimeMatriz(float **matriz, int numVertices){
    int i, j;
    for(i = 0; i < numVertices; i++){
        for(j = 0; j < numVertices; j++){
            printf("%.2f, ", matriz[i][j]);
        }
        printf("\n");
    }
}

// função que calcula a distância entre dois pontos
float calculaDistancia(int x1, int y1, int x2, int y2){
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

// função que preenche a matriz com as distâncias entre todos os pares de vértices
void preencheMatriz(float **matriz, int x[], int y[], int numVertices){
    for(int i = 0; i < numVertices; i++){
        for(int j = i + 1; j < numVertices; j++){
            float distancia = calculaDistancia(x[i], y[i], x[j], y[j]);
            matriz[i][j] = distancia;
            matriz[j][i] = distancia;
        }
    }
}

// função que cria a lista de arestas do algoritmo de kruskal
void criaListaArestas(float **matriz, Aresta arestas[], int numVertices){
    int contador = 0;
    for(int i = 0; i < numVertices; i++){
        for(int j = i + 1; j < numVertices; j++){
            arestas[contador].u = i;
            arestas[contador].v = j;
            arestas[contador].peso = matriz[i][j];
            contador++;
        }
    }
}

// função para encontrar o representante de um subconjunto
int encontrar(Subconjunto subconjuntos[], int i){
    if(subconjuntos[i].pais != i){
        subconjuntos[i].pais = encontrar(subconjuntos, subconjuntos[i].pais);
    }
    return subconjuntos[i].pais;
}

// função para unir dois subconjuntos pelo tamanho
void união(Subconjunto subconjuntos[], int x, int y){
    int raizX = encontrar(subconjuntos, x);
    int raizY = encontrar(subconjuntos, y);

    if(raizX != raizY){
        if(subconjuntos[raizX].tamanho < subconjuntos[raizY].tamanho){
            subconjuntos[raizX].pais = raizY;
        }
        else if(subconjuntos[raizX].tamanho > subconjuntos[raizY].tamanho){
            subconjuntos[raizY].pais = raizX;
        }
        else{
            subconjuntos[raizY].pais = raizX;
            subconjuntos[raizX].tamanho++;
        }
    }
}

void troca(Aresta *a, Aresta *b){
    Aresta temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(Aresta *arestas, int numArestas){
    int i, j;
    for(i = 0; i < numArestas - 1; i++){
        for(j = 0; j < numArestas - i - 1; j++){
            if(arestas[j].peso > arestas[j + 1].peso){
                troca(&arestas[j], &arestas[j + 1]);
            }
        }
    }
}

// algoritmo de kruskal para calcular AGM
float kruskal(Aresta arestas[], int numArestas, int numVertices){
    Subconjunto *subconjuntos = malloc(numVertices * sizeof(Subconjunto));
    float comprimentoMinimo = 0.0;
    int arestasUsadas = 0;
    
    bubbleSort(arestas, numArestas);
    for(int i = 0; i < numVertices; i++){
        subconjuntos[i].pais = i;
        subconjuntos[i].tamanho = 0;
    }

    for(int i = 0; i < numArestas && arestasUsadas < numVertices - 1; i++){
        int u = arestas[i].u;
        int v = arestas[i].v;

        int conjuntoU = encontrar(subconjuntos, u);
        int conjuntoV = encontrar(subconjuntos, v);

        if (conjuntoU != conjuntoV) {
            comprimentoMinimo += arestas[i].peso;
            união(subconjuntos, conjuntoU, conjuntoV);
            arestasUsadas++;
        }
    }

    free(subconjuntos);
    return comprimentoMinimo;
}

/* ESTO NO SE ENTREGA */
//To do : construir test para ver funcionalidad

#include "APIG24.h"
#include "APIG2024Parte2.h"
#include "EstructuraGrafo24.h"
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#define DGB(a) printf(#a);printf(" = %u\n", a)
#define min(x, y) ((x) < (y) ? (x) : (y))
#define RAYA printf("------------------\n");
#define NRUNS 50u
#define NRANDRUNS 500u


void printColores(Grafo G) {
    u32 n = NumeroDeVertices(G);
    for (u32 i = 0; i < n; i++) {
        printf("Vertice %u tiene color %d\n", i, Color(i, G));
    }
}

//tuplas para sortear los vertices;
struct tuple{
    u32 vert;
    u32 val;
};

//func de comparacion para ordenar las tuplas
int comparedescc(struct tuple *a, struct tuple *b){
    return (int)b->val - (int)a->val;
}
//programa para testear

int main(void){
    close(0);
    u32 fd = open("test.txt", O_RDONLY);
    if(fd){
        printf("AIUDA\n");
    }
    //Esta parte armaria el grafo que este en un archivo test.txt.
    Grafo g = ConstruirGrafo();

    // Imprimir información básica del grafo
    printf("Número de vértices: %u\n", NumeroDeVertices(g));
    printf("Número de lados: %u\n", NumeroDeLados(g));
    printf("Delta: %u\n", Delta(g));
    u32 n = NumeroDeVertices(g);
    u32 *colores1 = malloc(n*sizeof(u32)), *colores2 = malloc(n*sizeof(u32)), *colores3 = malloc(n*sizeof(u32)), *colores4 = malloc(n*sizeof(u32)), *colores5 = malloc(n*sizeof(u32));
    // Orden Natural
    u32 *Orden = malloc(sizeof(u32) * n);
    for (u32 i = 0; i < n; ++i) {
        Orden[i] = i;
    }
    printf("Greedy en orden natural: \n");
    u32 mejorColoreo1 = Greedy(g,Orden);
    // Ejecutar el algoritmo Greedy y mostrar los colores después de cada iteración
    for(u32 i = 0; i<NRUNS; ++i){
        GulDukat(g,Orden);
        mejorColoreo1 = min(mejorColoreo1,Greedy(g,Orden));
        ElimGarak(g,Orden);
        mejorColoreo1 = min(mejorColoreo1,Greedy(g,Orden));
    }
    ExtraerColores(g,colores1);
    DGB(mejorColoreo1);
    RAYA;
    // Orden n-1,...1,0
    for (u32 i = 0; i < n; ++i) {
        Orden[i] = (n-1)-i;
    }
    printf("Greedy en orden natural inverso: \n");
    u32 mejorColoreo2 = Greedy(g,Orden);
    // Ejecutar el algoritmo Greedy y mostrar los colores después de cada iteración
    for(u32 i = 0; i<NRUNS; ++i){
        GulDukat(g,Orden);
        mejorColoreo2 = min(mejorColoreo2,Greedy(g,Orden));
        ElimGarak(g,Orden);
        mejorColoreo2 = min(mejorColoreo2,Greedy(g,Orden));
    }
    ExtraerColores(g,colores2);
    DGB(mejorColoreo2);
    RAYA;
    // Orden pares creciente, impares creciente
    u32 ord = 0;
    for (u32 i = 0; i < n/2; ++i) {
        Orden[ord] = 2*i;
        ++ord;
    }
    if(n&1){
        Orden[ord] = n-1;
        ++ord;
    }
    for (u32 i = 0; i < n/2; ++i) {
        Orden[ord] = 2*i+1;
        ++ord;
    }
    printf("Greedy en orden pares impares: \n");
    u32 mejorColoreo3 = Greedy(g,Orden);
    // Ejecutar el algoritmo Greedy y mostrar los colores después de cada iteración
    for(u32 i = 0; i<NRUNS; ++i){
        GulDukat(g,Orden);
        mejorColoreo3 = min(mejorColoreo3,Greedy(g,Orden));;
        ElimGarak(g,Orden);
        mejorColoreo3 = min(mejorColoreo3,Greedy(g,Orden));
    }
    ExtraerColores(g,colores3);
    DGB(mejorColoreo3);
    RAYA;
    //Vertices ordenados de acuerdo a su grado
    struct tuple *vertices = malloc(sizeof(struct tuple)*n);
    struct tuple toadd;
    for(u32 i = 0; i<n; ++i){
        toadd.vert = i;
        toadd.val = Grado(i,g);
        vertices[i] = toadd;
    }
    qsort(vertices, n, sizeof(struct tuple), comparedescc);
    for(u32 i = 0; i<n; ++i){
        Orden[i] = vertices[i].vert;
    }
    printf("Greedy por orden no ascendente de grados\n");
    u32 mejorColoreo4 = Greedy(g,Orden);
    // Ejecutar el algoritmo Greedy y mostrar los colores después de cada iteración
    for(u32 i = 0; i<NRUNS; ++i){
        GulDukat(g,Orden);
        mejorColoreo4 = min(mejorColoreo4,Greedy(g,Orden));
        ElimGarak(g,Orden);
        mejorColoreo4 = min(mejorColoreo4,Greedy(g,Orden));
    }
    ExtraerColores(g,colores4);
    DGB(mejorColoreo4);
    RAYA;
    //Orden elegido por nosotros: Primero siempre al 10
    for (u32 i = 0; i < n; ++i) {
        Orden[i] = i;
    }
    if(n>10){
        Orden[10] = 0;
        Orden[0] = 10;
    }
    printf("Greedy por primero al 10\n");
    u32 mejorColoreo5 = Greedy(g,Orden);
    // Ejecutar el algoritmo Greedy y mostrar los colores después de cada iteración
    for(u32 i = 0; i<NRUNS; ++i){
        GulDukat(g,Orden);
        mejorColoreo5 = min(mejorColoreo5,Greedy(g,Orden));
        ElimGarak(g,Orden);
        mejorColoreo5 = min(mejorColoreo5,Greedy(g,Orden));
    }
    ExtraerColores(g,colores5);
    DGB(mejorColoreo5);
    RAYA;
    u32 mejorColoreo = mejorColoreo1;
    mejorColoreo = min(mejorColoreo2,mejorColoreo);
    mejorColoreo = min(mejorColoreo3,mejorColoreo);
    mejorColoreo = min(mejorColoreo4,mejorColoreo);
    mejorColoreo = min(mejorColoreo5,mejorColoreo);
    if(mejorColoreo == mejorColoreo1){
        ImportarColores(colores1,g);
    }
    else if(mejorColoreo == mejorColoreo2){
        ImportarColores(colores1,g);
    }
    else if(mejorColoreo == mejorColoreo3){
        ImportarColores(colores1,g);
    }
    else if(mejorColoreo == mejorColoreo4){
        ImportarColores(colores1,g);
    }
    else if(mejorColoreo == mejorColoreo5){
        ImportarColores(colores1,g);
    }
    for(u32 i = 0; i<NRANDRUNS; ++i){
        if(rand()%2){
            GulDukat(g,Orden);
        }
        else{
            ElimGarak(g,Orden);
        }
        mejorColoreo = min(mejorColoreo,Greedy(g,Orden));
    }
    DGB(mejorColoreo);
    free(vertices);
    free(Orden);
    free(colores1);free(colores2);free(colores3);free(colores4);free(colores5);
    DestruirGrafo(g);
    return 0;
}

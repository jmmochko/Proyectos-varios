#define max(x, y) ((x) > (y) ? (x) : (y))
#include "APIG24.h"

/* lee un grafo desde
standard input en el formato indicado en la última sección, lo carga en la estructura, colorea todos los vertices
con el color 0, y devuelve un puntero a la estructura.
En caso de error, la función devolverá un puntero a NULL */

Grafo ConstruirGrafo(){
    char Fchar;
    int aux = 0;
    u32 r ;
    u32 l ;
    Grafo g = malloc(sizeof(struct GrafoSt));
    if(g == NULL){
        return NULL;
    }
    //lee hasta que la primera letra es p 
    while (fscanf(stdin, "%c", &Fchar) != EOF && Fchar == 'c') {
        ++aux;
        while (fscanf(stdin, "%c", &Fchar) != EOF && Fchar != '\n');
    }
    // lee cantidad de vertices y aristas
    aux = fscanf(stdin, " edge %u %u", &g->vertex_num, &g->edges_num);
    if(aux<0){
        return NULL;
    }
    g->delta = 0 ;
    g->vertexes = malloc(sizeof(struct s_vertex)*(g->vertex_num));
    for(u32 i = 0; i<g->vertex_num; ++i){
        g->vertexes[i].vecinos = list_init();
    }
    for(u32 i = 0; i <g->edges_num; ++i){
        aux = fscanf(stdin, "%*s %u %u", &l, &r);
        if(aux<0){
            return NULL;
        }
        list_append(g->vertexes[l].vecinos, r);
        list_append(g->vertexes[r].vecinos, l);
    }
    for(u32 i = 0; i<g->vertex_num; ++i){
        g->delta = max(g->delta, g->vertexes[i].vecinos->length);
    }
    for(u32 i=0u; i<g->vertex_num; i++){
        g->vertexes[i].color = 0;
    }
    return g;
}

void DestruirGrafo(Grafo G){
    if( G != NULL){
        for(u32 i = 0; i<G->vertex_num; ++i){
            list_destroy(G->vertexes[i].vecinos);
        }
        free(G->vertexes);
        free(G);
    }
}

u32 NumeroDeVertices(Grafo G){
    return G->vertex_num ;
}
u32 NumeroDeLados(Grafo G){
    return G->edges_num ;
}
u32 Delta(Grafo G){
    return G->delta ;
}

u32 Grado(u32 i,Grafo G){
    return G->vertexes[i].vecinos->length;
}
color Color(u32 i,Grafo G){
    if(i < G->vertex_num){
        return G->vertexes[i].color ;
    } else {
        return 4294967295;
    }
}
u32 Vecino(u32 j,u32 i,Grafo G){
    if( i >= G->vertex_num || (i < G->vertex_num && j >= Grado(i,G))){
        return 4294967295 ; //2^32 -1 
    } else if (i < G->vertex_num && j < Grado(i, G)){
        return list_index(G->vertexes[i].vecinos, j); 
    }
    return 0;
}

void AsignarColor(color x,u32 i,Grafo  G){
    if(i < G->vertex_num){
        G->vertexes[i].color = x ;
    }
}
void ExtraerColores(Grafo G,color* Color){
    for (u32 i = 0 ; i < G->vertex_num; i+=1){
        Color[i] = G->vertexes[i].color ;
    }
}
void ImportarColores(color* Color,Grafo  G){
    u32 n = G->vertex_num;
    
    for(unsigned int i = 0; i < n ; i++){
        G->vertexes[i].color = Color[i];
    }

}
#include "APIG24.h"
#include "APIG2024Parte2.h"
#include <stdlib.h>

#define max(x, y) ((x) > (y) ? (x) : (y))
#define min(x, y) ((x) < (y) ? (x) : (y))
/*
procedure GreedyColoring(Graph G(V, E))
for all v ∈ V (G) do
    color(v) ← −1
for all v ∈ V (G) in order do
    isCol(1 . . . ∆(G) + 1) ← false
    for all u ∈ N(v) where color(u) != −1 do
        isCol(color(u)) ← true
    for k = 1 . . . ∆(G) + 1 do
        if isCol(k) = false then
        color(v) ← k
        break
k ← max(color(1 . . . n))
return k
*/
u32 Greedy(Grafo G,u32* Orden){
    u32 n = NumeroDeVertices(G);
    u32 m = NumeroDeLados(G);
    u32 delta = Delta(G);
    color *colores = calloc(n,sizeof(u32)); // Arreglo para almacenar los colores de los vértices
  
    colores[0] = 1 ; // color del primer vertice
    for (u32 i = 0; i < n; i++) {
        u32 v = Orden[i]; // Obtener el siguiente vértice en el orden
        u32 *isCol = calloc(delta + 1,sizeof(u32));  // arreglo temporal con colores disponibles
        // valor de isCol[j] significa que el color j 
        //es asignado a uno de sus vertices adjacentes
        //asigna colores a los restantes V-1 vertices
        for (u32 j = 0; j < Grado(v,G); j++) {
            //procesa todos los vertices adjacentes y marca sus colores como no disponiblescta
            u32 vecino = Vecino(j, v, G);
            color colorVecino = colores[vecino];
            if (colorVecino != 0) {
                isCol[colorVecino] = true;
            }
        }
        /*
        //mensajes de depuración para verificar el estado de isCol
        printf("Después de marcar los colores de los vecinos del vértice %u:\n", v);
        for (u32 k = 0; k <= delta; k++) {
            printf("Color %u está disponible: %s\n", k + 1, isCol[k] ? "true" : "false");
        }
        */

        // Encontrar el primer color disponible y asignarlo al vértice actual
        for (u32 k = 1; k <= delta + 1; k++) {
            if (isCol[k] == 0) {
                colores[v] = k;
                AsignarColor(k, v, G); // Colorear el vértice v con el color k
                break;
            }
        }
        free(isCol);
    }

    u32 maxColor = colores[Orden[0]];
    for (u32 i = 1; i < n; i++) {
        if (colores[Orden[i]] > maxColor) {
            maxColor = colores[Orden[i]];
        }
    }
    free(colores);
    return maxColor;
}

//initializes an empty llist, returns pointer to struct s_llist
//llist elements are of u32 type, meant to be neighbouring vertex IDs
typedef struct s_llist *llist ;

struct s_llist {
    u32 *chunk; //points to an array with the actual list elements
    u32 length; //number of elements in the list
    u32 allocd; //how much memory has been alloc´d to the list
}; 

llist llist_init(){
    llist new = malloc(sizeof(struct s_llist));
    new->length = 0;
    new->chunk = malloc(sizeof(u32)*2);
    new->allocd = 2;
    return new;
}

//adds element <e> to llist <l>
//usually O(1), O(l->length) when llist was full
void llist_append(llist l, u32 e){
    //If more memory is needed, we realloc to twice the size
    if(l->length>=l->allocd){
        l->chunk = realloc(l->chunk, sizeof(u32)*l->length*2);
    }
    l->chunk[l->length] = e;
    l->length++;
    return;
}

//frees all memory used by llist <l>
llist llist_destroy(llist l){
    if(l != NULL){
        free(l->chunk);
        free(l);
    }
    return NULL;
}

// en estas tuplas vamos a guardar el valor de orden de un vertice y su numero
struct tuple{
    u32 val;
    u32 vert;
};

//funcion de comparación para ordenar las tuplas
int comparedesc(struct tuple *a, struct tuple *b){
    return (int)b->val - (int)a->val;
}

int compareasc(struct tuple *a, struct tuple *b){
    return (int)a->val - (int)b->val;
}

//TO DO: manejo de errores, testing
char GulDukat(Grafo G,u32* Orden){
    u32 *inicial = malloc(sizeof(u32)*NumeroDeVertices(G));
    // En inicial guardamos los colores originales del grafo;
    if(inicial==NULL){
        return (char)1;
    }
    ExtraerColores(G,inicial);
    u32 r = 0;
    for (u32 i = 0 ; i < NumeroDeVertices(G); i++){
        r = max(r,inicial[i]);
    }
    if(r<=0 || r>NumeroDeVertices(G)){
        return (char)1;
    }
    //en cnt guardamos cuantas veces aparece cada color, en m el grado minimo entre los vertices que tienen ese color y en M el maximo
    //cnt[i] = ocurrencias del color i+1, m[i] = grado minimo del color i+1, M[i] grado maximo del color i+1
    u32 *cnt = calloc(r,sizeof(u32)), *m=calloc(r,sizeof(u32)), *M=calloc(r,sizeof(u32));
    if(cnt == NULL || m == NULL || M == NULL){
        return (char)1;
    }
    for(u32 i = 0; i<NumeroDeVertices(G); ++i){
        cnt[inicial[i]-1]++;
        M[inicial[i]-1] = max(M[inicial[i]-1],Grado(i,G));
        if(m[inicial[i]-1]!=0){
            m[inicial[i]-1] = min(m[inicial[i]-1],Grado(i,G));
        }
        else{
            m[inicial[i]-1] = Grado(i,G);
        }
    }
    // crear tuplas <M(x), i del color> para todos los colores divisibles por 4
    // <M(x) + m(x), i del color> para divisibles por 2 y <m(x), i> para el resto
    u32 num4s = 0, num2s = 0;
    for(u32 i=2; i<=r; i+=2){
        if(i%4==0){
            num4s++;
        }
        else{
            num2s++;
        }
    }
    struct tuple t4s[num4s], t2s[num2s], t13s[(r - num4s) - num2s];
    u32 t4 = 0, t2 = 0, t13 = 0; 
    for(u32 i=0; i<r; ++i){
        struct tuple toadd;
        toadd.vert = i;
        if((i+1)%4==0){
            toadd.val = M[i];
            t4s[t4] = toadd;
            ++t4;
        }
        else if((i+1)%2==0){
            toadd.val = M[i] + m[i];
            t2s[t2] = toadd;
            ++t2;
        }
        else{
            toadd.val = m[i];
            t13s[t13] = toadd;
            ++t13;
        }
    }
    //sorteo de mayor a menor en base a su val de comparacion
    qsort(t4s, t4, sizeof(struct tuple), comparedesc);
    qsort(t2s, t2, sizeof(struct tuple), comparedesc);
    qsort(t13s, t13, sizeof(struct tuple), comparedesc);
    //ahora armo llistas con todods los vertices de todos los colores
    //acá voy a guardar todos los vertices con color i en vertdecol[i-1]
    llist vertdecol[r];
    for(u32 i = 0; i<r; ++i){
        vertdecol[i] = llist_init();
    }
    for(u32 i = 0; i<NumeroDeVertices(G); ++i){
        llist_append(vertdecol[inicial[i]-1],i);
    }
    //guardo los vertices en Orden de acuerdo a como los sortee
    u32 ord = 0;
    for(u32 i = 0; i<t4; ++i){
        for(u32 j = 0; j<vertdecol[t4s[i].vert]->length; ++j){
            Orden[ord] = vertdecol[t4s[i].vert]->chunk[j];
            ++ord;
        }
    }
    for(u32 i = 0; i<t2; ++i){
        for(u32 j = 0; j<vertdecol[t2s[i].vert]->length; ++j){
            Orden[ord] = vertdecol[t2s[i].vert]->chunk[j];
            ++ord;
        }
    }
    for(u32 i = 0; i<t13; ++i){
        for(u32 j = 0; j<vertdecol[t13s[i].vert]->length; ++j){
            Orden[ord] = vertdecol[t13s[i].vert]->chunk[j];
            ++ord;
        }
    }
    //libero la memoria
    free(cnt);
    free(m);
    free(M);
    free(inicial);
    for(u32 i = 0; i<r; ++i){
        llist_destroy(vertdecol[i]);
    }
    //si todo bien returneo 0
    return 0;
}

char ElimGarak(Grafo G,u32* Orden){
    if(NumeroDeVertices(G)==1){
        Orden[0] = 0;
        return 0;
    }
    u32 *inicial = malloc(sizeof(u32)*NumeroDeVertices(G));
    if(inicial==NULL){
        return (char)1;
    }
    // En inicial guardamos los colores originales del grafo;
    ExtraerColores(G,inicial);
    u32 r = 0;
    for (u32 i = 0 ; i < NumeroDeVertices(G); i++){
        r = max(r,inicial[i]);
    }
    // Acá voy a guardar todos los vertices con color i en vertdecol[i-1]
    llist vertdecol[r];
    for(u32 i = 0; i<r; ++i){
        vertdecol[i] = llist_init();
    }
    for(u32 i = 0; i<NumeroDeVertices(G); ++i){
        llist_append(vertdecol[inicial[i]-1],i);
    }
    u32 ord = 0;
    if(r>2){
        //Para ordenar los colores hago tuplas <cantidad de vertices,color>;
        u32 cantidadAOrdenar = r-2;
        struct tuple ordcolores[cantidadAOrdenar];
        for(u32 i = 0; i<cantidadAOrdenar; ++i){
            ordcolores[i].vert = i+2;
            ordcolores[i].val = vertdecol[i+2]->length;
        }
        //si tengo mas de dos colores, ordeno esos colores
        if(r-2>0){
            qsort(ordcolores,r-2,sizeof(struct tuple),compareasc);
        }
        //agrego todos los vertices de esos colores en el orden que quedo
        for(u32 i = 0; i<r-2; ++i){
            for(u32 j = 0; j<vertdecol[ordcolores[i].vert]->length; ++j){
                Orden[ord] = vertdecol[ordcolores[i].vert]->chunk[j];
                ++ord;
            }
        }
    }
    if(r>1){
        for(u32 j = 0; j<vertdecol[1]->length; ++j){
            Orden[ord] = vertdecol[1]->chunk[j];
            ++ord;
        }
    }
    for(u32 j = 0; j<vertdecol[0]->length; ++j){
        Orden[ord] = vertdecol[0]->chunk[j];
        ++ord;
    }
    //libero memoria
    free(inicial);
    for(u32 i = 0; i<r; ++i){
        llist_destroy(vertdecol[i]);
    }
    return (char)0;
}
#include <stdio.h>
#include <stdlib.h>             /* dynamic memory management*/
#include <stdbool.h>            /* Definition of bool      */
#include <assert.h>

typedef unsigned int u32 ;
typedef u32 color ;

typedef struct s_list *list ;
typedef struct s_vertex *vertex ;

struct s_list {
    u32 *chunk; //points to an array with the actual list elements
    u32 length; //number of elements in the list
    u32 allocd; //how much memory has been alloc´d to the list
}; 

struct s_vertex{
    u32 grado ; //d(v)
    color color ; //c(v)
    list vecinos ; //list with the number of neigbouring vertexes
};

struct GrafoSt {
    vertex *vertexes; //array of all the vertexes
    u32 vertex_num ; //total number of vertexes
    u32 edges_num ; //total number of edges
    u32 delta ; 
};
typedef struct GrafoSt GrafoSt ;

//initializes an empty list, returns pointer to struct s_list
//list elements are of u32 type, meant to be neighbouring vertex IDs
list list_init() ;

//adds element <e> to list <l>
//usually O(1), O(l->length) when list was full
void list_append(list l, u32 e);

//returns the <i>th element of list <l>
//assumes 0 <= i < l->length
//indexes start at 0
u32 list_index(list l, u32 i);

//frees all memory used by list <l>
list list_destroy(list l);


//initializes an empty list, returns pointer to struct s_list
//list elements are of u32 type, meant to be neighbouring vertex IDs
list list_init(){
    list new = malloc(sizeof(struct s_list));
    new->length = 0;
    new->chunk = malloc(sizeof(u32)*2);
    new->allocd = 2;
    return new;
}

//adds element <e> to list <l>
//usually O(1), O(l->length) when list was full
void list_append(list l, u32 e){
    //If more memory is needed, we realloc to twice the size
    if(l->length>=l->allocd){
        l->chunk = realloc(l->chunk, sizeof(u32)*l->length*2);
    }
    l->chunk[l->length] = e;
    l->length++;
    return;
}

//returns the <i>th element of list <l>
//assumes 0 <= i < l->length
//indexes start at 0
u32 list_index(list l, u32 i){
    return l->chunk[i];
}

//frees all memory used by list <l>
list list_destroy(list l){
    if(l != NULL){
        free(l->chunk);
        free(l);
    }
    return NULL;
}

int main(void){
    list l = list_init();
    for(u32 i = 0; i<100; ++i){
        list_append(l,i);
    }
    for(u32 i = 0; i<100; ++i){
        printf("%u ", list_index(l,i));
    }
    printf("\n");
    l = list_destroy(l);
    return 0;
}
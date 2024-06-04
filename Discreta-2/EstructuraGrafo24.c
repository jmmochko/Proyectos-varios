#include <stdio.h>
#include <stdlib.h>             /* dynamic memory management*/
#include <stdbool.h>            /* Definition of bool      */
#include <assert.h>
#include"EstructuraGrafo24.h"


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
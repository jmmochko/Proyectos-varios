#include <stdio.h>
//execvp si vuelve si falla
int main(int argc, char ** argv){
    fork();
    printf("HOLA");
    execvp(argv[argc-1], argv);
    main(argc, argv);
}
#include <stdio.h>
#include <unistd.h>

int main(int argc, char ** argv){
    printf("%d\n", argc);
    if(0<--argc){
        printf("%d\n", argc);
        argv[argc] = NULL;
        printf("%s\n", argv[0]);
        execvp(argv[0], argv);
    }
    return 0;
}
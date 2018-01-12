#include <cstdio>
#include <cstdlib>

char error_elemNotFound[] = "Search for requested element failed";
char error_nullPtrArgs[] = "Function invoked with null pointers as arguments";
char error_drawNotFed[] = "Cannot perform draw, vertices haven't been fed";
char error_drawNotIdx[] = "Cannot perform draw, indices not present";
char error_initPhase[] = "Cannot proceed after initialization step";

void logError(char errorCode[]){
    puts("Runtime Error!");
    printf("%s \n", errorCode);
    exit(EXIT_FAILURE);
    return;
}

void logError(const char *file, int line, char errorCode[]){
    puts("Runtime Error!");
    printf("ERROR! File %s at line %d \n", file, line);
    printf("%s \n", errorCode);
    exit(EXIT_FAILURE);
    return;
}
#include "scene/ErrorCode.hpp"

void logError(char errorCode[]){
    printf("%s \n", errorCode);
    exit(EXIT_FAILURE);
    return;
}

void logError(const char *file, int line, char errorCode[]){
    printf("ERROR! File %s at line %d \n", file, line);
    printf("%s \n", errorCode);
    exit(EXIT_FAILURE);
    return;
}
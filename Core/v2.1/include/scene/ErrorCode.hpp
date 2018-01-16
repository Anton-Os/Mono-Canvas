#ifndef ERROR_CODE_H
    #include <cstdio>
    #include <cstdlib>

    /* char error_elemNotFound[] = "Search for requested element failed";
    char error_nullPtrArgs[] = "Function invoked with null pointers as arguments";
    char error_drawNotFed[] = "Cannot perform draw, vertices haven't been fed";
    char error_drawNotIdx[] = "Cannot perform draw, indices not present";
    char error_initPhase[] = "Cannot proceed after initialization step"; */

    void logError(char errorCode[]);
    void logError(const char *file, int line, char errorCode[]);

#define ERROR_CODE_H
#endif
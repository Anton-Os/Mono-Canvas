#ifndef SCENE_H
    #include "Scene.hpp"
#endif

#ifndef ERROR_CODE_H
    void logError(char errorCode[]);
    void logError(const char *file, int line, char errorCode[]);
    void logWarning(char errorCode[]);
    void logWarning(const char *file, int line, char errorCode[]);
#define ERROR_CODE_H
#endif
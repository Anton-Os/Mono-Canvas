#ifndef LOADERS_H
    #include "Loaders.h"
#endif

#ifndef FILE_IO_H
    const std::string getParentDirectory(const char* path);
    char* readFile(const char* fileName);
    void writeFile(const std::string& fileName, const std::string& contents);
#define FILE_IO_H
#endif
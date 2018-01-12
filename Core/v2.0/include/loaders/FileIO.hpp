#ifndef LOADERS_H
    #include "Loaders.h"
#endif

#ifndef LOADERS_FILEIO_H
    const std::string getParentDirectory(const char* path);
    char* readFile(const char* fileName);
    void writeFile(const std::string& fileName, const std::string& contents);
#define LOADERS_FILEIO_H
#endif
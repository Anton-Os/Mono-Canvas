#ifndef LOADERS_H
    #include "Loaders.h"
#endif

#include <cstring>

const std::string getParentDirectory(const char* path) {
	const char* ptr = path + strlen(path);
	while (ptr != path && nullptr == strchr("\\/", *(--ptr)));
	std::size_t len = ptr - path;
	std::string result(path, len);
	std::cout << "Parent dir: " << result << std::endl;
	return result;
}

char* readFile(const char* fileName){
    FILE* file = fopen(fileName, "r");
    if (nullptr == file) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return nullptr;
    }

    fseek(file, 0, SEEK_END);
    int length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* source = new GLchar[length + 1];
    std::size_t n = fread(source, 1, length, file);
    if (n <= 0) {
        std::cerr << "Failed to read file (got " << n
                  << " bytes, expected " << length << " bytes)" << std::endl;
        return nullptr;
    }
    fclose(file);
    source[n] = '\0';

    return source;
}

/* void delFile_ifEmpty(const char* fileName){
    FILE* file = fopen(fileName, "r");
    if(!file){
        std::cout << "File is empty" << std::endl;
    } else {
        std::cout << "File: " << fileName << " has been deleted" << std::endl;
        remove(fileName);
    }
    fclose(file);
} */

void writeFile(const std::string& fileName, const std::string& contents){
    // delFile_ifEmpty(fileName);
    FILE* file = fopen(fileName.c_str(), "w");
    fwrite(contents.c_str(), sizeof(char), contents.size(), file);
    // if('\0' != contents.back()) fputc('\0', file);
    fclose(file);
}
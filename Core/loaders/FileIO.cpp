#include "Loaders.h"

#include <fstream>
#include <cstring>

const std::string getParentDir(const char* path) {
	const char* ptr = path + strlen(path);
	while (ptr != path && nullptr == strchr("\\/", *(--ptr)));
	std::size_t len = ptr - path;
	std::string result(path, len);
	std::cout << "Parent dir: " << result << std::endl;
	return result;
}

char* readFile(const std::string& fileName){
    std::ifstream fileReadStream;
    fileReadStream.open(fileName.c_str());

    if(fileReadStream){
        std::cout << "Reading file " << fileName << std::endl;
        fileReadStream.seekg(0, fileReadStream.end);
        int length = fileReadStream.tellg();
        if(length == 0){
            std::cerr << "Cannot read file containing zero data" << std::endl;
            return nullptr;
        }

        fileReadStream.seekg(0, fileReadStream.beg);
        char * fileContents = new char[length + 1];

        fileReadStream.read(fileContents, length);
        fileContents[length] = '\0';
        fileReadStream.close();
        std::cout.write(fileContents, length);
        return fileContents;
    } else {
        std::cout << "Failed to open file " << fileName << std::endl;
        return nullptr;
    }
}
#include <iostream>

#include "Loaders.h"

int main(int argc, char** argv) {
    std::string parentDir = getParentDirectory(argv[0]);
    std::string fileName("Anton.txt");
    std::string contents("Good day! \nGood Night! \n");
    writeFile(fileName, contents);
    writeFile(fileName, contents);
    writeFile(fileName, contents);
    return 0;
}

#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <memory>
#include <string>
#include <windows.h>

extern "C" {
    #include <unqlite.h>
}

float zVal = 0.5f; 
float wVal = 1.0f;

const float XYZW[][4] = {
    {-0.5f, 0.5f, zVal, wVal}, {-0.5f, 0.5f, zVal, wVal}, {-0.5f, -0.5f, zVal, wVal}, {0.5f, -0.5f, zVal, wVal},
    {-0.1f, 0.9f, zVal, wVal}, {-0.1f, 0.9f, zVal, wVal}, {-0.1f, -0.9f, zVal, wVal}, {0.1f, -0.9f, zVal, wVal},
    {-0.3f, 0.2f, zVal, wVal}, {-0.3f, 0.2f, zVal, wVal}, {-0.3f, -0.2f, zVal, wVal}, {0.3f, -0.2f, zVal, wVal},
    {-0.4f, 0.6f, zVal, wVal}, {-0.4f, 0.6f, zVal, wVal}, {-0.4f, -0.6f, zVal, wVal}, {0.4f, -0.6f, zVal, wVal}
};

void unqliteInstance(const char* fileName){
    unqlite* unqDB;
    int unqInstance = unqlite_open(&unqDB, fileName, UNQLITE_OPEN_CREATE);
    if(unqInstance != UNQLITE_OK){
        std::cerr << "Unqlite failed to open " << fileName << std::endl;
        return;
    } else {
        std::cout << "Successfuly opened unqlite instance " << fileName << std::endl;
        return;
    }
}

bool proofXYZW(float* coordinates, int coordinatesSize){
    bool isValid = true;
    for(int iterations = 0; iterations < coordinatesSize / sizeof(float); iterations++){
        std::cout << "Iterations count: " << iterations << std::endl;
        if(iterations % 4 == 0 || iterations % 4 == 1){
            if(coordinates[iterations] > 1.0){
                std::cout << "Array index " << iterations + 1 << " is invalid" << std::endl;
                std::cout << "X and Y values cannot exceed 1.0" << std::endl;
                isValid = false;
            } else if(coordinates[iterations] < -1.0){
                std::cout << "Array index " << iterations + 1 << " is invalid" << std::endl;
                std::cout << "X and Y values cannot be less than -1.0" << std::endl;
                isValid = false;
            }
        } else if(iterations % 4 == 2){
            if(coordinates[iterations] > 1.0){
                std::cout << "Array index " << iterations + 1 << " is invalid" << std::endl;
                std::cout << "Z values cannot exceed 1.0" << std::endl;
                isValid = false;
            } else if(coordinates[iterations] < 0.0){
                std::cout << "Array index " << iterations + 1 << " is invalid" << std::endl;
                std::cout << "Z values cannot be less then 0.0" << std::endl;
                isValid = false;
            }
        }
    }
    
    return isValid;
}

/* bool proofRGBA(uint8_t* colors, int colorsSize){
    bool isValid = true;
    for(int iterations = 0; iterations < colorsSize / sizeof(uint8_t); iterations++){
        if(colors[iterations] > 255){
            std::cout << "Array index " << iterations + 1 << " is invlaid" << std::endl;
            std::cout << "RGBA values cannot exceed 255" << std::endl;
            isValid = false;
        } else if(colors[iterations] < 0){
            std::cout << "Array index " << iterations + 1 << " is invlaid" << std::endl;
            std::cout << "RGBA values cannot be less than 0" << std::endl;
            isValid = false;
        }
    }

    return isValid;
} */

bool unqliteInstance2(const char* fileName){
    unqlite* unqGL;
    unqlite_vm* unqGL_vm;
    int unqLog;

    char* keysXYZW[] = {
        "X1", "Y1", "Z1", "W1",
        "X3", "Y3", "Z2", "W2",
        "X3", "Y3", "Z3", "W3"
    };

    float valuesXYZW[] = {
        0.1f, 0.2f, 0.5f, 1.0f,
        0.4f, -0.6f, 0.5f, 1.0f,
        -0.5f, 0.9f, 0.5f, 1.0f
    };

    float valuesXYZW2[] = {
        1.2f, -2.2f, 0.5f, 1.0f,
        0.4f, -0.6f, 3.5f, 1.0f,
        -9.9f, 9.9f, 4.5f, 6.0f
    };

    char* keysRGBA[] = {
        "R1", "G1", "B1", "A1",
        "R2", "G2", "B2", "A2",
        "R3", "G3", "B3", "A3"
    };

    uint8_t valuesRGBA[] = {
        200, 150, 76, 255,
        98, 98, 187, 255,
        154, 35, 20, 255
    };

    uint8_t valuesRGBA2[] = {
        300, 200, -20, 0,
        0, 0, 0, 900,
        20, 20, 20, -1
    };

    unqLog = unqlite_open(&unqGL, fileName, UNQLITE_OPEN_CREATE);
    if(unqLog != UNQLITE_OK){
        std::cerr << "Unqlite failed to open " << fileName << std::endl;
        return false;
    }

    std::cout << sizeof(float) << std::endl;
    for(int iterations = 0; iterations < sizeof(valuesXYZW) / sizeof(float); iterations++){
        unqLog = unqlite_kv_store(unqGL, keysXYZW[iterations], sizeof(keysXYZW[iterations]), valuesXYZW, sizeof(valuesXYZW));
        std::cout << "Key value " << keysXYZW[iterations] << " has been assigned " << valuesXYZW[iterations] << std::endl;
    }
    
    std::cout << sizeof(uint8_t) << std::endl;
    for(int iterations = 0; iterations < sizeof(valuesRGBA) / sizeof(uint8_t); iterations++){
        unqLog = unqlite_kv_store(unqGL, keysRGBA[iterations], sizeof(keysRGBA[iterations]), valuesRGBA, sizeof(valuesRGBA));
        std::cout << "Key value " << keysRGBA[iterations] << " has been assigned " << unsigned(valuesRGBA[iterations]) << std::endl;
    }

    proofXYZW(valuesXYZW2, sizeof(valuesXYZW2));
    return true;
}

bool unqliteInstance3(const float VALUES[][4], int SIZE){
    char* X = "X";
    char* Y = "Y";
    char* Z = "Z";
    char* W = "W";
    bool isOk = true;
    std::string fullKey, oneKey, twoKey;

    unqlite* unqGL;
    unqlite_vm* unqVM;

    float currentFloat;
    int unqLog;
    int members = SIZE / sizeof(float);
    int membersWrap = 1;

    unqLog = unqlite_open(&unqGL, "unqGL.db", UNQLITE_OPEN_CREATE);
    if(unqLog != UNQLITE_OK){
        std::cout << "Database fails to open idiot" << std::endl;
    }

    for(int iterations = 0; iterations < members; iterations++){
        twoKey = std::to_string(membersWrap);
        if(iterations % 4 == 0){
            oneKey = X;
            currentFloat = VALUES[membersWrap - 1][0];
            if(currentFloat > 1.0 || currentFloat < -1.0){
                std::cout << oneKey << " value at index " << iterations <<  " ( " << membersWrap << " , 0) must lie between "
                          << "-1.0 and 1.0" << std::endl;
                isOk = false;
            }
        } else if(iterations % 4 == 1){
            oneKey = Y;
            currentFloat = VALUES[membersWrap - 1][1];
            if(currentFloat > 1.0 || currentFloat < -1.0){
                std::cout << oneKey << " value at index " << iterations <<  " ( " << membersWrap << " , 0) must lie between "
                          << "-1.0 and 1.0" << std::endl;
                isOk = false;
            }
        } else if(iterations % 4 == 2){
            oneKey = Z;
            currentFloat = VALUES[membersWrap - 1][2];
            if(currentFloat > 1.0 || currentFloat < 0.0){
                std::cout << oneKey << " value at index " << iterations <<  " ( " << membersWrap << " , 0) must lie between "
                          << "0.0 and 1.0" << std::endl;
                isOk = false;
            }
        } else if(iterations % 4 == 3){
            oneKey = W;
            currentFloat = VALUES[membersWrap - 1][3];
            membersWrap++;
        }

        fullKey = oneKey + twoKey;
        unqlite_kv_store(unqGL, &fullKey, sizeof(fullKey), &currentFloat, sizeof(currentFloat));
        std::cout << fullKey << " : " << currentFloat << std::endl;;
    }

    return isOk;
}

bool unqliteXYZW(unqlite* dbInstance, const float VALUES[][4], int SIZE){
    char* X = "X";
    char* Y = "Y";
    char* Z = "Z";
    char* W = "W";
    bool isOk = true;
    std::string fullKey, oneKey, twoKey;

    float currentFloat;
    int members = SIZE / sizeof(float);
    int membersWrap = 1;
    int unqSubLog;

    for(int iterations = 0; iterations < members; iterations++){
        twoKey = std::to_string(membersWrap);
        if(iterations % 4 == 0){
            oneKey = X;
            currentFloat = VALUES[membersWrap][0];
            if(currentFloat > 1.0 || currentFloat < -1.0){
                std::cout << oneKey << " value at index " << iterations <<  " ( " << membersWrap << " , 0) must lie between "
                          << "-1.0 and 1.0" << std::endl;
                isOk = false;
            }
        } else if(iterations % 4 == 1){
            oneKey = Y;
            currentFloat = VALUES[membersWrap][1];
            if(currentFloat > 1.0 || currentFloat < -1.0){
                std::cout << oneKey << " value at index " << iterations <<  " ( " << membersWrap << " , 0) must lie between "
                          << "-1.0 and 1.0" << std::endl;
                isOk = false;
            }
        } else if(iterations % 4 == 2){
            oneKey = Z;
            currentFloat = VALUES[membersWrap][2];
            if(currentFloat > 1.0 || currentFloat < 0.0){
                std::cout << oneKey << " value at index " << iterations <<  " ( " << membersWrap << " , 0) must lie between "
                          << "0.0 and 1.0" << std::endl;
                isOk = false;
            }
        } else if(iterations % 4 == 3){
            oneKey = W;
            currentFloat = VALUES[membersWrap][3];
            membersWrap++;
        }

        fullKey = oneKey + twoKey;
        unqSubLog = unqlite_kv_store(dbInstance, &fullKey, sizeof(fullKey), &currentFloat, sizeof(currentFloat));
        if(unqSubLog == UNQLITE_OK){
            std::cout << fullKey << " : " << currentFloat << std::endl;;
        } else {
            std::cout << fullKey << " : " << currentFloat << " failed to syncronize" << std::endl;;
        }
    }

    return isOk;
}

bool unqliteConfig(const char* dbName, const float VALS[][4], int VALS_SIZE){
    unqlite* unqGL;
    int unqLog;
    bool funcReturn;
    bool runCorrect = true;
    bool runCorrectBUFF;
    unqlite_int64* runCorrectBUFFSIZE = new int64_t(1);

    unqLog = unqlite_open(&unqGL, dbName, UNQLITE_OPEN_READWRITE);

    if(unqLog != UNQLITE_OK){
        std::cout << "Unqlite instance " << dbName << " has been created" << std::endl;
        funcReturn = unqliteXYZW(unqGL, VALS, VALS_SIZE);
        if(funcReturn == false){
            std::cout << "XYZW floats failed to process, please delete " << dbName << " and any associated files" << std::endl;
            runCorrect = false;
        }
        unqlite_kv_store(unqGL, "runCorrect", sizeof(runCorrect), &runCorrect, sizeof(runCorrect));
    } else {
        unqlite_kv_fetch(unqGL, "runCorrect", sizeof(runCorrect), &runCorrectBUFF, runCorrectBUFFSIZE);
        if(runCorrectBUFF == false){
            std::cout << "Database configuration failed previously, please delete " << dbName << " and any associated files" << std::endl;
        } else {
            std::cout << "UNQLITE SUCCESS!!!" << std::endl;
            unqlite_close(unqGL);
        }
    }     
    
    delete runCorrectBUFFSIZE;
    return runCorrect;
}

bool unqliteConfig2(const char* dbName, const float VALS[][4], int VALS_SIZE){
    unqlite* unqGL;
    int unqLog;
    bool funcReturn;
    bool runCorrect = true;
    bool runCorrectBUFF;
    std::unique_ptr<unqlite_int64> runCorrectBUFFSIZE(new std::int64_t(1));

    unqLog = unqlite_open(&unqGL, dbName, UNQLITE_OPEN_READWRITE);

    if(unqLog != UNQLITE_OK){
        std::cout << "Unqlite instance " << dbName << " has been created" << std::endl;
        funcReturn = unqliteXYZW(unqGL, VALS, VALS_SIZE);
        if(funcReturn == false){
            std::cout << "XYZW floats failed to process, please delete " << dbName << " and any associated files" << std::endl;
            runCorrect = false;
        }
        unqlite_kv_store(unqGL, "runCorrect", sizeof(runCorrect), &runCorrect, sizeof(runCorrect));
    } else if(unqLog == UNQLITE_OK) {
        unqlite_kv_fetch(unqGL, "runCorrect", sizeof(runCorrect), &runCorrectBUFF, runCorrectBUFFSIZE.get());
        if(runCorrectBUFF == false){
            std::cout << "Database configuration failed previously, please delete " << dbName << " and any associated files" << std::endl;
        } else {
            std::cout << "UNQLITE SUCCESS!!!" << std::endl;
            unqlite_close(unqGL);
        }
    } else {
        std::cout << "Program failed to execute" << std::endl;
        runCorrect = false;
    }

    return runCorrect;
} 

/* bool unqliteConfig3(const char* dbName){
    unqlite* unqGL;
    int unqLog;
    bool runCorrect = true;

    unqLog = unqlite_open(&unqGL, dbName, UNQLITE_OPEN_READWRITE);

} */

int main(int argc, char** argv){
    // unqliteInstance2("unqGL.db");
    // unqliteInstance3(XYZW, sizeof(XYZW));
    std::cout << "\n \n" << std::endl;
    unqliteConfig2("unqInstanceGL.db", XYZW, sizeof(XYZW));
    Sleep(50000);
    return 0;
}
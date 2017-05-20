#include <iostream>
#include <cstdint>
#include <string>
#include <istream>

//extern "C" {
//    #include <CppSQLite3.h>
// }

#include <sqlite3.h>

/* sqlite3* sqliteInit(const char* fileName){
    sqlite3* sqliteGL;
    int runLog = sqlite3_open(fileName, &sqliteGL);
    if(runLog != SQLITE_OK){
        std::cout << "Database connection to " << fileName << "failed to open" << std::endl;
        return runLog;
    }
    return sqliteGL;
}

void interpretMe(char** ARGV){
    std::cin >> ARGV;
    if(ARGV[0] == "X" || ARGV[0] == "Y" || ARGV[0] == "Z" || ARGV[0] == "W"){
        std::cout << "Assign a coordinate value..." << std::endl;
    } else if("R" || ARGV[0] == "G" || ARGV[0] == "B" || ARGV[0] == "A"){
        std::cout << "Assign a color value..." << std::endl;
    }
}

int main(int argc, char** argv){
    sqlite3* sqliteGL;
    int runLog = sqlite3_open("SQL-GL", &sqliteGL);
    if(runLog != SQLITE_OK){
        std::cout << "Database connection to " << fileName << "failed to open" << std::endl;
        return runLog;
    }

    while(true){
        std::cin >> argv;
        if(ARGV[0] == "X" || ARGV[0] == "Y" || ARGV[0] == "Z" || ARGV[0] == "W"){
            std::cout << "Assign a coordinate value..." << std::endl;
        } else if("R" || ARGV[0] == "G" || ARGV[0] == "B" || ARGV[0] == "A"){
            std::cout << "Assign a color value..." << std::endl;
        }
    }
    sqlite3_close(sqliteGL);
    return 0;
} */

void queryData1(){
    std::string queryAO;
    std::string followID;
    std::string::size_type followIDsize;
    float coordFloat;
    unsigned int minusSpace, colorInt; // because the std::string has no method to convert to uint8_t
    uint8_t colorByte;
    while (true) {
        std::cin >> queryAO;
        // std::cout << queryAO << std::endl;
        // std::cout << queryAO[0] << std::endl;
        if(queryAO == "exit"){ break; }
        else if(queryAO[0] == 'X' || queryAO[0] == 'Y' || queryAO[0] == 'Z' || queryAO[0] == 'W'){
            followID = queryAO.substr(1, sizeof(queryAO) - 1);
            std::cout << "Accessing attribute " << queryAO[0] << " for dot " << followID << std::endl;
            // followFloat = std::stof(followID, &followIDsize);
        } else if(queryAO[0] == 'R' || queryAO[0] == 'G' || queryAO[0] == 'B' || queryAO[0] == 'A'){
            followID = queryAO.substr(1, sizeof(queryAO) - 1);
            std::cout << "Accessing attribute " << queryAO[0] << " for dot " << followID << std::endl;
        } else if(queryAO.substr(0, 3) == "GEN"){
            // Generate a specified quantity of dots
        } else if(queryAO.substr(0, 3) == "DEL"){
            // Delete a specified quantity of dots between two index values
        } else if(queryAO.substr(0, 3) == "SEE"){
            // Display all values stored in the database
        } else {
            std::cout << "Type something legible" << std::endl;
        }
    }
}

void queryData2(){
    std::string queryAO;
    char ModeSpecific;
    std::string followID;
    std::string::size_type SZ;
    bool oneString = true;
    float coordFloat;
    unsigned long int minusSpace, colorInt; // because the std::string has no method to convert to uint8_t
    uint8_t MODE, colorByte;
    while (true) {
        std::cin >> queryAO;
        if(queryAO == "exit"){
            std::cout << "Bye bye" << std::endl;
            return;
        } else if(queryAO == "help"){
            std::cout << "Help is on the way!" << std::endl;
        } else if(oneString){
            // std::cout << queryAO << std::endl;
            // std::cout << queryAO[0] << std::endl;
            if(queryAO[0] == 'X' || queryAO[0] == 'Y' || queryAO[0] == 'Z' || queryAO[0] == 'W'){
                ModeSpecific = queryAO[0];
                followID = queryAO.substr(1, sizeof(queryAO) - 1);
                std::cout << "Accessing attribute " << queryAO[0] << " for dot " << followID << std::endl;
                MODE = 1;
            } else if(queryAO[0] == 'R' || queryAO[0] == 'G' || queryAO[0] == 'B' || queryAO[0] == 'A'){
                ModeSpecific = queryAO[0];
                followID = queryAO.substr(1, sizeof(queryAO) - 1);
                std::cout << "Accessing attribute " << queryAO[0] << " for dot " << followID << std::endl;
                MODE = 2;
            } else {
                std::cout << "Type something legible" << std::endl;
                MODE = 0;
                continue;
            }
            //std::cout << "oneString is false now" << std::endl;
            oneString = false;
        } else if(! oneString){
            oneString = true;
            if(MODE == 1){
                coordFloat = std::stof(queryAO, &SZ);
                if(coordFloat > 1.0f || coordFloat < -1.0f && ModeSpecific == 'X'){
                    std::cout << coordFloat << " must lie between -1.0 and 1.0" << std::endl;
                } else if(coordFloat < -1.0f || coordFloat > 1.0f && ModeSpecific == 'Y'){
                    std::cout << coordFloat << "must lie between -1.0 and 1.0" << std::endl;
                } else if(coordFloat < 0 || coordFloat > 1.0f && ModeSpecific == 'Z'){
                    std::cout << coordFloat << "must lie between 0 and 1.0" << std::endl;
                }
                std::cout << coordFloat << " has been assigned to " << ModeSpecific << followID << std::endl;
                std::cout << "current mode is " << int(MODE) << std::endl;
            } else if(MODE == 2){
                colorInt = std::stoul(queryAO, &SZ);
                std::cout << colorInt << " has been assigned to " << ModeSpecific << followID << std::endl;
                std::cout << "current mode is " << int(MODE) << std::endl;
            } else { // MODE will be zero, or something went wrong
                std::cout << "You will start over so god help me" << std::endl;
                continue;
            }
        }
    }
}

void queryData3(){
    char ModeSpecific;
    std::string queryAO, followID, genCommand;
    std::string::size_type SZ;
    bool oneString = true;
    bool genCall = false;
    float coordFloat;
    unsigned long int colorInt, genNum; // because the std::string has no method to convert to uint8_t
    uint8_t MODE, colorByte;
    while (true) {
        std::cout << " >> ";
        std::cin >> queryAO;
        if(queryAO == "exit"){
            std::cout << "Bye bye" << std::endl;
            return;
        } else if(queryAO == "help"){
            std::cout << "Help is on the way!" << std::endl;
        } else if(oneString && queryAO.length() == 1){
            std::cout << "Argument " << queryAO << " contains only one letter" << std::endl;
        } else if(genCall){
            genNum = std::stoul(queryAO, &SZ);
            if(genCommand == "AutoGenVert"){
                std::cout << genNum << " Coordinate values have been generated using defalut template: " << std::endl;
                std::cout << "\t X: 0.0 \t Y: 0.0 \t Z: 0.5 \t W: 1.0" << std::endl;
            } else if(genCommand == "RandGenVert"){
                std::cout << genNum << " Coordinate values have been generated using randomizer" << std::endl;
            } else if(genCommand == "AutoGenFrag"){
                std::cout << genNum << " Color values have been generated using defalut template: " << std::endl;
                std::cout << "\t R: 0 \t G: 0 \t B: 0 \t A: 255" << std::endl;
            } else if(genCommand == "RandGenFrag"){
                std::cout << genNum << " Color values have been generated using randomizer" << std::endl;
            }
            genCall = false;
        } else if(queryAO == "AutoGenVert" || queryAO == "RandGenVert" ||
                  queryAO == "AutoGenFrag" || queryAO == "RandGenFrag"){
            genCommand = queryAO;
            genCall = true;
        } else if(oneString){
            // std::cout << queryAO << std::endl;
            // std::cout << queryAO[0] << std::endl;
            if(queryAO[0] == 'X' || queryAO[0] == 'Y' || queryAO[0] == 'Z' || queryAO[0] == 'W'){
                ModeSpecific = queryAO[0];
                followID = queryAO.substr(1, sizeof(queryAO) - 1);
                std::cout << "Accessing attribute " << queryAO[0] << " for dot " << followID << std::endl;
                MODE = 1;
            } else if(queryAO[0] == 'R' || queryAO[0] == 'G' || queryAO[0] == 'B' || queryAO[0] == 'A'){
                ModeSpecific = queryAO[0];
                followID = queryAO.substr(1, sizeof(queryAO) - 1);
                std::cout << "Accessing attribute " << queryAO[0] << " for dot " << followID << std::endl;
                MODE = 2;
            } else {
                std::cout << "Type something legible" << std::endl;
                MODE = 0;
                continue;
            }
            //std::cout << "oneString is false now" << std::endl;
            oneString = false;
        } else if(! oneString){
            oneString = true;
            if(MODE == 1){
                coordFloat = std::stof(queryAO, &SZ);
                if(coordFloat > 1.0f || coordFloat < -1.0f && ModeSpecific == 'X'){
                    std::cout << coordFloat << " must lie between -1.0 and 1.0" << std::endl;
                } else if(coordFloat < -1.0f || coordFloat > 1.0f && ModeSpecific == 'Y'){
                    std::cout << coordFloat << "must lie between -1.0 and 1.0" << std::endl;
                } else if(coordFloat < 0 || coordFloat > 1.0f && ModeSpecific == 'Z'){
                    std::cout << coordFloat << "must lie between 0 and 1.0" << std::endl;
                }
                std::cout << coordFloat << " has been assigned to " << ModeSpecific << followID << std::endl;
                std::cout << "current mode is " << int(MODE) << std::endl;
            } else if(MODE == 2){
                colorInt = std::stoul(queryAO, &SZ);
                std::cout << colorInt << " has been assigned to " << ModeSpecific << followID << std::endl;
                std::cout << "current mode is " << int(MODE) << std::endl;
            } else { // MODE will be zero, or something went wrong
                std::cout << "You will start over so god help me" << std::endl;
                continue;
            }
        }
    }
}

std::string useDB(uint8_t mode, const char* dbName, std::string currentDbName){
    uint8_t modeVert = 1;
    uint8_t modeFrag = 2;
    std::string modeStr;
    std::string returnStr = dbName;

    if(dbName == currentDbName){
        std::cout << "You are already using collection named " << dbName << " for " << modeStr << " values" << std::endl;
    } else {
        if(mode == modeVert){
            // std::cout << "Now using Vertex collection named " << dbName << std::endl;
            modeStr = "Vertex";
            sqlite3* dbInstanceVert;
            sqlite3_open(dbName, &dbInstanceVert);
        } else if(mode == modeFrag){
            // std::cout << "Now using Fragment collection named " << dbName << std::endl;
            modeStr = "Fragment";
            sqlite3* dbInstanceFrag;
            sqlite3_open(dbName, &dbInstanceFrag);
        }
        std::cout << "Now using " << modeStr << " collection named " << dbName << std::endl;
        // return const_cast<std::string>(dbName);
        return std::string(dbName);
    }
}

/* void queryData4(){
    char ModeSpecific;
    bool oneString = true;
    bool genCall, switchCall = false;
    bool useAutoGen = true;
    float coordFloat;
    unsigned long int colorInt, genNum; // because the std::string has no method to convert to uint8_t
    unsigned long int DBxyzw, DBrgba = 1;
    uint8_t MODE, colorByte;
    
    std::string queryAO, followID, genCommand;
    std::string::size_type SZ;
    char* defaultNameVert = "AOv";
    char* defaultNameFrag = "AOf";
    // char* queryAOchar = new char[queryAO.length() + 1];
    const char* queryAOchar = queryAO.c_str();
    std::string vertExtension = ".vert";
    std::string fragExtension = ".frag";

    useDB(1, defaultNameVert, "abcd");
    useDB(2, defaultNameFrag, "abcd");

    while (true) {
        std::cout << " > ";
        std::cin >> queryAO;
        if(queryAO == "exit"){
            std::cout << "Bye bye" << std::endl;
            return;
        } else if(queryAO == "help"){
            std::cout << "Help is on the way!" << std::endl;
        } else if(oneString && queryAO.length() == 1){
            std::cout << "Argument " << queryAO << " contains only one letter" << std::endl;
        } else if(genCall){
            genNum = std::stoul(queryAO, &SZ);
            if(genCommand == "AutoGenVert"){
                std::cout << genNum << " Coordinate values have been generated using defalut template: " << std::endl;
                // std::cout << "\t X: 0.0 \t Y: 0.0 \t Z: 0.5 \t W: 1.0" << std::endl;
                std::cout << "\t" << "X: 0.0" << "\t" << "Y: 0.0" << "\t" << "Z: 0.5" << "\t" << "W: 1.0" << std::endl;
                DBxyzw += genNum;
                std::cout << DBxyzw << " entries exist in the XYZW (Coordinate) database" << std::endl;
            } else if(genCommand == "RandGenVert"){
                std::cout << genNum << " Coordinate values have been generated using randomizer" << std::endl;
                DBxyzw += genNum;
                std::cout << DBxyzw << " entries exist in the XYZW (Coordinate) database" << std::endl;
                useAutoGen = false;
            } else if(genCommand == "AutoGenFrag"){
                std::cout << genNum << " Color values have been generated using defalut template: " << std::endl;
                // std::cout << "\t R: 0.0 \t G: 0 \t B: 0 \t A: 255" << std::endl;
                std::cout << "\t" << "R: 0" << "\t" << "G: 0" << "\t" << "B: 0" << "\t" << "A: 255" << std::endl;
                DBrgba += genNum;
                std::cout << DBrgba << " entries exist in the RGBA (Colors) database" << std::endl;
            } else if(genCommand == "RandGenFrag"){
                std::cout << genNum << " Color values have been generated using randomizer" << std::endl;
                DBrgba += genNum;
                std::cout << DBrgba << " entries exist in the RGBA (Colors) database" << std::endl;
                useAutoGen = false;
            }
            genCall = false;
        } else if(queryAO == "AutoGenVert" || queryAO == "RandGenVert" ||
                  queryAO == "AutoGenFrag" || queryAO == "RandGenFrag"){
            genCommand = queryAO;
            genCall = true;
        } else if(switchCall){
            // std::strcpy(queryAOchar, queryAO.c_str());
            if(MODE == 1){
                defaultNameVert = useDB(MODE, queryAOchar, defaultNameVert);
            } else if(queryAO == "SwitchFrag"){
                defaultNameFrag = useDB(MODE, queryAOchar, defaultNameVert);
            }
            switchCall = false;
        } else if(queryAO == "SwitchVert" || queryAO == "SwitchFrag"){
            if(queryAO == "SwitchVert"){
                MODE = 1;
            } else if(queryAO == "SwitchFrag"){
                MODE = 2;
            }
            switchCall = true;
        } else if(oneString){
            // std::cout << queryAO << std::endl;
            // std::cout << queryAO[0] << std::endl;
            if(queryAO[0] == 'X' || queryAO[0] == 'Y' || queryAO[0] == 'Z' || queryAO[0] == 'W'){
                ModeSpecific = queryAO[0];
                followID = queryAO.substr(1, sizeof(queryAO) - 1);
                std::cout << "Accessing attribute " << queryAO[0] << " for entry " << followID << std::endl;
                MODE = 1;
            } else if(queryAO[0] == 'R' || queryAO[0] == 'G' || queryAO[0] == 'B' || queryAO[0] == 'A'){
                ModeSpecific = queryAO[0];
                followID = queryAO.substr(1, sizeof(queryAO) - 1);
                std::cout << "Accessing attribute " << queryAO[0] << " for entryr " << followID << std::endl;
                MODE = 2;
            } else {
                std::cout << "Type something legible" << std::endl;
                MODE = 0;
                continue;
            }
            //std::cout << "oneString is false now" << std::endl;
            oneString = false;
        } else if(! oneString){
            oneString = true;
            if(MODE == 1){
                coordFloat = std::stof(queryAO, &SZ);
                if(coordFloat > 1.0f || coordFloat < -1.0f && ModeSpecific == 'X'){
                    std::cout << coordFloat << " must lie between -1.0 and 1.0" << std::endl;
                } else if(coordFloat < -1.0f || coordFloat > 1.0f && ModeSpecific == 'Y'){
                    std::cout << coordFloat << "must lie between -1.0 and 1.0" << std::endl;
                } else if(coordFloat < 0 || coordFloat > 1.0f && ModeSpecific == 'Z'){
                    std::cout << coordFloat << "must lie between 0 and 1.0" << std::endl;
                }
                std::cout << coordFloat << " has been assigned to " << ModeSpecific << followID << std::endl;
                std::cout << "current mode is " << int(MODE) << std::endl;
            } else if(MODE == 2){
                colorInt = std::stoul(queryAO, &SZ);
                colorByte = uint8_t(colorInt);
                // std::cout << colorInt << " has been assigned to " << ModeSpecific << followID << std::endl;
                std::cout << int(colorByte) << " has been assigned to " << ModeSpecific << followID << std::endl;
                std::cout << "current mode is " << int(MODE) << std::endl;
            } else { // MODE will be zero, or something went wrong
                std::cout << "You will start over so god help me" << std::endl;
                continue;
            }
        }
    }
} */

void queryData5(const char* VertNameDB, const char* FragNameDB){
    sqlite3* VertDB;
    sqlite3* FragDB;
    
    sqlite3_open(VertNameDB, &VertDB);
    sqlite3_open(FragNameDB, &FragDB);

    // sqlite3_open_v2(VertNameDB, &VertDB, SQLITE_OPEN_CREATE);
    // sqlite3_open_v2(FragNameDB, &FragDB, SQLITE_OPEN_CREATE);

    char ModeSpecific;
    bool oneString = true;
	bool genCall = false;
	bool tagCall = false;
    bool useAutoGen = true;
    float coordFloat;
    unsigned long int colorInt, genNum, followID_int; // because the std::string has no method to convert to uint8_t
    unsigned long int DBxyzw = 1;
    unsigned long int DBrgba = 1;
    uint8_t MODE, colorByte;
    
    std::string queryAO, followID, genCommand, tagCommand, tagIndex, ModeSpecificStr;
    std::string::size_type SZ;
    std::string allTagName = "Full";
    std::string vertExtension = ".vert";
    std::string fragExtension = ".frag";

    while (true) {
        std::cout << " > ";
        std::cin >> queryAO;
        if(queryAO == "exit"){
            sqlite3_close(VertDB);
            sqlite3_close(FragDB);
            std::cout << "Bye bye" << std::endl;
            return;
        } else if(queryAO == "help"){
            std::cout << "Help is on the way!" << std::endl;
        } else if(oneString && queryAO.length() == 1){
            std::cout << "Argument " << queryAO << " contains only one letter" << std::endl;
        } else if(genCall){
            genNum = std::stoul(queryAO, &SZ);
            if(genCommand == "AutoGenVert"){
                std::cout << genNum << " Coordinate values have been generated using defalut template: " << std::endl;
                // std::cout << "\t X: 0.0 \t Y: 0.0 \t Z: 0.5 \t W: 1.0" << std::endl;
                std::cout << "\t" << "X: 0.0" << "\t" << "Y: 0.0" << "\t" << "Z: 0.5" << "\t" << "W: 1.0" << std::endl;
                DBxyzw += genNum;
                std::cout << DBxyzw << " entries exist in the XYZW (Coordinate) database" << std::endl;
            } else if(genCommand == "RandGenVert"){
                std::cout << genNum << " Coordinate values have been generated using randomizer" << std::endl;
                DBxyzw += genNum;
                std::cout << DBxyzw << " entries exist in the XYZW (Coordinate) database" << std::endl;
                useAutoGen = false;
            } else if(genCommand == "AutoGenFrag"){
                std::cout << genNum << " Color values have been generated using defalut template: " << std::endl;
                // std::cout << "\t R: 0.0 \t G: 0 \t B: 0 \t A: 255" << std::endl;
                std::cout << "\t" << "R: 0" << "\t" << "G: 0" << "\t" << "B: 0" << "\t" << "A: 255" << std::endl;
                DBrgba += genNum;
                std::cout << DBrgba << " entries exist in the RGBA (Colors) database" << std::endl;
            } else if(genCommand == "RandGenFrag"){
                std::cout << genNum << " Color values have been generated using randomizer" << std::endl;
                DBrgba += genNum;
                std::cout << DBrgba << " entries exist in the RGBA (Colors) database" << std::endl;
                useAutoGen = false;
            }
            genCall = false;
        } else if(queryAO == "AutoGenVert" || queryAO == "RandGenVert" ||
                  queryAO == "AutoGenFrag" || queryAO == "RandGenFrag"){
            genCommand = queryAO;
            genCall = true;
        } else if(queryAO.substr(0, 7) == "TagVert" || queryAO.substr(0, 7) == "TagFrag"){
            if(queryAO.substr(0, 7) == "TagVert"){
                MODE = 1;
                ModeSpecificStr = "XYZW";
            } else if(queryAO.substr(0, 7) == "TagFrag"){
                MODE = 2;
                ModeSpecificStr = "RGBA";
            }
            tagCommand = queryAO.substr(0, 7);
            tagIndex = queryAO.substr(7, queryAO.length() - 1);
            std::cout << "Tag command in use is " << tagCommand << std::endl;
            tagCall = true;
        } else if(tagCall){
            if(queryAO.length() > 12){
                std::cout << "Make sure your tags are only 12 characers in length" << std::endl;
                tagCall = false;
                continue;
            }
            std::cout << queryAO << " tag has been added to " << ModeSpecificStr << " index number " << tagIndex << std::endl;
            tagCall = false;
        }
        else if(oneString){
            ModeSpecific = queryAO[0];
            if(ModeSpecific == 'X' || ModeSpecific == 'Y' || ModeSpecific == 'Z' || ModeSpecific == 'W'){
                followID = queryAO.substr(1, sizeof(queryAO) - 1);
                followID_int = std::stoi(followID);
                if(followID_int > DBxyzw){
                    std::cout << "Entry " << followID_int << " does not exist, maximum allowed is " << DBxyzw << std::endl;
                    std::cout << "Use AutoGenVert or RandGenVert to create XYZW entries" << std::endl;
                    continue;
                }
                MODE = 1;
            } else if(ModeSpecific == 'R' || ModeSpecific == 'G' || ModeSpecific == 'B' || ModeSpecific == 'A'){
                followID = queryAO.substr(1, sizeof(queryAO) - 1);
                followID_int = std::stoi(followID);
                if(followID_int > DBrgba){
                    std::cout << "Entry " << followID_int << " does not exist, maximum allowed is " << DBrgba << std::endl;
                    std::cout << "Use AutoGenFrag or RandGenFrag to create XYZW entries" << std::endl;
                    continue;
                }
                MODE = 2;
            } else {
                // std::cout << "Type something legible" << std::endl;
                std::cout << "Input \"" << queryAO << "\" skipped..." << std::endl;
                MODE = 0;
                continue;
            }
            std::cout << "Accessing attribute " << ModeSpecific << " for entry " << followID_int << std::endl;
            oneString = false;
        } else if(! oneString){
            oneString = true;
            if(MODE == 1){
                coordFloat = std::stof(queryAO, &SZ);
                if(coordFloat > 1.0f || coordFloat < -1.0f && ModeSpecific == 'X'){
                    std::cout << coordFloat << " must lie between -1.0 and 1.0" << std::endl;
                    continue;
                } else if(coordFloat > 1.0f || coordFloat < -1.0f && ModeSpecific == 'Y'){
                    std::cout << coordFloat << " must lie between -1.0 and 1.0" << std::endl;
                    continue;
                } else if(coordFloat < 0 || coordFloat > 1.0f && ModeSpecific == 'Z'){
                    std::cout << coordFloat << " must lie between 0 and 1.0" << std::endl;
                    continue;
                }
                std::cout << coordFloat << " has been assigned to " << ModeSpecific << followID << std::endl;
                std::cout << "current mode is " << int(MODE) << std::endl;
            } else if(MODE == 2){
                colorInt = std::stoul(queryAO, &SZ);
                colorByte = uint8_t(colorInt);
                // std::cout << colorInt << " has been assigned to " << ModeSpecific << followID << std::endl;
                std::cout << int(colorByte) << " has been assigned to " << ModeSpecific << followID << std::endl;
                std::cout << "current mode is " << int(MODE) << std::endl;
            } else { // MODE will be zero, or something went wrong
                std::cerr << "Something went wrong" << std::endl;
                continue;
            }
        }
    }
}

int main(int argc, char** argv){
    queryData5("AO_XYZW", "AO_RGBA");
    return 0;
}


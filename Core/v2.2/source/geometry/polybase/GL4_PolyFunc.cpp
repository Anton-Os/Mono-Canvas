#include "geometry/polybase/GL4_PolyFunc.hpp"

static char error_xValsImmute[] = "X values are immutable";
static char error_yValsImmute[] = "Y values are immutable";
static char error_zValsImmute[] = "Z values are immutable";
static char error_xyzPresent[] = "X, Y, and Z values must be present to create()";

void GL4_PolyFunc::reset(){
    xVals.clear();
    yVals.clear();
    zVals.clear();
    xyzBits.reset();
    xSequence = nullptr;
    yEquation = nullptr;
    zEquation = nullptr;
}

void GL4_PolyFunc::gen_x(){
    if(xyzBits[Y] == true || xyzBits[Z] == true) logError(__FILE__, __LINE__, error_xValsImmute);

    xSequence(&xVals);
    xyzBits.set(X);
}

void GL4_PolyFunc::gen_y(){
    if(xyzBits[Z] == true) logError(__FILE__, __LINE__, error_yValsImmute);

    if(yVals.empty())
        yVals.resize(xVals.size());
    else
        yVals.resize(yVals.size() + xVals.size());

    unsigned xElem = 0;
    for(unsigned yElem = yVals.size() - xVals.size(); yElem < yVals.size(); yElem++){
        xElem++;
        yVals[yElem] = yEquation(xVals[xElem]);
    }

    xyzBits.set(Y);
}

void GL4_PolyFunc::gen_z(){
    if(zVals.empty())
        zVals.resize(yVals.size());
    else
        zVals.resize(zVals.size() + yVals.size());

    unsigned xElem = 0;
    unsigned yElem = 0;
    for(unsigned zElem = zVals.size() - yVals.size(); zElem < zVals.size(); zElem++){
        if(xElem == xVals.size()) xElem = 0;
        if(yElem == yVals.size()) yElem = 0;
        zVals[zElem] = zEquation(xVals[xElem], yVals[yElem]);
        xElem++; yElem++;
    }

    xyzBits.set(Z);
}

static unsigned genIndices1D(std::vector<unsigned>* indexAccum, unsigned xCount){
    unsigned idxCount = 0;
    for(unsigned indexElem = 0; indexElem < xCount - 1; indexElem++){
        indexAccum->push_back(indexElem);
        indexAccum->push_back(indexElem + 1);
        idxCount += 2;
    }
    return idxCount;
}

static unsigned genIndices2D(std::vector<unsigned>* indexAccum, unsigned xCount, unsigned yCount){
    unsigned idxCount = 0;
    std::array<unsigned, 4> indexSet;
    for(unsigned indexElem = 0; indexElem < yCount - xCount; indexElem++){
        if(indexElem % xCount == xCount - 1) continue;
        indexSet = {indexElem, indexElem + 1, indexElem + xCount, indexElem + xCount + 1};
        indexAccum->push_back(indexSet[0]);
        indexAccum->push_back(indexSet[1]);
        indexAccum->push_back(indexSet[2]);
        indexAccum->push_back(indexSet[3]);
        indexAccum->push_back(indexSet[2]);
        indexAccum->push_back(indexSet[1]);
        idxCount += 6;
    }
    return idxCount;
}

static unsigned genIndices3D(std::vector<unsigned>* indexAccum, unsigned xCount, unsigned yCount, unsigned zCount){
    unsigned idxCount = 0;
    unsigned ySetOfX = yCount / xCount;
    unsigned zSetOfY = zCount / yCount;
    std::array<unsigned, 4> indexSet;
    for(unsigned zIndex = 0; zIndex < zSetOfY; zIndex++){
        for(unsigned indexElem = zIndex * yCount; indexElem < zIndex * yCount + yCount - xCount; indexElem++){
            if(indexElem % xCount == xCount - 1) continue;
            indexSet = {indexElem, indexElem + 1, indexElem + xCount, indexElem + xCount + 1};
            indexAccum->push_back(indexSet[0]);
            indexAccum->push_back(indexSet[1]);
            indexAccum->push_back(indexSet[2]);
            indexAccum->push_back(indexSet[3]);
            indexAccum->push_back(indexSet[2]);
            indexAccum->push_back(indexSet[1]);
            idxCount += 6;
        }
    }

    unsigned indexOffset = 0;
    for(unsigned zIndex = 0; zIndex < zSetOfY - 1; zIndex++){
        indexOffset = zIndex * yCount;
        for(unsigned xIndex = 0; xIndex < xCount - 1; xIndex++){
            indexSet = {
                indexOffset + xIndex,
                indexOffset + xIndex + 1, 
                indexOffset + yCount + xIndex, 
                indexOffset + yCount + xIndex + 1
            };
            indexAccum->push_back(indexSet[0]);
            indexAccum->push_back(indexSet[1]);
            indexAccum->push_back(indexSet[2]);
            indexAccum->push_back(indexSet[3]);
            indexAccum->push_back(indexSet[2]);
            indexAccum->push_back(indexSet[1]);
            idxCount += 6;
            unsigned incFactor = yCount - xCount;
            indexSet = {
                indexOffset + xIndex + incFactor,
                indexOffset + xIndex + 1 + incFactor, 
                indexOffset + yCount + xIndex + incFactor,
                indexOffset + yCount + xIndex + 1  + incFactor
            };
            indexAccum->push_back(indexSet[0]);
            indexAccum->push_back(indexSet[1]);
            indexAccum->push_back(indexSet[2]);
            indexAccum->push_back(indexSet[3]);
            indexAccum->push_back(indexSet[2]);
            indexAccum->push_back(indexSet[1]);
            idxCount += 6;
        }
    }

    indexOffset = 0;
    for(unsigned zIndex = 0; zIndex < zSetOfY - 1; zIndex++){
        indexOffset = zIndex * yCount;
        for(unsigned yIndex = 0; yIndex < yCount - xCount; yIndex += xCount){
            indexSet = {
                indexOffset + yIndex,
                indexOffset + yIndex + xCount,
                indexOffset + yIndex + yCount,
                indexOffset + yIndex + yCount + xCount
            };
            indexAccum->push_back(indexSet[0]);
            indexAccum->push_back(indexSet[1]);
            indexAccum->push_back(indexSet[2]);
            indexAccum->push_back(indexSet[3]);
            indexAccum->push_back(indexSet[2]);
            indexAccum->push_back(indexSet[1]);
            idxCount += 6;
            unsigned incFactor = xCount - 1;
            indexSet = {
                indexOffset + yIndex + incFactor,
                indexOffset + yIndex + xCount + incFactor,
                indexOffset + yIndex + yCount + incFactor,
                indexOffset + yIndex + yCount + xCount + incFactor
            };
            indexAccum->push_back(indexSet[0]);
            indexAccum->push_back(indexSet[1]);
            indexAccum->push_back(indexSet[2]);
            indexAccum->push_back(indexSet[3]);
            indexAccum->push_back(indexSet[2]);
            indexAccum->push_back(indexSet[1]);
            idxCount += 6;
        }
    }

    return idxCount;
}

void GL4_PolyFunc::create(GL4_Mesh* mesh, GL4_Vertex_Factory* factory){
    if(!xyzBits.all()) logError(__FILE__, __LINE__, error_xyzPresent);

    std::vector<GLfloat> threePts(zVals.size() * 3);
    for(GLuint vecElem = 0; vecElem < zVals.size(); vecElem++){
        threePts[vecElem * 3] = xVals[vecElem % xVals.size()];
        threePts[vecElem * 3 + 1] = yVals[vecElem % yVals.size()];
        threePts[vecElem * 3 + 2] = zVals[vecElem];
    }

    std::vector<unsigned> indices;

    unsigned ySetOfX = yVals.size() / xVals.size();
    unsigned zSetOfY = zVals.size() / yVals.size();
    unsigned zSetOfX = zVals.size() / xVals.size();

    if(zSetOfX == 1) mesh->order.indexCount = genIndices1D(&indices, xVals.size());
    else if(ySetOfX > 1 && zSetOfY == 1) mesh->order.indexCount = genIndices2D(&indices, GL4_PolyFunc::xVals.size(), GL4_PolyFunc::yVals.size());
    // else if(ySetOfX == 1 && zSetOfY > 1) genIndices2(&indices, GL4_PolyFunc::xVals.size(), GL4_PolyFunc::yVals.size(), GL4_PolyFunc::zVals.size());
    else if(ySetOfX > 1 && zSetOfY > 1) mesh->order.indexCount = genIndices3D(&indices, GL4_PolyFunc::xVals.size(), GL4_PolyFunc::yVals.size(), GL4_PolyFunc::zVals.size());
    else std::cerr << "Something went wrong while indexing Grid" << std::endl;

    mesh->add_feed(factory->get_format(_GL4_Vertex_Feed::pos_3f));
    mesh->run_feed(0, threePts.data(), sizeof(float));
}

void GL4_PolyFunc::create(){
    if(!xyzBits.all()) logError(__FILE__, __LINE__, error_xyzPresent);

    vertices.resize(zVals.size() * 3);
    for(GLuint vecElem = 0; vecElem < zVals.size(); vecElem++){
        vertices[vecElem * 3] = xVals[vecElem % xVals.size()];
        vertices[vecElem * 3 + 1] = yVals[vecElem % yVals.size()];
        vertices[vecElem * 3 + 2] = zVals[vecElem];
    }

    unsigned ySetOfX = yVals.size() / xVals.size();
    unsigned zSetOfY = zVals.size() / yVals.size();
    unsigned zSetOfX = zVals.size() / xVals.size();

    if(zSetOfX == 1) genIndices1D(&indices, xVals.size());
    else if(ySetOfX > 1 && zSetOfY == 1) genIndices2D(&indices, GL4_PolyFunc::xVals.size(), GL4_PolyFunc::yVals.size());
    // else if(ySetOfX == 1 && zSetOfY > 1) genIndices2(&indices, GL4_PolyFunc::xVals.size(), GL4_PolyFunc::yVals.size(), GL4_PolyFunc::zVals.size());
    else if(ySetOfX > 1 && zSetOfY > 1) genIndices3D(&indices, GL4_PolyFunc::xVals.size(), GL4_PolyFunc::yVals.size(), GL4_PolyFunc::zVals.size());
    else std::cerr << "Something went wrong while indexing Grid" << std::endl;
}

#include "geometry/polybase/GL4_PolyFunc.hpp"

static char error_xValsImmute[] = "X values are immutable";
static char error_yValsImmute[] = "Y values are immutable";
static char error_zValsImmute[] = "Z values are immutable";
static char error_xyzPresent[] = "X, Y, and Z values must be present to create()";

void GL4_PolyFunc::reset(){
    GL4_PolyFunc::xVals.clear();
    GL4_PolyFunc::yVals.clear();
    GL4_PolyFunc::zVals.clear();
    GL4_PolyFunc::xyzBits.reset();
    GL4_PolyFunc::xSequence = nullptr;
    GL4_PolyFunc::yEquation = nullptr;
    GL4_PolyFunc::zEquation = nullptr;
}

void GL4_PolyFunc::gen_x(){
    if(GL4_PolyFunc::xyzBits[GL4_PolyFunc::Y] == true || GL4_PolyFunc::xyzBits[GL4_PolyFunc::Z] == true) logError(__FILE__, __LINE__, error_xValsImmute);

    GL4_PolyFunc::xSequence(&xVals);
    GL4_PolyFunc::xyzBits.set(GL4_PolyFunc::X);
}

void GL4_PolyFunc::gen_y(){
    if(GL4_PolyFunc::xyzBits[GL4_PolyFunc::Z] == true) logError(__FILE__, __LINE__, error_yValsImmute);

    if(GL4_PolyFunc::yVals.empty())
        GL4_PolyFunc::yVals.resize(GL4_PolyFunc::xVals.size());
    else
        GL4_PolyFunc::yVals.resize(GL4_PolyFunc::yVals.size() + GL4_PolyFunc::xVals.size());

    unsigned xElem = 0;
    for(unsigned yElem = GL4_PolyFunc::yVals.size() - GL4_PolyFunc::xVals.size(); yElem < GL4_PolyFunc::yVals.size(); yElem++){
        xElem++;
        GL4_PolyFunc::yVals[yElem] = GL4_PolyFunc::yEquation(GL4_PolyFunc::xVals[xElem]);
    }

    GL4_PolyFunc::xyzBits.set(GL4_PolyFunc::Y);
}

void GL4_PolyFunc::gen_z(){
    if(GL4_PolyFunc::zVals.empty())
        GL4_PolyFunc::zVals.resize(GL4_PolyFunc::yVals.size());
    else
        GL4_PolyFunc::zVals.resize(GL4_PolyFunc::zVals.size() + GL4_PolyFunc::yVals.size());

    unsigned xElem = 0;
    unsigned yElem = 0;
    for(unsigned zElem = GL4_PolyFunc::zVals.size() - GL4_PolyFunc::yVals.size(); zElem < GL4_PolyFunc::zVals.size(); zElem++){
        if(xElem == GL4_PolyFunc::xVals.size()) xElem = 0;
        if(yElem == GL4_PolyFunc::yVals.size()) yElem = 0;
        GL4_PolyFunc::zVals[zElem] = GL4_PolyFunc::zEquation(GL4_PolyFunc::xVals[xElem], GL4_PolyFunc::yVals[yElem]);
        xElem++; yElem++;
    }

    GL4_PolyFunc::xyzBits.set(GL4_PolyFunc::Z);
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
    if(!GL4_PolyFunc::xyzBits.all()) logError(__FILE__, __LINE__, error_xyzPresent);

    std::vector<GLfloat> threePts(GL4_PolyFunc::zVals.size() * 3);
    for(GLuint vecElem = 0; vecElem < GL4_PolyFunc::zVals.size(); vecElem++){
        threePts[vecElem * 3] = GL4_PolyFunc::xVals[vecElem % GL4_PolyFunc::xVals.size()];
        threePts[vecElem * 3 + 1] = GL4_PolyFunc::yVals[vecElem % GL4_PolyFunc::yVals.size()];
        threePts[vecElem * 3 + 2] = GL4_PolyFunc::zVals[vecElem];
    }

    std::vector<unsigned> indexAccum;

    unsigned ySetOfX = GL4_PolyFunc::yVals.size() / GL4_PolyFunc::xVals.size();
    unsigned zSetOfY = GL4_PolyFunc::zVals.size() / GL4_PolyFunc::yVals.size();
    unsigned zSetOfX = GL4_PolyFunc::zVals.size() / GL4_PolyFunc::xVals.size();

    if(zSetOfX == 1) mesh->order.indexCount = genIndices1D(&indexAccum, GL4_PolyFunc::xVals.size());
    else if(ySetOfX > 1 && zSetOfY == 1) mesh->order.indexCount = genIndices2D(&indexAccum, GL4_PolyFunc::xVals.size(), GL4_PolyFunc::yVals.size());
    // else if(ySetOfX == 1 && zSetOfY > 1) genIndices2(&indexAccum, GL4_PolyFunc::xVals.size(), GL4_PolyFunc::yVals.size(), GL4_PolyFunc::zVals.size());
    else if(ySetOfX > 1 && zSetOfY > 1) mesh->order.indexCount = genIndices3D(&indexAccum, GL4_PolyFunc::xVals.size(), GL4_PolyFunc::yVals.size(), GL4_PolyFunc::zVals.size());
    else std::cerr << "Something went wrong while indexing Grid" << std::endl;

    mesh->add_feed(factory->get_format(0));
    mesh->run_feed(0, threePts.data(), sizeof(float));
}

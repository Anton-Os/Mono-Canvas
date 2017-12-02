#include "geometry/GL4_PolyFunc.hpp"

void GL4_PolyFunc::reset(){
    GL4_PolyFunc::xVals.clear();
    GL4_PolyFunc::yVals.clear();
    GL4_PolyFunc::zVals.clear();
    GL4_PolyFunc::xyzBits.reset();
    GL4_PolyFunc::indexCount = 0;
    GL4_PolyFunc::vertexCount = 0;
    GL4_PolyFunc::relMatrix = glm::mat4(1);
    GL4_PolyFunc::xEquation = nullptr;
    GL4_PolyFunc::yEquation = nullptr;
    GL4_PolyFunc::zEquation = nullptr;
}

void GL4_PolyFunc::gen_x(){
    if(GL4_PolyFunc::xyzBits[GL4_PolyFunc::Y] == true || GL4_PolyFunc::xyzBits[GL4_PolyFunc::Z] == true){
        std::cerr << "X values are immutable" << std::endl;
        return;
    }
    GL4_PolyFunc::xEquation(&xVals);
    GL4_PolyFunc::xyzBits.set(GL4_PolyFunc::X);
}

void GL4_PolyFunc::gen_y(){
    if(GL4_PolyFunc::xyzBits[GL4_PolyFunc::Z] == true){
        std::cerr << "Y values are immutable" << std::endl;
        return;
    }

    if(GL4_PolyFunc::yVals.empty())
        GL4_PolyFunc::yVals.resize(GL4_PolyFunc::xVals.size());
    else
        GL4_PolyFunc::yVals.resize(GL4_PolyFunc::yVals.size() + GL4_PolyFunc::xVals.size());

    unsigned int xElem = 0;
    for(unsigned int yElem = GL4_PolyFunc::yVals.size() - GL4_PolyFunc::xVals.size(); yElem < GL4_PolyFunc::yVals.size(); yElem++){
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

    unsigned int xElem = 0;
    unsigned int yElem = 0;
    for(unsigned int zElem = GL4_PolyFunc::zVals.size() - GL4_PolyFunc::yVals.size(); zElem < GL4_PolyFunc::zVals.size(); zElem++){
        if(xElem == GL4_PolyFunc::xVals.size()) xElem = 0;
        if(yElem == GL4_PolyFunc::yVals.size()) yElem = 0;
        GL4_PolyFunc::zVals[zElem] = GL4_PolyFunc::zEquation(GL4_PolyFunc::xVals[xElem], GL4_PolyFunc::yVals[yElem]);
        xElem++; yElem++;
    }

    GL4_PolyFunc::xyzBits.set(GL4_PolyFunc::Z);
}

void GL4_PolyFunc::createXI(){
    if(!GL4_PolyFunc::xyzBits.all()){
        std::cerr << "Feed GL can only work if all x y z values are present" << std::endl;
        return;
    }

    std::vector<GLfloat> threePts(GL4_PolyFunc::zVals.size() * 3);
    for(GLuint vecElem = 0; vecElem < GL4_PolyFunc::zVals.size(); vecElem++){
        threePts[vecElem * 3] = GL4_PolyFunc::xVals[vecElem % GL4_PolyFunc::xVals.size()];
        threePts[vecElem * 3 + 1] = GL4_PolyFunc::yVals[vecElem % GL4_PolyFunc::yVals.size()];
        threePts[vecElem * 3 + 2] = GL4_PolyFunc::zVals[vecElem];
    }

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, threePts.size() * sizeof(GLfloat), threePts.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    GL4_PolyFunc::vertexCount = threePts.size() / 3;
    GL4_PolyFunc::feed[GL4_PolyFunc::VAO] = VAO;
    GL4_PolyFunc::feed[GL4_PolyFunc::feedPos] = VBO;
}

unsigned int genIndices1D(std::vector<unsigned int>* indexAccum, unsigned int xCount){
    unsigned int indexCount = 0;
    for(unsigned int indexElem = 0; indexElem < xCount - 1; indexElem++){
        indexAccum->push_back(indexElem);
        indexAccum->push_back(indexElem + 1);
        indexCount += 2;
    }
    return indexCount;
}

unsigned int genIndices2D(std::vector<unsigned int>* indexAccum, unsigned int xCount, unsigned int yCount){
    unsigned int indexCount = 0;
    std::array<unsigned int, 4> indexSet;
    for(unsigned int indexElem = 0; indexElem < yCount - xCount; indexElem++){
        if(indexElem % xCount == xCount - 1) continue;
        indexSet = {indexElem, indexElem + 1, indexElem + xCount, indexElem + xCount + 1};
        indexAccum->push_back(indexSet[0]);
        indexAccum->push_back(indexSet[1]);
        indexAccum->push_back(indexSet[2]);
        indexAccum->push_back(indexSet[3]);
        indexAccum->push_back(indexSet[2]);
        indexAccum->push_back(indexSet[1]);
        indexCount += 6;
    }
    return indexCount;
}

unsigned int genIndices3D(std::vector<unsigned int>* indexAccum, unsigned int xCount, unsigned int yCount, unsigned int zCount){
    unsigned int indexCount = 0;
    unsigned int ySetOfX = yCount / xCount;
    unsigned int zSetOfY = zCount / yCount;
    std::array<unsigned int, 4> indexSet;
    for(unsigned int zIndex = 0; zIndex < zSetOfY; zIndex++){
        for(unsigned int indexElem = zIndex * yCount; indexElem < zIndex * yCount + yCount - xCount; indexElem++){
            if(indexElem % xCount == xCount - 1) continue;
            indexSet = {indexElem, indexElem + 1, indexElem + xCount, indexElem + xCount + 1};
            indexAccum->push_back(indexSet[0]);
            indexAccum->push_back(indexSet[1]);
            indexAccum->push_back(indexSet[2]);
            indexAccum->push_back(indexSet[3]);
            indexAccum->push_back(indexSet[2]);
            indexAccum->push_back(indexSet[1]);
            indexCount += 6;
        }
    }

    unsigned int indexOffset = 0;
    for(unsigned int zIndex = 0; zIndex < zSetOfY - 1; zIndex++){
        indexOffset = zIndex * yCount;
        for(unsigned int xIndex = 0; xIndex < xCount - 1; xIndex++){
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
            indexCount += 6;
            unsigned int incFactor = yCount - xCount;
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
            indexCount += 6;
        }
    }

    for(unsigned int zIndex = 0; zIndex < zSetOfY - 1; zIndex++){
        for(unsigned int yIndex = 0; yIndex < yCount - xCount; yIndex += xCount){
            indexSet = {
                yIndex,
                yIndex + xCount,
                yIndex + yCount,
                yIndex + yCount + xCount
            };
            indexAccum->push_back(indexSet[0]);
            indexAccum->push_back(indexSet[1]);
            indexAccum->push_back(indexSet[2]);
            indexAccum->push_back(indexSet[3]);
            indexAccum->push_back(indexSet[2]);
            indexAccum->push_back(indexSet[1]);
            indexCount += 6;
            unsigned int incFactor = xCount - 1;
            indexSet = {
                yIndex + incFactor,
                yIndex + xCount + incFactor,
                yIndex + yCount + incFactor,
                yIndex + yCount + xCount + incFactor
            };
            indexAccum->push_back(indexSet[0]);
            indexAccum->push_back(indexSet[1]);
            indexAccum->push_back(indexSet[2]);
            indexAccum->push_back(indexSet[3]);
            indexAccum->push_back(indexSet[2]);
            indexAccum->push_back(indexSet[1]);
            indexCount += 6;
        }
    }

    return indexCount;
}

void GL4_PolyFunc::create(){
    if(!GL4_PolyFunc::xyzBits.all()){
        std::cerr << "Feed GL can only work if all x y z values are present" << std::endl;
        return;
    }

    std::vector<GLfloat> threePts(GL4_PolyFunc::zVals.size() * 3);
    for(GLuint vecElem = 0; vecElem < GL4_PolyFunc::zVals.size(); vecElem++){
        threePts[vecElem * 3] = GL4_PolyFunc::xVals[vecElem % GL4_PolyFunc::xVals.size()];
        threePts[vecElem * 3 + 1] = GL4_PolyFunc::yVals[vecElem % GL4_PolyFunc::yVals.size()];
        threePts[vecElem * 3 + 2] = GL4_PolyFunc::zVals[vecElem];
    }

    std::vector<unsigned int> indexAccum;

    unsigned int ySetOfX = GL4_PolyFunc::yVals.size() / GL4_PolyFunc::xVals.size();
    unsigned int zSetOfY = GL4_PolyFunc::zVals.size() / GL4_PolyFunc::yVals.size();
    unsigned int zSetOfX = GL4_PolyFunc::zVals.size() / GL4_PolyFunc::xVals.size();

    if(zSetOfX == 1) GL4_PolyFunc::indexCount = genIndices1D(&indexAccum, GL4_PolyFunc::xVals.size());
    else if(ySetOfX > 1 && zSetOfY == 1) GL4_PolyFunc::indexCount = genIndices2D(&indexAccum, GL4_PolyFunc::xVals.size(), GL4_PolyFunc::yVals.size());
    // else if(ySetOfX == 1 && zSetOfY > 1) genIndices2(&indexAccum, GL4_PolyFunc::xVals.size(), GL4_PolyFunc::yVals.size(), GL4_PolyFunc::zVals.size());
    else if(ySetOfX > 1 && zSetOfY > 1) GL4_PolyFunc::indexCount = genIndices3D(&indexAccum, GL4_PolyFunc::xVals.size(), GL4_PolyFunc::yVals.size(), GL4_PolyFunc::zVals.size());
    else std::cerr << "Something went wrong while indexing Cartesian Grid" << std::endl;

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBOs[2];
    glGenBuffers(2, VBOs);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexAccum.size() * sizeof(GLuint), indexAccum.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, threePts.size() * sizeof(GLfloat), threePts.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    GL4_PolyFunc::vertexCount = threePts.size() / 3;
    GL4_PolyFunc::feed[GL4_PolyFunc::VAO] = VAO;
    GL4_PolyFunc::feed[GL4_PolyFunc::EBO] = VBOs[0];
    GL4_PolyFunc::feed[GL4_PolyFunc::feedPos] = VBOs[1];
}

void GL4_PolyFunc::drawXI(GLenum drawMode, GLuint drawCount){
    glBindVertexArray(GL4_PolyFunc::feed[GL4_PolyFunc::VAO]);
    glDrawArrays(drawMode, 0, drawCount);
    glBindVertexArray(0);
}

void GL4_PolyFunc::draw(GLenum drawMode){
    glBindVertexArray(GL4_PolyFunc::feed[GL4_PolyFunc::VAO]);
    glDrawElements(drawMode, GL4_PolyFunc::indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void GL4_PolyFunc::draw(GLenum drawMode, unsigned int drawCount){
    glBindVertexArray(GL4_PolyFunc::feed[GL4_PolyFunc::VAO]);
    glDrawElements(drawMode, drawCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

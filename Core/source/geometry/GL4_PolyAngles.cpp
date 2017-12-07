#include "geometry/GL4_PolyAngles.hpp"

void GL4_PolyAngles::reset(){
    GL4_PolyAngles::angles.clear();
    GL4_PolyAngles::xVals.clear();
    GL4_PolyAngles::yVals.clear();
    GL4_PolyAngles::zVals.clear();
    GL4_PolyAngles::xyzBits.reset();
    GL4_PolyAngles::idxCount = 0;
    GL4_PolyAngles::vertexCount = 0;
    GL4_PolyAngles::relMatrix = glm::mat4(1);
    GL4_PolyAngles::anglEquation = nullptr;
    GL4_PolyAngles::idxEquation = nullptr;
    GL4_PolyAngles::xEquation = nullptr;
    GL4_PolyAngles::yEquation = nullptr;
    GL4_PolyAngles::zEquation = nullptr;
}

void GL4_PolyAngles::gen_angl(){
    if(GL4_PolyAngles::xyzBits[GL4_PolyAngles::X] == true || 
       GL4_PolyAngles::xyzBits[GL4_PolyAngles::Y] == true ||
       GL4_PolyAngles::xyzBits[GL4_PolyAngles::Z] == true){
        std::cerr << "Angles are immutable" << std::endl;
        return;
    }
    GL4_PolyAngles::anglEquation(&angles);
    GL4_PolyAngles::xyzBits.set(GL4_PolyAngles::Angl);
}

void GL4_PolyAngles::gen_x(){
    if(GL4_PolyAngles::xyzBits[GL4_PolyAngles::Angl] == false){
        std::cout << "X Values are immutable without Angles" << std::endl;
        return;
    }

    GL4_PolyAngles::xVals.resize(GL4_PolyAngles::angles.size());

    for(unsigned int xElem = 0; xElem < GL4_PolyAngles::xVals.size(); xElem++)
        GL4_PolyAngles::xVals[xElem] = GL4_PolyAngles::xEquation(GL4_PolyAngles::angles[xElem]);

    xyzBits.set(GL4_PolyAngles::X);
}

void GL4_PolyAngles::gen_y(){
    if(GL4_PolyAngles::xyzBits[GL4_PolyAngles::Angl] == false){
        std::cout << "Y Values are immutable without Angles" << std::endl;
        return;
    }

    GL4_PolyAngles::yVals.resize(GL4_PolyAngles::angles.size());

    for(unsigned int yElem = 0; yElem < GL4_PolyAngles::yVals.size(); yElem++)
        GL4_PolyAngles::yVals[yElem] = GL4_PolyAngles::yEquation(GL4_PolyAngles::angles[yElem]);

    xyzBits.set(GL4_PolyAngles::Y);
}

void GL4_PolyAngles::gen_z(){
    if(GL4_PolyAngles::xyzBits[GL4_PolyAngles::Angl] == false){
        std::cout << "Z Values are immutable without Angles" << std::endl;
        return;
    }

    GL4_PolyAngles::zVals.resize(GL4_PolyAngles::angles.size());

    for(unsigned int zElem = 0; zElem < GL4_PolyAngles::zVals.size(); zElem++)
        GL4_PolyAngles::zVals[zElem] = GL4_PolyAngles::zEquation(GL4_PolyAngles::angles[zElem]);

    xyzBits.set(GL4_PolyAngles::Z);
}

void GL4_PolyAngles::createXI(){
    if(!GL4_PolyAngles::xyzBits.all()){
        std::cerr << "Feed GL can only work if all x y z values are present" << std::endl;
        return;
    }

    std::vector<GLfloat> threePts(GL4_PolyAngles::angles.size() * 3);
    for(GLuint vecElem = 0; vecElem < GL4_PolyAngles::angles.size(); vecElem++){
        threePts[vecElem * 3] = GL4_PolyAngles::xVals[vecElem];
        threePts[vecElem * 3 + 1] = GL4_PolyAngles::yVals[vecElem];
        threePts[vecElem * 3 + 2] = GL4_PolyAngles::zVals[vecElem];
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

    GL4_PolyAngles::isFed = true;
    GL4_PolyAngles::vertexCount = threePts.size() / 3;
    GL4_PolyAngles::VAO = VAO;
    GL4_PolyAngles::posBff = VBO;
}

unsigned int genIndices1D(std::vector<unsigned int>* indexAccum, unsigned int posCount){
    unsigned int idxCount = 0;
    for(unsigned int i = 1; i < posCount; i++){
        indexAccum->push_back(i);
        indexAccum->push_back(i + 1);
        idxCount += 2;
    }
    indexAccum->at(idxCount - 1) = 1;
    return idxCount;
}

void GL4_PolyAngles::create(){
    if(!GL4_PolyAngles::xyzBits.all()){
        std::cerr << "Feed GL can only work if all x y z values are present" << std::endl;
        return;
    }

    std::vector<GLfloat> threePts(GL4_PolyAngles::angles.size() * 3);
    for(GLuint vecElem = 0; vecElem < GL4_PolyAngles::angles.size(); vecElem++){
        threePts[vecElem * 3] = GL4_PolyAngles::xVals[vecElem];
        threePts[vecElem * 3 + 1] = GL4_PolyAngles::yVals[vecElem];
        threePts[vecElem * 3 + 2] = GL4_PolyAngles::zVals[vecElem];
    }

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    std::vector<unsigned int> indexAccum;
    GL4_PolyAngles::idxCount = genIndices1D(&indexAccum, threePts.size() / 3);

    GLuint VBOs[2];
    glGenBuffers(2, VBOs);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexAccum.size() * sizeof(unsigned int), indexAccum.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, threePts.size() * sizeof(GLfloat), threePts.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    GL4_PolyAngles::isFed = true;
    GL4_PolyAngles::isIdx = true;
    GL4_PolyAngles::vertexCount = threePts.size() / 3;
    GL4_PolyAngles::VAO = VAO;
    GL4_PolyAngles::posBff = VBOs[0];
    GL4_PolyAngles::idxBff = VBOs[1];
}

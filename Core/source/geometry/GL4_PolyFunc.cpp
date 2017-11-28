#include "geometry/GL4_PolyFunc.hpp"

void GL4_PolyFunc::gen_x(){
    if(GL4_PolyFunc::xyzBits[GL4_PolyFunc::Y] == true || GL4_PolyFunc::xyzBits[GL4_PolyFunc::Z] == true){
        std::cerr << "X values are immutable" << std::endl;
        return;
    }
    GL4_PolyFunc::xEquasion(&xVals);
    GL4_PolyFunc::xyzBits.set(0);
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
        GL4_PolyFunc::yVals[yElem] = GL4_PolyFunc::yEquasion(GL4_PolyFunc::xVals[xElem]);
    }

    GL4_PolyFunc::xyzBits.set(1);
}

void GL4_PolyFunc::gen_z(){
    if(GL4_PolyFunc::zVals.empty())
        GL4_PolyFunc::zVals.resize(GL4_PolyFunc::yVals.size());
    else
        GL4_PolyFunc::zVals.resize(GL4_PolyFunc::zVals.size() + GL4_PolyFunc::yVals.size());

    for(unsigned int zElem = GL4_PolyFunc::zVals.size() - GL4_PolyFunc::yVals.size(); zElem < GL4_PolyFunc::zVals.size(); zElem++)
        GL4_PolyFunc::zVals[zElem] = GL4_PolyFunc::zEquasion(GL4_PolyFunc::xVals[zElem % GL4_PolyFunc::xVals.size()], GL4_PolyFunc::yVals[zElem]);

    GL4_PolyFunc::xyzBits.set(2);
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

void GL4_PolyFunc::draw(GLenum drawMode, GLuint drawCount){
    glBindVertexArray(GL4_PolyFunc::feed[GL4_PolyFunc::VAO]);
    glDrawArrays(drawMode, 0, drawCount);
    glBindVertexArray(0);
}

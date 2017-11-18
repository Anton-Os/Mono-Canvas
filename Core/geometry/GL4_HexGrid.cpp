#include "Geometry.h"

#include <algorithm>

namespace HexAngle {
    /* float shortSide = 2.0 * glm::pi<float>() / 6;
    float longSide = shortSide * 5;
    float sin30 = std::sin(shortSide);
    float cos30 = std::cos(shortSide);
    float sin150= std::sin(longSide);
    float cos150 = std::cos(longSide); */
    float sin30 = std::sin(glm::radians(30.0f));
    float cos30 = std::cos(glm::radians(30.0f));
    float sin150= std::sin(glm::radians(150.0f));
    float cos150 = std::cos(glm::radians(150.0f));
}

Hexagon createHex(float size) {
    Hexagon hexagon;
    std::fill(hexagon.midPoint.begin(), hexagon.midPoint.end(), 0.0f);
    std::fill(hexagon.sixProx.begin(), hexagon.sixProx.end(), 0.0f);

    hexagon.sixProx[0] = size;
    hexagon.sixProx[3] = -1 * size;
    hexagon.sixProx[6] = HexAngle::sin30 * size;
    hexagon.sixProx[7] = HexAngle::cos30 * size;
    hexagon.sixProx[9] = HexAngle::sin150 * size;
    hexagon.sixProx[10] = HexAngle::cos150 * size;
    hexagon.sixProx[12] = -1 * HexAngle::sin30 * size;
    hexagon.sixProx[13] = -1 * HexAngle::cos30 * size;
    hexagon.sixProx[15] = -1 * HexAngle::sin150 * size; 
    hexagon.sixProx[16] = -1 * HexAngle::cos150 * size;

    return hexagon;
}

Hexagon createHex(float size, float initPos[]) {
    Hexagon hexagon;
    std::fill(hexagon.midPoint.begin(), hexagon.midPoint.end(), 0.0f);
    std::fill(hexagon.sixProx.begin(), hexagon.sixProx.end(), 0.0f);

    hexagon.sixProx[0] = size + initPos[0];
    hexagon.sixProx[1] = initPos[1];
    hexagon.sixProx[3] = -1 * size + initPos[0];
    hexagon.sixProx[4] = initPos[1];
    hexagon.sixProx[6] = HexAngle::sin30 * size + initPos[0];
    hexagon.sixProx[7] = HexAngle::cos30 * size + initPos[1];
    hexagon.sixProx[9] = HexAngle::sin150 * size + initPos[0];
    hexagon.sixProx[10] = HexAngle::cos150 * size + initPos[1];
    hexagon.sixProx[12] = -1 * HexAngle::sin30 * size + initPos[0];
    hexagon.sixProx[13] = -1 * HexAngle::cos30 * size + initPos[1];
    hexagon.sixProx[15] = -1 * HexAngle::sin150 * size + initPos[0]; 
    hexagon.sixProx[16] = -1 * HexAngle::cos150 * size + initPos[1];

    hexagon.midPoint[0] = initPos[0];
    hexagon.midPoint[1] = initPos[1];

    return hexagon;
}

/* void GL4_HexGrid::create(GLuint xDimension, GLuint rowCount, GLuint yDimension, GLuint colCount){

} */

/* void GL4_HexGrid::create(float hexSize, GLuint rowCount, GLuint colCount){
    float pos[2];
    float colOffset = -1 * hexSize * 2 * colCount;
    
    Hexagon hexagon;
    GLuint vertexCount = 0;
    for(GLuint currentCol = 0; currentCol < colCount; colCount++){
        pos[0] = 0.0;
        pos[1] = colOffset;
        hexagon = createHex(hexSize, pos);
        vertexCount += 6;
    }

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint feed[3];
    glGenBuffers(3, feed);
    glBindBuffer(GL_ARRAY_BUFFER, feed[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, hexagon.sixProx.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(0);

    GL4_HexGrid::vertexCount = vertexCount;
    GL4_HexGrid::feed[GL4_HexGrid::VAO] = VAO;
    // GL4_HexGrid::feed[GL4_HexGrid::feedPos] = feed[1];

    glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}*/

void GL4_HexGrid::drawXI(GLenum drawMode){
    glBindVertexArray(GL4_HexGrid::feed[GL4_HexGrid::VAO]);
    glDrawArrays(drawMode, 0, GL4_HexGrid::vertexCount);
    glBindVertexArray(0);
}
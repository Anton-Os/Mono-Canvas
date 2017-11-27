#include "geometry/GL4_HexGrid.hpp"

#include <algorithm>

namespace HexAngle {
    /* float shortSide = 2.0 * glm::pi<float>() / 6;
    float longSide = shortSide * 5;
    float sin30 = std::sin(shortSide);
    float cos30 = std::cos(shortSide);
    float sin150= std::sin(longSide);
    float cos150 = std::cos(longSide); */
    const float sin30 = std::sin(glm::radians(30.0f));
    const float cos30 = std::cos(glm::radians(30.0f));
    const float sin150= std::sin(glm::radians(150.0f));
    const float cos150 = std::cos(glm::radians(150.0f));
}

Hexagon createHex(float size) {
    Hexagon hexagon;
    std::fill(hexagon.midPoint, hexagon.midPoint + 3, 0.0f);
    std::fill(hexagon.sixProx, hexagon.sixProx + 18, 0.0f);

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
    std::fill(hexagon.midPoint, hexagon.midPoint + 3, 0.0f);
    std::fill(hexagon.sixProx, hexagon.sixProx + 18, 0.0f);

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


HexagonIdx12 createHexIdx12(float size, float initPos[], unsigned short int mode) {
    HexagonIdx12 hexagon12;
    std::fill(hexagon12.midPoint, hexagon12.midPoint + 3, 0.0f);
    std::fill(hexagon12.sixProx, hexagon12.sixProx + 18, 0.0f);

    hexagon12.sixProx[0] = size + initPos[0];
    hexagon12.sixProx[1] = initPos[1];
    hexagon12.sixProx[3] = -1 * size + initPos[0];
    hexagon12.sixProx[4] = initPos[1];
    hexagon12.sixProx[6] = HexAngle::sin30 * size + initPos[0];
    hexagon12.sixProx[7] = HexAngle::cos30 * size + initPos[1];
    hexagon12.sixProx[9] = HexAngle::sin150 * size + initPos[0];
    hexagon12.sixProx[10] = HexAngle::cos150 * size + initPos[1];
    hexagon12.sixProx[12] = -1 * HexAngle::sin30 * size + initPos[0];
    hexagon12.sixProx[13] = -1 * HexAngle::cos30 * size + initPos[1];
    hexagon12.sixProx[15] = -1 * HexAngle::sin150 * size + initPos[0]; 
    hexagon12.sixProx[16] = -1 * HexAngle::cos150 * size + initPos[1];

    hexagon12.midPoint[0] = initPos[0];
    hexagon12.midPoint[1] = initPos[1];

    if(mode == 0) // Outline
        hexagon12.indices = { 1, 4, 4, 3, 3, 0, 0, 2, 2, 5, 5, 1 };
    else if(mode == 1) // Vertical Fill
        hexagon12.indices = { 1, 5, 4, 4, 3, 5, 5, 2, 3, 3, 0, 2};
    else if(mode == 2) // Horizontal Fill
        hexagon12.indices = { 1, 3, 4, 0, 3, 1, 1, 5, 0, 5, 2, 0};
    else if(mode == 3) // Clockwise Fill with "pinhole"
        hexagon12.indices = { 1, 5, 2, 5, 2, 0, 0, 4, 3, 1, 3, 4};

    return hexagon12;
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, hexagon.sixProx.data(), GL_STAT C_DRAW);
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
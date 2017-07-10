#include "Assimp.h"

Mesh::Mesh(GLuint shaderProgIdArg, std::vector<Point> pointsArg, std::vector<GLuint> indicesArg, std::vector<Texture> texturesArg){
    shaderProgId = shaderProgIdArg;
    points = pointsArg;
    indices = indicesArg;
    textures = texturesArg;

    loadMesh();
}

void Mesh::loadMesh(){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(Point), &points[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (GLvoid*)offsetof(Point, pos));
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Point), (void*)offsetof(Point, color));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)offsetof(Point, texCoord));
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)offsetof(Point, normal));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void Mesh::renderMesh(){
    glUseProgram(shaderProgId);

    // set uniforms

    glBindTextureUnit(0, textures[0].texId);

    // draw arrays

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::deleteMesh(){
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}



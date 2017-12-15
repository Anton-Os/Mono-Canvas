#include "geometry/GL4_Tree.hpp"

glm::mat4 GL4_Tree::traceBack(GLuint nodeID){
    if(nodeID > GL4_Tree::nodeOrder.size()){
        std::cout << "Node requested is out of bounds" << std::endl;
        return glm::mat4(1);
    }
    std::vector<glm::mat4> matrices;
    GLuint exitNode = GL4_Tree::nodeOrder.size() + 1;
    GLuint currentNode = nodeID;
    while(currentNode != exitNode){
        matrices.push_back(GL4_Tree::nodes[currentNode].relMatrix);
        if(currentNode == 0) currentNode = exitNode;
        else currentNode = GL4_Tree::nodeOrder[currentNode];
    }

    glm::mat4 matrix = matrices[matrices.size() - 1];
    if(matrices.size() == 1) return matrix;

    for(unsigned int matrixElem = matrices.size() - 2; matrixElem >= 0; matrixElem--){
        matrix *= matrices[matrixElem];
    }

    return matrix;
}
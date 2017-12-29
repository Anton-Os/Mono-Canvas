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

glm::mat4 GL4_Tree::get_mtx(GLuint nodeID){
    if(nodeID > GL4_Tree::nodeOrder.size()){
        std::cout << "Node requested is out of bounds" << std::endl;
        return glm::mat4(1);
    }
    return GL4_Tree::nodes[nodeID].relMatrix;
}

void GL4_Tree::drawXI(GLuint nodeID, GLenum drawMode){
    if(nodeID > GL4_Tree::nodeOrder.size()){
        std::cout << "Node requested is out of bounds" << std::endl;
        return;
    }
    GL4_Tree::nodes[nodeID].drawXI(drawMode);
}

void GL4_Tree::draw(GLuint nodeID, GLenum drawMode){
    if(nodeID > GL4_Tree::nodeOrder.size()){
        std::cout << "Node requested is out of bounds" << std::endl;
        return;
    }
    GL4_Tree::nodes[nodeID].draw(drawMode);
}

void GL4_Tree::exportMeta(GL4_Tree_Meta* treeMeta){
    treeMeta->nodeCount = GL4_Tree::nodeOrder.size();
}

void GL4_Tree::addNode(glm::mat4* matrix, vertexFeed* vFeed){
    GL4_Entity entity;
    entity.relMatrix = *matrix;
    entity.init();
    entity.feedPos(vFeed->pos.data(), vFeed->pos.size());
    GL4_Tree::nodes.push_back(entity);
    GL4_Tree::nodeOrder.push_back(0);
}

void GL4_Tree::addNode(glm::mat4* matrix, vertexFeedIdx* vFeed){
    GL4_Entity entity;
    entity.relMatrix = *matrix;
    entity.init();
    entity.feedPos(vFeed->pos.data(), vFeed->pos.size());
    entity.feedIdx(vFeed->idx.data(), vFeed->idx.size());
    GL4_Tree::nodes.push_back(entity);
    GL4_Tree::nodeOrder.push_back(0);
}


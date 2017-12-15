#ifndef GEOMETRY_H
    #include "Geometry.hpp"
    #define GEOMETRY_H
#endif

#ifndef GL4_ENTITY_H
    #include "geometry/GL4_Entity.hpp"
#endif

#ifndef GL4_TREE_H
    class GL4_Tree {
    public:
        glm::mat4 relMatrix;
        glm::mat4 traceBack(GLuint nodeID);
        void addNode(glm::mat4* matrix, vertexFeed* vFeed);
    private:
        std::vector<GL4_Entity> nodes;
        std::vector<GLuint> nodeOrder;
    };
#define GL4_TREE_H
#endif

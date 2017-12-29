#ifndef GEOMETRY_H
    #include "Geometry.hpp"
    #define GEOMETRY_H
#endif

#ifndef GL4_ENTITY_H
    #include "geometry/GL4_Entity.hpp"
#endif

#ifndef GL4_TREE_H
    struct GL4_Tree_Meta {
        // Will contain data such as max children, lowest child, etc...
        unsigned nodeCount;
    };

    class GL4_Tree {
    public:
        glm::mat4 relMatrix;
        glm::mat4 traceBack(GLuint nodeID);
        glm::mat4 get_mtx(GLuint nodeID);
        void addNode(glm::mat4* matrixPtr, vertexFeed* vFeed);
        void addNode(glm::mat4* matrixPtr, vertexFeedIdx* vFeed);
        void drawXI(GLuint nodeID, GLenum drawMode);
        void draw(GLuint nodeID, GLenum drawMode);
        void exportMeta(GL4_Tree_Meta* treeMeta);
    private:
        std::vector<GL4_Entity> nodes;
        std::vector<GLuint> nodeOrder;
    };
#define GL4_TREE_H
#endif

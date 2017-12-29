#ifndef GEOMETRY_H
    #include "Geometry.hpp"
    #define GEOMETRY_H
#endif

#ifndef GL4_TREE_H
    #include "geometry/GL4_Tree.hpp"
#endif

#ifndef POLY_CLONE_H
    class GL4_PolyClone : public GL4_Tree {
    public:
        void reset();
        void (*mtxSequence)(std::vector<glm::mat4>* matrices);
        void gen_mtx(); 
        void createXI(vertexFeed* vFeed);
        void create(vertexFeedIdx* vFeed);
    private:
        std::vector<glm::mat4> matrices;
        enum ptAttrib { Mtx };
        std::bitset<1> xyzBits;
    };
#define POLY_CLONE_H
#endif

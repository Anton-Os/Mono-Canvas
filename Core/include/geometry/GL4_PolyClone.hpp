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
        void (*mtxSequence)(std::vector<glm::mat4>* matrices);
        void gen_mtx();
    };
#define POLY_CLONE_H
#endif

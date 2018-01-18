#ifndef GEOMETRY_H
    #include "Geometry.hpp"
    #define GEOMETRY_H
#endif

#ifndef GL4_MESH_H
    #include "geometry/GL4_Mesh.hpp"
#endif

#ifndef GL4_TREE_H
    struct GL4_Tree_Node {
        GL4_Tree_Node* parent;
        GL4_Mesh mesh;
        std::vector<float> transform;
    }

    class GL4_Tree {
    public:
        add_node(GL4_Mesh* mesh);
    private:
        std::vector<GL4_Entity> nodes;
    };
#define GL4_TREE_H
#endif

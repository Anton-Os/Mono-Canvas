#define PIPELINE_X
#ifndef GL4_API_COMMON_H
    #include "GL4_Api_Common.hpp"
#endif

#ifndef GL4_VERTEX_H
    #include "graphics/GL4_Vertex.hpp"
#endif

#ifndef GL4_VERTEX_FACTORY_H
    #include "graphics/factory/GL4_Vertex_Factory.hpp"
#endif

#ifndef GL4_MESH_H
    #include "graphics/entity/GL4_Mesh.hpp"
#endif

#ifndef GEOMETRY_HEDGY_HPP
    class Hedgy {
    public:
        void create(GL4_Mesh* mesh, GL4_Vertex_Factory* factory);
    };
#endif
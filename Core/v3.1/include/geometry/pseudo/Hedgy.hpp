#ifndef GEOMETRY_H
    #include "Geometry.hpp"
#endif

#ifndef GL4_VERTEX_H
    #include "GL4/GL4_Vertex.hpp"
#endif

#ifndef GL4_VERTEX_FACTORY_H
    #include "GL4/factory/GL4_Vertex_Factory.hpp"
#endif

#ifndef GL4_MESH_H
    #include "GL4/geometry/GL4_Mesh.hpp"
#endif

#ifndef GEOMETRY_HEDGY_HPP
    class Hedgy {
    public:
        void create(GL4_Mesh* mesh, GL4_Vertex_Factory* factory);
    };
#endif
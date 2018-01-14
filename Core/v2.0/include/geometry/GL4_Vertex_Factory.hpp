#ifndef GEOMETRY_H
    #include "Geometry.hpp"
#endif

#ifndef GL4_VERTEX_H
    #include "geometry/GL4_Vertex.hpp"
#endif

// #include <new>

#ifndef GL4_VERTEX_FACTORY_H

    class GL4_Vertex_Factory {
    public:
        GL4_Vertex_Factory(){ create(); }
        ~GL4_Vertex_Factory(){ delete[] formats; }
    private:
        GL4_Vertex* formats = new GL4_Vertex[4];
        // std::array<GL4_Vertex, 5> formats;
        void create();
    };

#define GL4_VERTEX_FACTORY_H
#endif
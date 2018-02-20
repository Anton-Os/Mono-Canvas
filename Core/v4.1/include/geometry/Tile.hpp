#define PIPELINE_X
#ifndef GL4_API_COMMON_H
    #include "GL4_Api_Common.hpp"
#endif
#ifndef ERROR_CODE_H
    #include "scene/ErrorCode.hpp"
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
#ifndef GEOMETRY_TILE_H
    class Tile {
    public:
        Tile(float height_arg, float width_arg){ init(height_arg, width_arg); }
        void init(float height_arg, float width_arg);
        void create(GL4_Mesh* mesh, GL4_Vertex_Factory* factory);
    private:
        float mHeight;
        float mWidth;
        bool mInitPhase = false;
        bool mCreatePhase = false;
    };
#endif

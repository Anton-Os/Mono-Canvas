#define PIPELINE_X
#ifndef GL4_API_COMMON_H
    #include "GL4_Api_Common.hpp"
#endif

#ifndef ERROR_CODE_H
    #include "scene/ErrorCode.hpp"
#endif

#ifndef GL4_VERTEX_FACTORY_H
    #include "graphics/factory/GL4_Vertex_Factory.hpp"
#endif

#ifndef GL4_MESH_H
    #include "graphics/geometry/GL4_Mesh.hpp"
#endif

#ifndef POLY_CLONE_H
    class GL4_PolyClone {
    public:
        void create();
        std::vector<float> transforms;
    };

#define POLY_CLONE_H
#endif

#ifndef GEOMETRY_H
    #include "Geometry.hpp"
#endif

#ifndef GL4_VERTEX_H
    #include "geometry/GL4_Vertex.hpp"
#endif

/* #define VERTEX_POS_FLT_3 0
#define VERTEX_COLOR_FLT_4 1
#define VERTEX_NORMAL_FLT_3 2
#define VERTEX_TEXCOORD_FLT_2 3 */

#define VERTEX_FACTORY_ATTRIB_COUNT 4

#ifndef GL4_VERTEX_FACTORY_H
    namespace GL4_Vertex_Feed {
        typedef enum { pos_3f, color_4f, normal_3f, texCoord_2f } Pick;
    }

    class GL4_Vertex_Factory {
    public:
        GL4_Vertex_Factory(){ create(); }
        ~GL4_Vertex_Factory(){ delete[] formats; }
        GL4_Vertex_Format* get_format(GLuint vAttrib);
    private:
        GL4_Vertex_Format* formats = new GL4_Vertex_Format[VERTEX_FACTORY_ATTRIB_COUNT];
        void create();
    };

    static GLint match_vAttrib(GLuint vAttrib, const GL4_Vertex_Format* formatPtr);
#define GL4_VERTEX_FACTORY_H
#endif
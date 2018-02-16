#ifndef GL4_API_COMMON_H
    #include <cstdlib>
    #include <vector>
    #include <string>
    #include <bitset>
    #include <stack>
    #include <algorithm>

    #include <GL/glew.h>

    #include <glm/gtc/matrix_transform.hpp>
    #include <glm/gtc/type_ptr.hpp>

    /* By default all "child-headers" and namespaces are included in the file unless you specify not to
       by defining an X Macro */

    // From Geometry.hpp

    #ifndef GEOMETRY_X
        const float GL4_TEXCOORD_S_MIN = 0.0f;
        const float GL4_TEXCOORD_S_MAX = 1.0f;
        const float GL4_TEXCOORD_T_MIN = 0.0f;
        const float GL4_TEXCOORD_T_MAX = 1.0f;

        namespace _GL4_Vertex_Feed_ID {
            enum Pick { 
                pos_3f,
                pos_2f,
                color_4f, 
                normal_3f, 
                texCoord_2f,
                frag_4f
            };
        }
    #endif

    // From Pipeline.hpp

    #ifndef PIPELINE_X
        namespace _GL4_Program_ID {
            typedef enum { Idle, Tones, Flatland } Pick;
        }

        namespace _GL4_Shader_Stage {
            typedef enum { vert, frag, tesc, tese, geom, comp } Pick;
        }

        namespace _GL4_Uniform_Basic_ID {
            enum Pick {
                renderMode
            };
        }

        namespace _GL4_Uniform_Matrix_ID {
            enum Pick {
                mvpMatrix
            };
        }
    #endif

#define GL4_API_COMMON_H
#endif
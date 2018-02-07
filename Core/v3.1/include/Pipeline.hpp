#ifndef PIPELINE_H
    #include <cstdio>
    #include <vector>
    #include <string>
    #include <bitset>

    #include <GL/glew.h>

    #include <glm/gtc/matrix_transform.hpp>
    #include <glm/gtc/type_ptr.hpp>

    namespace _GL4_Program_ID {
        typedef enum { Idle } Pick;
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
#define PIPELINE_H
#endif
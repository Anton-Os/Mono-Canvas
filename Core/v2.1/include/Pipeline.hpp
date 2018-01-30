#ifndef PIPELINE_H
    #include <cstdio>
    #include <vector>
    #include <string>
    #include <bitset>

    #include <GL/glew.h>

    #include <glm/gtc/matrix_transform.hpp>
    #include <glm/gtc/type_ptr.hpp>

    namespace _GL4_Shader_Stage {
        typedef enum { vert, frag, tesc, tese, geom, comp } Pick;
    }
#define PIPELINE_H
#endif
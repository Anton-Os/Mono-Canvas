#ifndef GEOMETRY_H
    #include <iostream>
    #include <vector>
    #include <array>
    #include <bitset>
    #include <algorithm>

    #include <GL/glew.h>

    #include <glm/gtc/matrix_transform.hpp>
    #include <glm/gtc/type_ptr.hpp>

    namespace _GL4_Vertex_Feed_ID {
        enum Pick { 
            pos_3f, 
            color_4f, 
            normal_3f, 
            texCoord_2f,
            frag_4f
        };
    }
#define GEOMETRY_H
#endif
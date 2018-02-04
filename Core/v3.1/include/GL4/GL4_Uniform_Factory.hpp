#ifndef PIPELINE_H
    #include "Pipeline.hpp"
#endif

#ifndef SCENE_ERROR_CODE_H
    #include "scene/ErrorCode.hpp"
#endif

#ifndef GL4_VERTEX_H
    #include "geometry/GL4_Vertex.hpp"
#endif

#ifndef GL4_UNIFORM_H
    #include "GL4/GL4_Uniform.hpp"
#endif

#define SHADER_UNIFORM_BASIC_COUNT 1
#define SHADER_UNIFORM_MATRIX_COUNT 1

#ifndef GL4_UNIFORM_FACTORY_H
    namespace _GL4_Uniform_Basic_ID {
        typedef enum { renderMode } Pick;
    }

    namespace _GL4_Uniform_Matrix_ID {
        typedef enum { mvpMatrix } Pick;
    }

    class GL4_Uniform_Factory {
    public:
        GL4_Uniform_Basic* get_uniform_b(GLuint uAttrib_arg);
        GL4_Uniform_Matrix* get_uniform_m(GLuint uAttrib_arg);
        void create();
    private:
        std::vector<GL4_Uniform_Basic> uniforms_b;
        std::bitset<SHADER_UNIFORM_BASIC_COUNT> uniform_b_bits;
        void append_uniform_b(GL4_Uniform_Basic* uniform_b_arg);
        std::vector<GL4_Uniform_Matrix> uniforms_m;
        std::bitset<SHADER_UNIFORM_MATRIX_COUNT> uniform_m_bits;
        void append_uniform_m(GL4_Uniform_Matrix* uniform_m_arg);
    };
#define GL4_UNIFORM_FACTORY_H
#endif
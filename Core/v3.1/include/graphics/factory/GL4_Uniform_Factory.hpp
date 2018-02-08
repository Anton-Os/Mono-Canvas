#define GEOMETRY_X
#ifndef GL4_API_COMMON_H
    #include "GL4_Api_Common.hpp"
#endif

#ifndef SCENE_ERROR_CODE_H
    #include "scene/ErrorCode.hpp"
#endif

#ifndef GL4_UNIFORM_H
    #include "graphics/GL4_Uniform.hpp"
#endif

#define SHADER_UNIFORM_BASIC_COUNT 1
#define SHADER_UNIFORM_MATRIX_COUNT 1

#ifndef GL4_UNIFORM_FACTORY_H
    class GL4_Uniform_Factory {
    public:
        GL4_Uniform_Basic_Format* get_uniform_b(_GL4_Uniform_Basic_ID::Pick uniform_b_arg);
        GL4_Uniform_Matrix_Format* get_uniform_m(_GL4_Uniform_Matrix_ID::Pick uniform_m_arg);
        void create();
    private:
        std::vector<GL4_Uniform_Basic_Format> mUniforms_b;
        std::bitset<SHADER_UNIFORM_BASIC_COUNT> mUniform_b_bits;
        void append_uniform_b(_GL4_Uniform_Basic_ID::Pick uniform_b_arg);
        std::vector<GL4_Uniform_Matrix_Format> mUniforms_m;
        std::bitset<SHADER_UNIFORM_MATRIX_COUNT> mUniform_m_bits;
        void append_uniform_m(_GL4_Uniform_Matrix_ID::Pick uniform_m_arg);
    };
#define GL4_UNIFORM_FACTORY_H
#endif
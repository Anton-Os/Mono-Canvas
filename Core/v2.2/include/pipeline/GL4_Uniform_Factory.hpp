#ifndef PIPELINE_H
    #include "Pipeline.hpp"
#endif

#ifndef SCENE_ERROR_CODE_H
    #include "scene/ErrorCode.hpp"
#endif

#ifndef GL4_UNIFORM_H
    #include "pipeline/GL4_Uniform.hpp"
#endif

#define SHADER_UNIFORM_BASIC_COUNT 1
#define SHADER_UNIFORM_MATRIX_COUNT 1

#ifndef GL4_SHADER_FACTORY_H
    namespace _GL4_Uniform_Basic_ID {
        typedef enum { renderMode } Pick;
    }

    namespace _GL4_Uniform_Matrix_ID {
        typedef enum { mvpMatrix } Pick;
    }

    class GL4_Uniform_Factory {
    public:
        GL4_Uniform_Factory(){ create(); }
        ~GL4_Uniform_Factory(){ 
	        delete[] uniforms_b;
	        delete[] uniforms_m;
        }
    private:
        GL4_Uniform_Basic* uniforms_b = new GL4_Uniform_Basic[SHADER_UNIFORM_BASIC_COUNT];
	    GL4_Uniform_Matrix* uniforms_m = new GL4_Uniform_Matrix[SHADER_UNIFORM_MATRIX_COUNT];
        void create();
    };
#define GL4_UNIFORM_FACTORY_H
#endif
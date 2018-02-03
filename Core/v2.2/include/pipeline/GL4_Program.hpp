#ifndef PIPELINE_H
    #include "Pipeline.hpp"
#endif

#ifndef SCENE_ERROR_CODE_H
    #include "scene/ErrorCode.hpp"
#endif

#ifndef GL4_UNIFORM_H
    #include "pipeline/GL4_Uniform.hpp"
#endif

#ifndef GL4_SHADER_H
    #include "pipeline/GL4_Shader.hpp"
#endif

#ifndef GL4_PROGRAM_H
    class GL4_Program {
    public:
        GL4_Program(){}
        GL4_Program(_GL4_Program_ID::Pick ID_arg){
            ID = ID_arg;
        }
        _GL4_Program_ID::Pick ID;
        void add_shader(GL4_Shader* shader_arg);
	    void add_uniform(GL4_Uniform_Basic* basic_arg);
	    void add_uniform(GL4_Uniform_Matrix* matrix_arg);
        GLuint get_progID(){ return progID; }
        void create();
    private:
        GLuint progID;
        std::bitset<6> stageBits;
        std::vector<GL4_Shader> shaders;
        std::vector<GL4_Uniform_Basic*> uniforms_b;       
        std::vector<GL4_Uniform_Matrix*> uniforms_m;
    };
#define GL4_PROGRAM_H
#endif
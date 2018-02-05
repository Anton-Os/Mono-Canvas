#ifndef PIPELINE_H
    #include "Pipeline.hpp"
#endif

#ifndef SCENE_ERROR_CODE_H
    #include "scene/ErrorCode.hpp"
#endif

#ifndef GL4_UNIFORM_H
    #include "GL4/GL4_Uniform.hpp"
#endif

#ifndef GL4_SHADER_H
    #include "GL4/GL4_Shader.hpp"
#endif

#ifndef GL4_PROGRAM_H
    class GL4_Program {
    public:
        GL4_Program(){}
        GL4_Program(_GL4_Program_ID::Pick ID_arg){
            mID = ID_arg;
        }
        _GL4_Program_ID::Pick mID;
        void add_shader(GL4_Shader* shader_arg);
	    void add_uniform(GL4_Uniform_Basic* basic_arg);
	    void add_uniform(GL4_Uniform_Matrix* matrix_arg);
        GLuint get_progID(){ return mProgID; }
        void create();
    private:
        bool immutable = false;
        GLuint mProgID;
        std::bitset<6> mStage_bits;
        std::vector<GL4_Shader> mShaders;
        std::vector<GL4_Uniform_Basic*> mUniforms_b;       
        std::vector<GL4_Uniform_Matrix*> mUniforms_m;
    };
#define GL4_PROGRAM_H
#endif
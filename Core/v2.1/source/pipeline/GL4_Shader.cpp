#include "pipeline/GL4_Shader.hpp"

void GL4_Shader::create(const std::string& fileName){
    std::string extension;
    switch(stage){
        case GL4_Shader_Stage::vert :
            extension = ".vert";
            break;
        case GL4_Shader_Stage::frag :
            extension = ".frag";
            break;
        case GL4_Shader_Stage::tesc :
            extension = ".tesc";
            break;
        case GL4_Shader_Stage::tese :
            extension = ".tese";
            break;
        case GL4_Shader_Stage::geom :
            extension = ".geom";
            break;
        case GL4_Shader_Stage::comp :
            extension = ".comp";
            break;
    }
    std::string shader_source = "Antons shader!";
    writeFile(fileName + extension, shader_source);
    ready = true;
}
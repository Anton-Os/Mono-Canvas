#include "GL4/GL4_Uniform.hpp"

char error_progID[] = "progID cannot be a null pointer";
char error_name[] = "name cannot be an empty string";
char error_initPhase[] = "init phase hasn't been triggered yet";
char error_formatSupport[] = "shader format not supported";

void GL4_Uniform::init(const GLuint* progID_arg){
    if(progID_arg == nullptr) logError(__FILE__, __LINE__, error_progID);
    if(name.empty()) logError(__FILE__, __LINE__, error_name);
    progID = progID_arg;
    initPhase = true;
}

/* void GL4_Uniform::init(const std::string& name_arg){
    if(progID == nullptr) logError(__FILE__, __LINE__, error_progID);
    if(name_arg.empty()) logError(__FILE__, __LINE__, error_name);
    name = name_arg;
    initPhase = true;
} */

void GL4_Uniform::init(_GL4_Shader_Format::Type shader_type_arg, const GLuint* progID_arg, const std::string& name_arg){
    shader_type = shader_type_arg;
    if(progID_arg == nullptr) logError(__FILE__, __LINE__, error_progID);
    if(name_arg.empty()) logError(__FILE__, __LINE__, error_name);
    progID = progID_arg;
    name = name_arg;
    initPhase = true;
}

void GL4_Uniform::get_loc(){
    if(!initPhase) logError(__FILE__, __LINE__, error_initPhase);
    location = glGetUniformLocation(*progID, name.c_str());
}

static void set_uniform_basic(GL4_Uniform_Basic::Type* type_arg, _GL4_Shader_Format::Type format_arg, void* data){
    switch(format_arg){
        case _GL4_Shader_Format::f :
            type_arg->f1 = *(GLfloat *)(data);
            break;
        case _GL4_Shader_Format::vec2 :
            type_arg->i1 = *(GLint *)(data);
            break;
        case _GL4_Shader_Format::vec3 :
            type_arg->ui1 = *(GLuint *)(data);
            break;
        default:
            logError(__FILE__, __LINE__, error_formatSupport);
            break;
    }
}

void GL4_Uniform_Basic::set(void* data){
    puts("Uniform Basic");
    set_uniform_basic(&type, shader_type, data);                               
    return;
}

void GL4_Uniform_Matrix::set(void* data){
    puts("Uniform Matrix");
    return;
}
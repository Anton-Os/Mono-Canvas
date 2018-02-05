#include "GL4/GL4_Uniform.hpp"

static char error_progID[] = "progID cannot be a null pointer";
static char error_name[] = "name cannot be an empty string";
static char error_initPhase[] = "init phase hasn't been triggered yet";
static char error_formatSupport[] = "shader format not supported";
static char warning_notFound[] = "shader program uniform not found";

void GL4_Uniform::init(const GLuint* progID_arg){
    if(progID_arg == nullptr) logError(__FILE__, __LINE__, error_progID);
    if(mName.empty()) logError(__FILE__, __LINE__, error_name);
    mProgID = progID_arg;
    mInitPhase = true;
}

void GL4_Uniform::init(_GL4_Shader_Format::Type shader_type_arg, const GLuint* progID_arg, const std::string& name_arg){
    mShader_type = shader_type_arg;
    if(progID_arg == nullptr) logError(__FILE__, __LINE__, error_progID);
    if(name_arg.empty()) logError(__FILE__, __LINE__, error_name);
    mProgID = progID_arg;
    mName = name_arg;
    mInitPhase = true;
}

void GL4_Uniform::get_loc(){
    if(!mInitPhase) logError(__FILE__, __LINE__, error_initPhase);
    mLocation = glGetUniformLocation(*mProgID, mName.c_str());
    logWarning(__FILE__, __LINE__, warning_notFound);
}

static void set_uniform_basic(GL4_Uniform_Basic::Type* type_arg, _GL4_Shader_Format::Type format_arg, void* data, GLint location_arg){
    switch(format_arg){
        case _GL4_Shader_Format::f :
            type_arg->f1 = *(GLfloat *)(data);
            glUniform1f(location_arg, type_arg->f1);
            break;
        case _GL4_Shader_Format::vec2 :
            type_arg->i1 = *(GLint *)(data);
            glUniform1i(location_arg, type_arg->i1);
            break;
        case _GL4_Shader_Format::vec3 :
            type_arg->ui1 = *(GLuint *)(data);
            glUniform1ui(location_arg, type_arg->ui1);
            break;
        default:
            logError(__FILE__, __LINE__, error_formatSupport);
            break;
    }
}

void GL4_Uniform_Basic::set(void* data_arg){
    puts("Uniform Basic");
    set_uniform_basic(&mType, mShader_type, data_arg, mLocation);         
    return;
}

void GL4_Uniform_Matrix::set(void* data){
    puts("Uniform Matrix");
    return;
}
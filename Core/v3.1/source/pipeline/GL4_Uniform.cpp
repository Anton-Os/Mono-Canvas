#include "graphics/GL4_Uniform.hpp"

static char error_progID[] = "progID cannot be a null pointer";
static char error_name[] = "name cannot be an empty string";
static char error_unready[] = "uniform hasnt been properly initialized";
static char error_formatSupport[] = "shader format not supported";
static char warning_notFound[] = "shader program uniform not found";

void GL4_Uniform::init(const GLuint* progID_arg){
    if(progID_arg == nullptr) logError(__FILE__, __LINE__, error_progID);
    if(mName.empty()) logError(__FILE__, __LINE__, error_name);
    mProgID = progID_arg;
    mReady = true;
}

void GL4_Uniform::get_loc(){
    if(!mReady) logError(__FILE__, __LINE__, error_unready);
    mLocation = glGetUniformLocation(*mProgID, mName.c_str());
    logWarning(__FILE__, __LINE__, warning_notFound);
}

static void set_uniform_basic(GL4_Uniform_Basic::Type* type_arg, _GL4_Uniform_Basic_Format::Pick format_arg, void* data, GLint location_arg){
    switch(format_arg){
        case _GL4_Uniform_Basic_Format::f1 :
            type_arg->f1 = *(GLfloat *)(data);
            glUniform1f(location_arg, type_arg->f1);
            break;
        case _GL4_Uniform_Basic_Format::i1 :
            type_arg->i1 = *(GLint *)(data);
            glUniform1i(location_arg, type_arg->i1);
            break;
        case _GL4_Uniform_Basic_Format::ui1 :
            type_arg->ui1 = *(GLuint *)(data);
            glUniform1ui(location_arg, type_arg->ui1);
            break;
        default:
            logError(__FILE__, __LINE__, error_formatSupport);
            break;
    }
}

void GL4_Uniform_Basic::set(void* data_arg){
    if(!mReady) logError(__FILE__, __LINE__, error_unready);
    set_uniform_basic(&mType, mFormat, data_arg, mLocation);         
    return;
}

void GL4_Uniform_Matrix::set(void* data){
    if(!mReady) logError(__FILE__, __LINE__, error_unready);
    return;
}
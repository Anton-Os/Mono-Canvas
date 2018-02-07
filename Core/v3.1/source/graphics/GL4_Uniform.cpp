#include "graphics/GL4_Uniform.hpp"

static char error_progID[] = "progID cannot be a null pointer";
static char error_name[] = "name cannot be an empty string";
static char error_unready[] = "uniform hasnt been properly initialized";
static char error_formatSupport[] = "shader format not supported";
static char warning_notFound[] = "shader program uniform not found";

GLint GL4_Uniform::get_loc(const std::string& name_arg){
    if(!mReady) logError(__FILE__, __LINE__, error_unready);
    GLint location = glGetUniformLocation(*mProgID, name_arg.c_str());
    if(mLocation <= 0) logWarning(__FILE__, __LINE__, warning_notFound);
    return location;
}

void GL4_Uniform_Basic::init(const GLuint* progID_arg, const GL4_Uniform_Basic_Format* format_arg){
    mProgID = progID_arg;
    mFormat = format_arg;
    mReady = true;
    return;
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
    set_uniform_basic(&mType, mFormat->mPick, data_arg, mLocation);         
    return;
}

void GL4_Uniform_Matrix::init(const GLuint* progID_arg, const GL4_Uniform_Matrix_Format* format_arg){
    mProgID = progID_arg;
    mFormat = format_arg;
    mReady = true;
    return;
}

void GL4_Uniform_Matrix::set(void* data){
    if(!mReady) logError(__FILE__, __LINE__, error_unready);
    return;
}
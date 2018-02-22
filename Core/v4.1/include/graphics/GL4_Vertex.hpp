#define PIPELINE_X
#ifndef GL4_API_COMMON_H
    #include "GL4_Api_Common.hpp"
#endif

#ifndef SCENE_ERROR_CODE_H
    #include "scene/ErrorCode.hpp"
#endif

#ifndef GL4_VERTEX_H
    namespace _vaoPtrModes {
        enum Pick  {
            Default,
            Integral,
            Double
        };
    }

    namespace _GL4_Shader_Format_ID {
        enum Type {
            f,
            i,
            ui,
            vec2,
            vec3,
            vec4,
            dvec2,
            dvec3,
            dvec4
        };
    }

    class GL4_Vertex_Format {
    public:
		GL4_Vertex_Format(){}
        GL4_Vertex_Format(_GL4_Vertex_Feed_ID::Pick feedID_arg, GLint count_arg, GLsizei size_arg, GLenum type_arg, GLboolean normalized_arg, _vaoPtrModes::Pick vaoPtrMode_arg, _GL4_Shader_Format_ID::Type shaderFormat_arg){
			mFeedID = feedID_arg;
			mCount = count_arg;
			mSize = size_arg;
			mType = type_arg;
			mNormalized = normalized_arg;
			mVaoPtrMode = vaoPtrMode_arg;
			mShaderFormat = shaderFormat_arg;
		}
		/* GL4_Vertex_Format(GL4_Vertex_Format* vertexFormat_arg){
			mFeedID = *(vertexFormat_arg->mFeedID_ptr);
			mCount = *(vertexFormat_arg->mCount_ptr);
			mSize = *(vertexFormat_arg->mSize_ptr);
			mType = *(vertexFormat_arg->mType_ptr);
			mNormalized = *(vertexFormat_arg->mNormalized_ptr);
			mVaoPtrMode = *(vertexFormat_arg->mVaoPtrMode_ptr);
			mShaderFormat = *(vertexFormat_arg->mShaderFormat_ptr);
		} */
		const _GL4_Vertex_Feed_ID::Pick *const mFeedID_ptr = &mFeedID;
		const GLint *const mCount_ptr = &mCount;
		const GLsizei *const mSize_ptr = &mSize;
		const GLenum *const mType_ptr = &mType;
		const GLboolean *const mNormalized_ptr = &mNormalized;
		const _vaoPtrModes::Pick *const mVaoPtrMode_ptr = &mVaoPtrMode;
		const _GL4_Shader_Format_ID::Type *const mShaderFormat_ptr = &mShaderFormat;
    private:
        _GL4_Vertex_Feed_ID::Pick mFeedID;
        GLint mCount;
		GLsizei mSize;
        GLenum mType;
        GLboolean mNormalized = false;
        _vaoPtrModes::Pick mVaoPtrMode;
        _GL4_Shader_Format_ID::Type mShaderFormat;
    };

    class GL4_Vertex_Feed {
    public: 
	GL4_Vertex_Feed(const GLuint* buffer_arg, const GL4_Vertex_Format* vertexFormat_arg){
	    mBuffer = buffer_arg;
	    mFormat = vertexFormat_arg;
	}
	void enable(){
	    if(*(mFormat->mVaoPtrMode_ptr) == _vaoPtrModes::Default) glVertexAttribPointer(*(mFormat->mFeedID_ptr), *(mFormat->mCount_ptr), *(mFormat->mType_ptr), *(mFormat->mNormalized_ptr), 0, nullptr);
	    else if(*(mFormat->mVaoPtrMode_ptr) == _vaoPtrModes::Integral) glVertexAttribIPointer(*(mFormat->mFeedID_ptr), *(mFormat->mCount_ptr), *(mFormat->mType_ptr), 0, nullptr);
	    else if(*(mFormat->mVaoPtrMode_ptr) == _vaoPtrModes::Double) glVertexAttribLPointer(*(mFormat->mFeedID_ptr), *(mFormat->mCount_ptr), *(mFormat->mType_ptr), 0, nullptr);
	    glEnableVertexAttribArray(*(mFormat->mFeedID_ptr));
	    mActive = true;
	}
	void disable(){ 
	    glDisableVertexAttribArray(*(mFormat->mFeedID_ptr));
	    mActive = false;
	}
    private:
		const GLuint* mBuffer;
		const GL4_Vertex_Format* mFormat;
		GLboolean mActive = false;
    };

    class GL4_Shader_Vertex_Format {
    public:
	GL4_Shader_Vertex_Format(const GL4_Vertex_Format* vertexFormat_arg){
	    mFeedID = (GLuint)(*(vertexFormat_arg->mFeedID_ptr));
	    mFormat = vertexFormat_arg;
	}
	GL4_Shader_Vertex_Format(GLuint feedID_arg, const GL4_Vertex_Format* vertexFormat_arg){
	    mFeedID = feedID_arg;
	    mFormat = vertexFormat_arg;
	}
    private:
	GLuint mFeedID;
	const GL4_Vertex_Format* mFormat;
    };

#define GL4_VERTEX_H
#endif

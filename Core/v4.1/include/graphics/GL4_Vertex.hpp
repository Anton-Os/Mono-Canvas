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
		_GL4_Vertex_Feed_ID::Pick get_feedID() const { return mFeedID; }
		GLint get_count() const { return mCount; }
		GLsizei get_size() const { return  mSize; }
		GLenum get_type() const { return mType; }
		GLboolean get_normalized() const { return mNormalized; }
		_vaoPtrModes::Pick get_vaoPtrMode() const { return mVaoPtrMode; }
		_GL4_Shader_Format_ID::Type get_shaderFormat() const { return mShaderFormat; }
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
		GLuint get_buffer(){ return *mBuffer; }

    private:
		const GLuint* mBuffer;
		const GL4_Vertex_Format* mFormat;
		GLboolean mActive = false;
    };

    class GL4_Shader_Vertex_Format {
    public:
		GL4_Shader_Vertex_Format(const GL4_Vertex_Format* vertexFormat_arg){
			mFeedID = (GLuint)(vertexFormat_arg->get_feedID());
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

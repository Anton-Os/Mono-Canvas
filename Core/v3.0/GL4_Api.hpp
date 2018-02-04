#ifndef GL4_API_COMMON_H
    #include <cstdlib>
    #include <vector>
    #include <string>
    #include <bitset>
    #include <stack>
    #include <algorithm>

    #include <GL/glew.h>

    #include <glm/gtc/matrix_transform.hpp>
    #include <glm/gtc/type_ptr.hpp>

    namespace _GL4_Vertex_Feed {
        typedef enum { pos_3f, color_4f, normal_3f, texCoord_2f } Pick;
    }

    namespace _GL4_Program_ID {
        typedef enum { Idle } Pick;
    }

    namespace _GL4_Shader_Stage {
        typedef enum { vert, frag, tesc, tese, geom, comp } Pick;
    }

    // from GL4_Vertex.hpp

    namespace _GL4_Shader_Format {
        enum Type {
            f,
            i,
            ui,
            vec2,
            vec3,
            vec4,
            dvec2,
            dvec3,
            dvec4,
            // Matrix
            mat2,
            mat3,
            mat4
        };
    }

    namespace _vaoPtrModes {
        enum Modes {
            Default,
            Integral,
            Double
        };
    }

    struct GL4_Vertex_Format {
        GL4_Vertex_Format(){}
        GL4_Vertex_Format(GLuint f, GLint c, GLenum trg, GLenum typ, GLenum u, GLboolean n, GLint v, _GL4_Shader_Format::Type st){ 
            feedID = f;
            count = c;
            target = trg;
            type = typ;
            usage = u;
            normalized = n;
            vaoPtrMode = v;
            shader_type = st;
        }
        GLint feedID;
        GLint count;
        GLenum target;
        GLenum type;
        GLenum usage;
        GLboolean normalized;
        GLint vaoPtrMode;
        _GL4_Shader_Format::Type shader_type;
    };

    struct GL4_Vertex {
        ~GL4_Vertex(){ glDeleteBuffers(1, &buffer); }
        GLuint buffer = 0;
        const GL4_Vertex_Format* format;
    };

    class GL4_Shader_Vertex_Format {
    public:
        GL4_Shader_Vertex_Format(const _GL4_Shader_Format::Type* shader_type_arg){
            type = shader_type_arg;
        }
        GL4_Shader_Vertex_Format(const _GL4_Shader_Format::Type* shader_type_arg, GLint feedID_arg){
            feedID = feedID_arg;
            overwrite = true;
            type = shader_type_arg;
        }
        bool overwrite = false;
    private:
        GLint feedID;
        const _GL4_Shader_Format::Type* type;
    };

    // From GL4_Shader.hpp

    struct GL4_Shader {
        GL4_Shader(const std::string& path_arg, _GL4_Shader_Stage::Pick stage_arg){
            stage = stage_arg;
            filePath = path_arg;
            shaderID = compileShader(filePath);
        }
        GLuint shaderID;
        std::string filePath;
        _GL4_Shader_Stage::Pick stage;
        std::vector<GL4_Shader_Vertex_Format> inputs;
        std::vector<GL4_Shader_Vertex_Format> outputs;
    };

    // From GL4_Uniform.hpp

    class GL4_Uniform {
    public:
        GL4_Uniform(){}
        GL4_Uniform(_GL4_Shader_Format::Type shader_type_arg, const std::string& name_arg){
            shader_type = shader_type_arg;
            name = name_arg;
        }
        GL4_Uniform(_GL4_Shader_Format::Type shader_type_arg, const std::string& name_arg, const GLuint* progID_arg){
            init(shader_type_arg, progID_arg, name_arg);
            get_loc();
        }
        void init(const GLuint* progID_arg);
        void get_loc();
    protected:
        void init(_GL4_Shader_Format::Type shader_type_arg, const GLuint* progID_arg, const std::string& name_arg);
        _GL4_Shader_Format::Type shader_type;
        bool initPhase = false;
        std::string name;
        const GLuint* progID = nullptr;
        GLint location;
    };

    struct GL4_Uniform_Basic : public GL4_Uniform {
        GL4_Uniform_Basic(){}
        GL4_Uniform_Basic(_GL4_Shader_Format::Type shader_type_arg, const std::string& name_arg) : GL4_Uniform(shader_type_arg, name_arg){}
        void set(void* data);
        union Type {
            GLfloat f1;
            GLfloat f2[2];
            GLfloat f3[3];
            GLfloat f4[4];
            GLfloat* fv;
            GLint i1;
            GLint i2[2];
            GLint i3[3];
            GLint i4[4];
            GLint* iv;
            GLuint ui1;
            GLuint ui2[2];
            GLuint ui3[3];
            GLuint ui4[4];
            GLuint* uiv;
        } type;
    };

    struct GL4_Uniform_Matrix : public GL4_Uniform {
	    GL4_Uniform_Matrix(){}
        GL4_Uniform_Matrix(_GL4_Shader_Format::Type shader_type_arg, const std::string& name_arg) : GL4_Uniform(shader_type_arg, name_arg){}
        void set(void* data);
        union Type {
            glm::mat2 m2;
            glm::mat3 m3;
            glm::mat4 m4;
        } type;
    };

    // from GL4_Program.hpp

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
        bool immutable = false;
        GLuint progID;
        std::bitset<6> stage_bits;
        std::vector<GL4_Shader> shaders;
        std::vector<GL4_Uniform_Basic*> uniforms_b;       
        std::vector<GL4_Uniform_Matrix*> uniforms_m;
    };

    // from GL4_Vertex_Factory.hpp

    #define VERTEX_FACTORY_ENTRY_COUNT 4
    
    class GL4_Vertex_Factory {
    public:
        GL4_Vertex_Format* get_format(_GL4_Vertex_Feed::Pick pick_arg) ;
        _GL4_Shader_Format::Type* get_shader_format(_GL4_Vertex_Feed::Pick pick_arg);
        void create();
    private:
        std::bitset<VERTEX_FACTORY_ENTRY_COUNT> format_bits;
        std::vector<GL4_Vertex_Format> formats;
        void append_format(_GL4_Vertex_Feed::Pick pick_arg);
    };

    // fron GL4_Uniform_Factory.hpp

    #define SHADER_UNIFORM_BASIC_COUNT 1
    #define SHADER_UNIFORM_MATRIX_COUNT 1

    namespace _GL4_Uniform_Basic_ID {
        typedef enum { renderMode } Pick;
    }

    namespace _GL4_Uniform_Matrix_ID {
        typedef enum { mvpMatrix } Pick;
    }

    class GL4_Uniform_Factory {
    public:
        GL4_Uniform_Basic* get_uniform_b(GLuint uAttrib_arg);
        GL4_Uniform_Matrix* get_uniform_m(GLuint uAttrib_arg);
        void create();
    private:
        std::vector<GL4_Uniform_Basic> uniforms_b;
        std::bitset<SHADER_UNIFORM_BASIC_COUNT> uniform_b_bits;
        void append_uniform_b(GL4_Uniform_Basic* uniform_b_arg);
        std::vector<GL4_Uniform_Matrix> uniforms_m;
        std::bitset<SHADER_UNIFORM_MATRIX_COUNT> uniform_m_bits;
        void append_uniform_m(GL4_Uniform_Matrix* uniform_m_arg);
    };

    // from GL4_Shader_Factory.hpp

    #define SHADER_FACTORY_PROG_COUNT 1

    class GL4_Shader_Factory {
    public:
        GL4_Shader_Factory(const std::string& parentDir_arg, GL4_Vertex_Factory* factory_arg){ 
            parentDir = parentDir_arg;
            vertexFactory = factory_arg;
        }
        GL4_Program get_program(_GL4_Program_ID::Pick progID_arg);
        void create();
    private:
        std::string parentDir;
        GL4_Vertex_Factory* vertexFactory;
        std::vector<GL4_Program> programs;
        std::bitset<SHADER_FACTORY_PROG_COUNT> program_bits;

    };

    // from GL4_Mesh.hpp

    class GL4_Mesh {
    public:
        GL4_Mesh(GLuint v){
            vertexCount = v;
            quill.init(&ready, &order.isIdx, &VAO, &vertexCount, &order.indexCount);
        }
        struct GL4_Mesh_Order {
            GLboolean isIdx = false;
            GLuint indexCount;
            GLuint buffer;
            GLenum target = GL_ELEMENT_ARRAY_BUFFER;
            GLenum type = GL_UNSIGNED_INT;
            void feed(const void* data, size_t size, GLuint count);
        } order;
        class GL4_Mesh_Quill {
        public:
            GLenum mode = GL_TRIANGLES;
            void init(const GLboolean* fed, const GLboolean* idx, const GLuint* o, const GLuint* v, const GLuint* i);
            void unordered_draw();
            void unordered_drawFixed(GLuint count);
            void unordered_drawPart(GLuint part, GLuint whole);
            void ordered_draw();
            void ordered_drawFixed(GLuint count);
            void ordered_drawPart(GLuint part, GLuint whole);
        private:
            GLboolean initPhase = false;
            const GLboolean* isFedPtr = nullptr;
            const GLboolean* isIdxPtr = nullptr;
            const GLuint* vaoPtr = nullptr;
            const GLuint* vertexCountPtr = nullptr;
            const GLuint* indexCountPtr = nullptr;
        } quill;
        void init();
        void add_feed(const GL4_Vertex_Format* vertexFeed);
        void del_feed(GLuint vAttrib);
        void set_feed(GLuint vAttrib, const void* data, size_t size);
    private:
        GLushort fin_counter = 0;
        GLboolean ready = false;
        std::vector<GL4_Vertex> feeds;
        GLuint VAO;
        GLboolean initPhase = false;
        GLuint vertexCount;
    };
#define GL4_API_COMMON_H
#endif
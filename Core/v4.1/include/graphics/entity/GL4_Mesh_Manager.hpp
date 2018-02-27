#ifndef GL4_API_COMMON_H
    #include "GL4_Api_Common.hpp"
#endif

#ifndef SCENE_ERROR_CODE_H
    #include "scene/ErrorCode.hpp"
#endif

#ifndef GL4_VERTEX_H
    #include "graphics/GL4_Vertex.hpp"
#endif

#ifndef GL4_VERTEX_REGISTRY_H
    #include "graphics/factory/GL4_Vertex_Registry.hpp"
#endif

#ifndef GL4_MESH_H
    #include "graphics/entity/GL4_Mesh.hpp"
#endif

#ifndef GL4_MESH_MANAGER_H
    class GL4_Mesh_Manager {
    public:
        GL4_Mesh_Manager(GLuint VAO_count_arg, GLuint VBO_count_arg);
        GL4_Mesh* add_mesh(GLuint vertexCount_arg);
    private:
        GLuint mVAO_count;
        GLuint mVAO_used = 0;
        std::vector<GLuint> mVAOs;
        GLuint mVBO_count;
        GLuint mVBO_used = 0;
        std::vector<GLuint> mVBOs;
        std::vector<GL4_Mesh> mMeshes;
    };
#define GL4_MESH_MANAGER_H
#endif

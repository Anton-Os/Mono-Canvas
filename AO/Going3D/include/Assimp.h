#include "Common.h"

#include <vector>

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>       // Output data structure
#include <assimp/postprocess.h> // Post processing flags

// From Mesh.cpp

struct Point {
    std::array<GLfloat, 3> pos;
    std::array<GLubyte, 4> color;
    std::array<GLfloat, 2> texCoord;
    std::array<GLfloat, 3> normal;
};

struct Texture {
    GLuint texId;
    std::string type;
};

class Mesh {
public:
    GLuint shaderProgId;
    std::vector<Point> points;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;
    Mesh(GLuint shaderProgId, std::vector<Point>, std::vector<GLuint>, std::vector<Texture>);
    void renderMesh();

private:
    unsigned int VAO, VBO, EBO;
    void loadMesh();
    void deleteMesh();
};

// From Model3D.cpp

class Model3D{

public:
    std::string modelPath;
    const aiScene* currentScene;
    Model3D(std::string &modelPath);
    void renderScene();

private:
    std::vector<Mesh> existingMeshes;
    void loadModel();
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(
        aiMaterial* material, 
        aiTextureType materialType, 
        std::string materialTypeName
    );
    GLuint shaderProgId; // MUST BE INHERITED FROM CURRENT MESH
    GLuint surfaceRenderMode; // AO
    GLubyte genRandomColorAttrib();// AO
};
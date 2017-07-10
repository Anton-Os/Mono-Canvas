#include "Assimp.h"

/* class Model3D{

class Model3D{

public:
    const aiScene* currentScene;
    Model3D(std::string &modelPath);
    void renderScene(GLuint shaderId);

private:
    std::vector<Mesh> existingMeshes;
    void loadModel(std::string &modelPath);
    void processNode(aiNode *node, const aiScene* scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(
        aiMaterial* material, 
        aiTextureType materialType, 
        std::string materialTypeName
    );

}; */

void Model3D::renderScene(){
    for(unsigned int i = 0; i < existingMeshes.size(); i++){
        existingMeshes[i].renderMesh();
    }
}

void Model3D::loadModel(){
    Assimp::Importer modelImporter;
    const aiScene* currentScene = modelImporter.ReadFile(
        modelPath,
        aiProcess_Triangulate | // Converts to triangles if not done so
        aiProcess_FlipUVs | // Flips texture coordinates on Y axis
        aiProcess_GenNormals // Creates normals if model data does not contain
    );

    if(! currentScene || currentScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || ! currentScene->mRootNode){
        std::cout << "Assimp Error " << modelImporter.GetErrorString() << std::endl;
        return;
    }

    processNode(currentScene->mRootNode, currentScene);
}

void Model3D::processNode(aiNode *node, const aiScene *scene){
    // Process the meshes belonging to node
    for(unsigned int i = 0; i < node->mNumMeshes; i++){
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        existingMeshes.push_back(processMesh(mesh, currentScene));
    }

    // Recursive call to process child nodes and process meshes if any are present
    for(unsigned int i = 0; i < node->mNumChildren; i++){
        processNode(node->mChildren[i], scene);
    }

    // Ends only when root node and all child nodes have had their meshes processed
}

Mesh Model3D::processMesh(aiMesh *mesh, const aiScene *scene){
    std::vector<Point> meshPoints;
    std::vector<GLuint> meshIndices;
    std::vector<Texture> meshTextures;

    // Processes all attributes belonging to given mesh (points, indices, textures)
    for(unsigned int i = 0; i < mesh->mNumVertices; i++){
        Point myPoint;
        std::array<GLfloat, 3> currentVertexPos;
        // GLubyte currentVertexColor[4];
        std::array<GLubyte, 4> currentVertexColor = {255, 255, 255, 255};
        std::array<GLfloat, 2> currentVertexUV;
        std::array<GLfloat, 3> currentVertexNorm;
        
        currentVertexPos[0] = mesh->mVertices[i].x;
        currentVertexPos[1] = mesh->mVertices[i].y;
        currentVertexPos[2] = mesh->mVertices[i].z;

        currentVertexNorm[0] = mesh->mNormals[i].x;
        currentVertexNorm[1] = mesh->mNormals[i].y;
        currentVertexNorm[2] = mesh->mNormals[i].z;

        // Assimp allows up to 8 texture coordinates per vertex but we need first 2
        if(mesh->mTextureCoords[0]){ // Do they even exist?
            currentVertexNorm[0] = mesh->mTextureCoords[0][i].x;
            currentVertexNorm[1] = mesh->mTextureCoords[0][i].y;
            surfaceRenderMode = 0;
        } else {
            currentVertexUV[0] = 0.0f;
            currentVertexUV[1] = 0.0f;
            surfaceRenderMode = 1;
        }

        myPoint.pos = currentVertexPos;
        myPoint.color = currentVertexColor;
        myPoint.texCoord = currentVertexUV;
        myPoint.normal = currentVertexNorm;
        
        meshPoints.push_back(myPoint);
    } // LEFT OFF HERE

    if(mesh->mMaterialIndex >= 0){

    }

    return Mesh(shaderProgId, meshPoints, meshIndices, meshTextures);
}

GLubyte genRandomColorAttrib(){
    int colorAttrib = std::rand() % 255;
    return GLubyte(colorAttrib);
}





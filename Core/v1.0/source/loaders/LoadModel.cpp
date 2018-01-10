#include "Loaders.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

glm::mat4 convertToGLMMat4(aiMatrix4x4 from) {
	glm::mat4 to;
	to[0][0] = from.a1; to[1][0] = from.a2;	to[2][0] = from.a3; to[3][0] = from.a4;
	to[0][1] = from.b1; to[1][1] = from.b2;	to[2][1] = from.b3; to[3][1] = from.b4;
	to[0][2] = from.c1; to[1][2] = from.c2;	to[2][2] = from.c3; to[3][2] = from.c4;
	to[0][3] = from.d1; to[1][3] = from.d2;	to[2][3] = from.d3; to[3][3] = from.d4;
	return to;
}

unsigned computeIdxCount(aiMesh* mesh){
    unsigned indexCount;
    for(unsigned faceElem = 0; faceElem < mesh->mNumFaces; faceElem++)
        indexCount += mesh->mFaces[faceElem].mNumIndices;
    return indexCount;
}

void extractMesh(GL4_Tree* tree, const aiScene* scene, aiNode* currentNode){
    for(unsigned meshElem = 0; meshElem < currentNode->mNumMeshes; meshElem++){
        vertexFeed vFeed;
        glm::mat4 matrix = convertToGLMMat4(currentNode->mTransformation);
        vFeed.pos.resize(scene->mMeshes[*(currentNode->mMeshes + meshElem)]->mNumVertices * 3);
        for(unsigned vAttribElem = 0; vAttribElem < scene->mMeshes[currentNode->mMeshes[meshElem]]->mNumVertices; vAttribElem++){
            vFeed.pos[vAttribElem * 3] = scene->mMeshes[currentNode->mMeshes[meshElem]]->mVertices[vAttribElem].x;
            vFeed.pos[vAttribElem * 3 + 1] = scene->mMeshes[currentNode->mMeshes[meshElem]]->mVertices[vAttribElem].y;
            vFeed.pos[vAttribElem * 3 + 2] = scene->mMeshes[currentNode->mMeshes[meshElem]]->mVertices[vAttribElem].z;
        }
        tree->addNode(&matrix, &vFeed);
    }
}

void extractMeshIdx(GL4_Tree* tree, const aiScene* scene, aiNode* currentNode){
    for(unsigned meshElem = 0; meshElem < currentNode->mNumMeshes; meshElem++){
        vertexFeedIdx vFeed;
        glm::mat4 matrix = convertToGLMMat4(currentNode->mTransformation);
        vFeed.pos.resize(scene->mMeshes[currentNode->mMeshes[meshElem]]->mNumVertices * 3);
        for(unsigned vAttribElem = 0; vAttribElem < scene->mMeshes[currentNode->mMeshes[meshElem]]->mNumVertices; vAttribElem++){
            vFeed.pos[vAttribElem * 3] = scene->mMeshes[currentNode->mMeshes[meshElem]]->mVertices[vAttribElem].x;
            vFeed.pos[vAttribElem * 3 + 1] = scene->mMeshes[currentNode->mMeshes[meshElem]]->mVertices[vAttribElem].y;
            vFeed.pos[vAttribElem * 3 + 2] = scene->mMeshes[currentNode->mMeshes[meshElem]]->mVertices[vAttribElem].z;
        }
        vFeed.idx.resize(computeIdxCount(scene->mMeshes[currentNode->mMeshes[meshElem]]));
        unsigned idxOffset = 0;
        for(unsigned faceElem = 0; faceElem < scene->mMeshes[currentNode->mMeshes[meshElem]]->mNumFaces; faceElem++)
            for(unsigned idxElem = 0; idxElem < scene->mMeshes[currentNode->mMeshes[meshElem]]->mFaces[faceElem].mNumIndices; idxElem++){
                vFeed.idx[idxOffset] = scene->mMeshes[currentNode->mMeshes[meshElem]]->mFaces[faceElem].mIndices[idxElem];
                idxOffset++;
            }
        tree->addNode(&matrix, &vFeed);
    }
}

void iterateNodes(std::stack<aiNode*>* nodes, aiNode* parentNode){
    nodes->pop();
    if(parentNode->mNumChildren > 0){
        for(unsigned nodeElem = 0; nodeElem < parentNode->mNumChildren; nodeElem++)
            nodes->push(parentNode->mChildren[nodeElem]);
    }
}

void assimpImport(std::string filepath, GL4_Tree* tree){
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filepath.c_str(),
            aiProcess_CalcTangentSpace       | 
            aiProcess_Triangulate            |
            aiProcess_JoinIdenticalVertices  |
            aiProcess_SortByPType |
            aiProcess_GenNormals |
            aiProcess_PreTransformVertices
    );

    aiNode* rootNode = scene->mRootNode;
    std::stack<aiNode*> childNodes;
    childNodes.push(rootNode);
    while(! childNodes.empty()){
        aiNode* currentNode = childNodes.top();
        extractMeshIdx(tree, scene, currentNode);
        iterateNodes(&childNodes, currentNode);
    }
}

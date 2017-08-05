#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace ImportCtrl {
    enum ImportCtrl {
        color,
        texCoord,
        drawable
    };
};

struct MeshBlock {
    aiVector3D pos;
    aiColor4D color;
    aiVector3D texCoord;
    aiVector3D normal;
};

struct AssimpComposite {
    aiNode* currentNode;
    std::vector<MeshBlock> modelMeshes;
    std::vector<unsigned int> faceIndex;
    aiMatrix4x4 relTransform;

    std::bitset<3> renderParams;
};

int assimpImportCPP(const std::string &pFile, std::vector<AssimpComposite>* MPerComponent);

// From ProcessData.cpp

namespace CONTEXT {
    enum CONTEXT {
        Default
    };
};

int processData(std::vector<AssimpComposite>* MPerComponent, enum CONTEXT::CONTEXT);
#include "Feeds.h"
#include "geometry/polyform/Polyform_Tilemap.hpp"

namespace Polyform_Tilemap_Eq {
    unsigned gridPosCount;
    unsigned perVertex = 3;
    float* gridData;

    void mtxSequence(std::vector<glm::mat4>* matrices){
        matrices->resize(gridPosCount);
        float currentX;
        float currentY;
        float currentZ;
        for(unsigned gridPosElem = 0; gridPosElem < gridPosCount; gridPosElem++){
            currentX = *(gridData + gridPosElem * perVertex);
            currentY = *(gridData + gridPosElem * perVertex + 1);
            currentZ = *(gridData + gridPosElem * perVertex + 2);
            matrices->at(gridPosElem) = glm::translate(glm::mat4(1), glm::vec3(currentX, currentY, currentZ));
        }
    }

    void createTile(float tileX, float tileY, vertexFeed* vFeed){
        vFeed->pos.resize(12);
        vFeed->pos.at(0) = -1 * tileX * 0.5f;
        vFeed->pos.at(1) = -1 * tileY * 0.5f;
        vFeed->pos.at(2) = 0.0f;
        vFeed->pos.at(3) = tileX * 0.5f;
        vFeed->pos.at(4) = -1 * tileY * 0.5f;
        vFeed->pos.at(5) = 0.0f;
        vFeed->pos.at(6) = -1 * tileX * 0.5f;
        vFeed->pos.at(7) = tileY * 0.5f;
        vFeed->pos.at(8) = 0.0f;
        vFeed->pos.at(9) = tileX * 0.5f;
        vFeed->pos.at(10) = tileY * 0.5f;
        vFeed->pos.at(11) = 0.0f;
    }
}

void Polyform_Tilemap::create(GL4_PolyClone* polyClone, Polyform_Grid* polyGrid){
    GL4_PolyFunc polyFunc;
    polyGrid->create(&polyFunc);
    vertexFeed vFeed;
    polyFunc.dump(&vFeed);
    Polyform_Tilemap_Eq::gridPosCount = vFeed.pos.size() / vFeed.perVertex;
    Polyform_Tilemap_Eq::perVertex = vFeed.perVertex;
    Polyform_Tilemap_Eq::gridData = vFeed.pos.data();
    polyClone->mtxSequence = Polyform_Tilemap_Eq::mtxSequence;
    polyClone->gen_mtx();

    Polyform_Grid_Meta polyGridMeta;
    polyGrid->exportMeta(&polyGridMeta);
    vertexFeed tile;
    float tileX = polyGridMeta.width / polyGridMeta.xCount;
    float tileY = polyGridMeta.height / polyGridMeta.yCount;
    Polyform_Tilemap_Eq::createTile(tileX, tileY, &tile);
    polyClone->createXI(&tile);
}
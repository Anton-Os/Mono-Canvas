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

    void createTile(float tileX, float tileY, vertexFeedIdx* vFeed){
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

        vFeed->idx.resize(6);
        vFeed->idx.at(0) = 0;
        vFeed->idx.at(1) = 1;
        vFeed->idx.at(2) = 2;
        vFeed->idx.at(3) = 3;
        vFeed->idx.at(4) = 1;
        vFeed->idx.at(5) = 2;
    }
}

void Polyform_Tilemap::create(GL4_PolyClone* polyClone, Polyform_Grid* polyGrid){
    GL4_PolyFunc polyFunc;
    polyGrid->create(&polyFunc);
    vertexFeed vFeed;
    polyFunc.dump(&vFeed);
    Polyform_Tilemap::states.resize(vFeed.pos.size() / vFeed.perVertex);
    Polyform_Tilemap_Eq::gridPosCount = vFeed.pos.size() / vFeed.perVertex;
    Polyform_Tilemap_Eq::perVertex = vFeed.perVertex;
    Polyform_Tilemap_Eq::gridData = vFeed.pos.data();
    polyClone->mtxSequence = Polyform_Tilemap_Eq::mtxSequence;
    polyClone->gen_mtx();

    Polyform_Grid_Meta polyGridMeta;
    polyGrid->exportMeta(&polyGridMeta);
    vertexFeedIdx tile;
    float tileX = polyGridMeta.width / polyGridMeta.xCount;
    float tileY = polyGridMeta.height / polyGridMeta.yCount;
    Polyform_Tilemap_Eq::createTile(tileX, tileY, &tile);
    polyClone->create(&tile);
}

void Polyform_Tilemap::gen_points(float thresh){
    if(thresh > 1.0f || thresh < 0.0f){
        std::cerr << "Threshold should be set between 0 and 1" << std::endl;
        return;
    }
    std::srand(time(NULL));
    float random;
    for(unsigned stateElem = 0; stateElem < Polyform_Tilemap::states.size(); stateElem++){
        random = static_cast<GLfloat>(std::rand()) / static_cast<GLfloat>(RAND_MAX);
        if(random < thresh){
            Polyform_Tilemap::states[stateElem] = 1;
        } else {
            Polyform_Tilemap::states[stateElem] = 0;
        }
    }
}

int Polyform_Tilemap::get_state(unsigned nodeID){
    if(Polyform_Tilemap::states.empty() || nodeID > Polyform_Tilemap::states.size()){
        std::cerr << "No states present or requested node out of range" << std::endl;
        return 0;
    }
    return Polyform_Tilemap::states[nodeID];
}
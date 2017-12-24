#include "geometry/polybase/GL4_PolyClone.hpp"

void GL4_PolyClone::reset(){
    GL4_PolyClone::mtxSequence = nullptr;
    GL4_PolyClone::matrices.clear();
    GL4_PolyClone::xyzBits.reset();
}

void GL4_PolyClone::gen_mtx(){
    GL4_PolyClone::mtxSequence(&matrices);
    GL4_PolyClone::xyzBits.set(GL4_PolyClone::Mtx);
}

void GL4_PolyClone::createXI(vertexFeed* vFeed){
    if(!GL4_PolyClone::xyzBits.all()){
        std::cerr << "Feed GL can only work if all x y z values are present" << std::endl;
        return;
    }

    for(unsigned int matElem = 0; matElem < GL4_PolyClone::matrices.size(); matElem++){
        glm::mat4 currentMatrix = GL4_PolyClone::matrices[matElem];
        GL4_PolyClone::addNode(&currentMatrix, vFeed);
    }
}
#include "geometry/GL4_Entity.hpp"
#include "geometry/GL4_PolyFunc.hpp"
#include "geometry/polyform/Polyform_Box.hpp"
#include "geometry/polyform/Polyform_Rubiks.hpp"
#include "scene/Editor.hpp"

void Editor::init(Polyform_Box* polyBox, Polyform_Rubiks* polyRubiks){
    polyRubiks->create(Editor::workspace, polyBox);

    Polyform_Box_Meta polyBoxMeta;
    polyBox->exportMeta(&polyBoxMeta);
    Editor::polyBoxMeta = polyBoxMeta;

    Polyform_Rubiks_Meta polyRubiksMeta;
    polyRubiks->exportMeta(&polyRubiksMeta);
    Editor::polyRubiksMeta = polyRubiksMeta;

    Editor::xBounds[0] = polyRubiksMeta.xCount / 2;
    Editor::xBounds[1] = polyRubiksMeta.xCount - Editor::xBounds[0] - 1;
    Editor::xBounds[0] *= -1;
    Editor::yBounds[0] = polyRubiksMeta.yCount / 2;
    Editor::yBounds[1] = polyRubiksMeta.yCount - Editor::yBounds[0] - 1;
    Editor::yBounds[0] *= -1;
    Editor::zBounds[0] = polyRubiksMeta.zCount / 2;
    Editor::zBounds[1] = polyRubiksMeta.zCount - Editor::zBounds[0] - 1;
    Editor::zBounds[0] *= -1;

    vertexFeed vFeed;
    Editor::workspace->dump(&vFeed);
    if(vFeed.pos.empty()){
        std::cerr << "PolyFunc cannot be empty" << std::endl;
        return;
    }
    Editor::vFeedIn = vFeed;

    Editor::cursor3D.init();
    Editor::cursor3D.relMatrix = Editor::workspace->relMatrix;
    Editor::model.init();
    Editor::model.relMatrix = Editor::workspace->relMatrix;

    Editor::setCursor(0, 0, 0);

    return;
}

void Editor::setCursor(int x, int y, int z){
    if(x < Editor::xBounds[0]) x = Editor::xBounds[0];
    else if(x > Editor::xBounds[1]) x = Editor::xBounds[1];
    if(y < Editor::yBounds[0]) y = Editor::yBounds[0];
    else if(y > Editor::yBounds[1]) y = Editor::yBounds[1];
    if(z < Editor::zBounds[0]) z = Editor::zBounds[0];
    else if(z > Editor::zBounds[1]) z = Editor::zBounds[1];

    unsigned int absVertex = (x - xBounds[0]) + 
                          ((y - yBounds[0]) * Editor::polyRubiksMeta.xCount) + 
                          ((z - zBounds[0]) * Editor::polyRubiksMeta.xCount * Editor::polyRubiksMeta.yCount);

    std::array<float, 3> cursorPos = {
        Editor::vFeedIn.pos[absVertex * Editor::vFeedIn.perVertex],
        Editor::vFeedIn.pos[absVertex * Editor::vFeedIn.perVertex + 1],
        Editor::vFeedIn.pos[absVertex * Editor::vFeedIn.perVertex + 2]
    };

    Editor::cursor3D.feedPos(cursorPos.data(), 3);
}

void Editor::setCursor(std::array<int, 3>* location){
    if(location->at(0)< Editor::xBounds[0]) location->at(0)= Editor::xBounds[0];
    else if(location->at(0)> Editor::xBounds[1]) location->at(0)= Editor::xBounds[1];
    if(location->at(1)< Editor::yBounds[0]) location->at(1)= Editor::yBounds[0];
    else if(location->at(1)> Editor::yBounds[1]) location->at(1)= Editor::yBounds[1];
    if(location->at(2)< Editor::zBounds[0]) location->at(2)= Editor::zBounds[0];
    else if(location->at(2)> Editor::zBounds[1]) location->at(2)= Editor::zBounds[1];

    unsigned int absVertex = (location->at(0)- xBounds[0]) + 
                          ((location->at(1)- yBounds[0]) * Editor::polyRubiksMeta.xCount) + 
                          ((location->at(2)- zBounds[0]) * Editor::polyRubiksMeta.xCount * Editor::polyRubiksMeta.yCount);

    std::array<float, 3> cursorPos = {
        Editor::vFeedIn.pos[absVertex * Editor::vFeedIn.perVertex],
        Editor::vFeedIn.pos[absVertex * Editor::vFeedIn.perVertex + 1],
        Editor::vFeedIn.pos[absVertex * Editor::vFeedIn.perVertex + 2]
    };

    Editor::cursor3D.feedPos(cursorPos.data(), 3);
}

void Editor::spawnVertex(int x, int y, int z){
    unsigned int absVertex = (x - xBounds[0]) + 
                          ((y - yBounds[0]) * Editor::polyRubiksMeta.xCount) + 
                          ((z - zBounds[0]) * Editor::polyRubiksMeta.xCount * Editor::polyRubiksMeta.yCount);
    float xOut = Editor::vFeedIn.pos[absVertex * Editor::vFeedIn.perVertex];
    float yOut = Editor::vFeedIn.pos[absVertex * Editor::vFeedIn.perVertex + 1];
    float zOut = Editor::vFeedIn.pos[absVertex * Editor::vFeedIn.perVertex + 2];

    unsigned int currentVertexCount = Editor::vFeedOut.pos.size();
    Editor::vFeedOut.pos.resize(currentVertexCount + 3);
    Editor::vFeedOut.pos[currentVertexCount] = xOut;
    Editor::vFeedOut.pos[currentVertexCount + 1] = yOut;
    Editor::vFeedOut.pos[currentVertexCount + 2] = zOut;

    // Editor::model.clearPos();
    Editor::model.feedPos(Editor::vFeedOut.pos.data(), Editor::vFeedOut.pos.size());
}
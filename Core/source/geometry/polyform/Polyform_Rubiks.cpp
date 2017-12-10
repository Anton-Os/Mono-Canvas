#include "geometry/GL4_Entity.hpp"
#include "geometry/GL4_PolyFunc.hpp"
#include "geometry/polyform/Polyform_Box.hpp"
#include "geometry/polyform/Polyform_Rubiks.hpp"

void Polyform_Rubiks::create(GL4_Entity* entity, Polyform_Box* polyBox){
    // GL4_PolyFunc polyFunc;
    /* GL4_PolyFunc_Ref polyFuncRef = polyFunc.exportRef();

    float x1 = *(polyFuncRef.xValPtr);
    float x2 = *(polyFuncRef.xValPtr + 1);
    float y1 = *(polyFuncRef.xValPtr);
    float y2 = *(polyFuncRef.xValPtr + 1);
    float z1 = *(polyFuncRef.xValPtr);
    float z2 = *(polyFuncRef.xValPtr + 1); */
    Polyform_Box_Meta metaData;
    polyBox->exportMeta(&metaData);
}
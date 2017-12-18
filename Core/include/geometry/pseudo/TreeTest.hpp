#ifndef GEOMETRY_H
    #include "Geometry.hpp"
    #define GEOMETRY_H
#endif

#ifndef GL4_ENTITY_H
    #include "geometry/GL4_Tree.hpp"
#endif

#ifndef GL4_TREE_H
    #include "geometry/GL4_Tree.hpp"
#endif

#ifndef POLY_FUNC_H
    #include "geometry/GL4_PolyFunc.hpp"
#endif

#ifndef POLY_CLONE_H
    #include "geometry/GL4_PolyClone.hpp"
#endif

#ifndef POLYFORM_BOX_H
    #include "geometry/polyform/Polyform_Box.hpp"
#endif

class TreeTest {
public:
    TreeTest(GL4_PolyClone* polyClone, Polyform_Box* polyBox){
        polyBox->exportMeta(&polyBoxMeta);
        createXI(polyClone);
    }
    void createXI(GL4_PolyClone* polyClone);
private:
    Polyform_Box_Meta polyBoxMeta;
};
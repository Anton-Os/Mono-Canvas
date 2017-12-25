#ifndef GEOMETRY_H
    #include "Geometry.hpp"
    #define GEOMETRY_H
#endif

#ifndef GL4_ENTITY_H
    #include "geometry/GL4_Entity.hpp"
#endif

#ifndef POLY_FUNC_H
    #include "geometry/polybase/GL4_PolyFunc.hpp"
#endif

#ifndef POLY_BOX_H
    #include "geometry/polyform/Polyform_Box.hpp"
#endif

#ifndef POLY_RUBIKS_H
    #include "geometry/polyform/Polyform_Rubiks.hpp"
#endif

#ifndef EDITOR_H
    class Editor {
    public:
        Editor(GL4_PolyFunc* polyFuncArg, Polyform_Box* polyBox, Polyform_Rubiks* polyRubiks) {
            workspace = polyFuncArg;
            init(polyBox, polyRubiks);
        }
        GL4_PolyFunc* workspace;
        GL4_Entity cursor3D;
        GL4_Entity model;
        void init(Polyform_Box* polyBox, Polyform_Rubiks* polyRubiks);
        void setCursor(int x, int y, int z);
        void setCursor(std::array<int, 3>* location);
        void spawnVertex(int x, int y, int z);
    private:
        Polyform_Box_Meta polyBoxMeta;
        Polyform_Rubiks_Meta polyRubiksMeta;
        vertexFeed vFeedIn;
        vertexFeed vFeedOut;
        int xBounds[2];
        int yBounds[2];
        int zBounds[2];
    };
#define EDITOR_H
#endif
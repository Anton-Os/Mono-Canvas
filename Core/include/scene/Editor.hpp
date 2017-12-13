#ifndef GEOMETRY_H
    #include "Geometry.hpp"
    #define GEOMETRY_H
#endif

#ifndef ENTITY_H
    #include "geometry/GL4_Entity.hpp"
#endif

#ifndef POLY_FUNC_H
    #include "geometry/GL4_PolyFunc.hpp"
#endif

#ifndef POLYFORM_RUBIKS_H
    #include "geometry/polyform/Polyform_Rubiks.hpp"
#endif

#ifndef EDITOR_H
    class Editor {
    public:
        Editor(GL4_Entity* entityArg1, GL4_Entity* entityArg2, GL4_PolyFunc* polyFuncArg, 
               Polyform_Box* polyBox, Polyform_Rubiks* polyRubiks) {
            workspace = polyFuncArg; 
            cursor3D = entityArg1;
            model = entityArg2;
            init(polyBox, polyRubiks);
        }
        GL4_PolyFunc* workspace;
        GL4_Entity* cursor3D;
        GL4_Entity* model;
        void init(Polyform_Box* polyBox, Polyform_Rubiks* polyRubiks);
        void create(int x, int y, int z);
    private:
        Polyform_Box_Meta polyBoxMeta;
        Polyform_Rubiks_Meta polyRubiksMeta;
        vertexFeed vFeed;
        int xBounds[2];
        int yBounds[2];
        int zBounds[2];
    };

    /* class Editor {
    public:
        Editor(GL4_PolyFunc* workspace, Polyform_Rubiks* polyRubiks){
            init(workspace, polyRubiks);
        }
        void init(GL4_PolyFunc* workspace, Polyform_Rubiks* polyRubiks);
        create();
    } */
#define EDITOR_H
#endif
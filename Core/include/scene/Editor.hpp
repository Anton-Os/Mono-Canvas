#ifndef GEOMETRY_H
    #include "Geometry.hpp"
    #define GEOMETRY_H
#endif

#ifndef ENTITY_H
    #include "geometry/GL4_Entity.hpp"
#endif

#ifndef POLYFORM_RUBIKS_H
    #include "geometry/polyform/Polyform_Rubiks.hpp"
#endif

#ifndef EDITOR_H
    class Editor {
    public:
        Editor(GL4_Entity* entityArg1, GL4_Entity* entityArg2, 
               GL4_PolyFunc* polyFunc, Polyform_Rubiks* polyRubiks) {
            cursor3D = entityArg1;
            model = entityArg2;
            init(polyFunc, polyRubiks);
        }
        GL4_Entity* cursor3D;
        GL4_Entity* model;
        void init(GL4_PolyFunc* polyFunc, Polyform_Rubiks* polyRubiks);
        void create(int x, int y, int z);
    private:
        vertexFeed vFeed;
        int xBounds[2];
        int yBounds[2];
        int zBounds[2];
    };

    /* class Editor {
    public:
        Editor(GL4_PolyFunc* polyFunc, Polyform_Rubiks* polyRubiks){
            init(polyFunc, polyRubiks);
        }
        void init(GL4_PolyFunc* polyFunc, Polyform_Rubiks* polyRubiks);
        create();
    } */
#define EDITOR_H
#endif
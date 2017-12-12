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
        Editor(GL4_Entity* entityArg1, GL4_Entity* entityArg2, Polyform_Rubiks* polyRubiksArg){
            cursor3D = entityArg1;
            model = entityArg2;
            polyRubiks = polyRubiksArg;
            init();
        }
        GL4_Entity* cursor3D;
        GL4_Entity* model;
        Polyform_Rubiks* polyRubiks;
        void init();
        void create(int x, int y, int z);
    };
#define EDITOR_H
#endif
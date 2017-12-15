#ifndef GEOMETRY_H
    #include "Geometry.hpp"
    #define GEOMETRY_H
#endif

#ifndef ENTITY_H
    #include "geometry/GL4_Entity.hpp"
#endif

#ifndef POLY_CLONE_H
    class GL4_PolyFunc : public GL4_Entity {
    public:
        void (*mtxSequence)(std::vector<glm::mat4>>* matrices);
        void create(vertexFeedIdx* vFeed);
    };

#define POLY_CLONE_H
#endif

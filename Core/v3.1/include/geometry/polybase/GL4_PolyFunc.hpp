#ifndef GEOMETRY_H
    #include "Geometry.hpp"
    #define GEOMETRY_H
#endif

#ifndef ERROR_CODE_H
    #include "scene/ErrorCode.hpp"
#endif

#ifndef GL4_VERTEX_FACTORY_H
    #include "GL4/factory/GL4_Vertex_Factory.hpp"
#endif

#ifndef GL4_MESH_H
    #include "GL4/geometry/GL4_Mesh.hpp"
#endif

#ifndef POLY_FUNC_H
    class GL4_PolyFunc {
    public:
        void (*xSequence)(std::vector<float>* xVals);
        float (*yEquation)(float);
        float (*zEquation)(float, float);
        void reset();
        void gen_x();
        void gen_y();
        void gen_z();
        unsigned get_xCount(){ return xVals.size(); }
        unsigned get_yCount(){ return yVals.size() / xVals.size(); }
        unsigned get_zCount(){ return zVals.size() / yVals.size(); }
        void create();
        void create(GL4_Mesh* mesh, GL4_Vertex_Factory* factory);
        std::vector<float> vertices;
        std::vector<GLuint> indices;
    private:
        std::vector<float> xVals;
        std::vector<float> yVals;
        std::vector<float> zVals;
        enum ptAttrib { X, Y, Z };
        std::bitset<3> xyzBits;
    };

    //static unsigned genIndices1D(std::vector<unsigned>* indexAccum, unsigned xCount);
    //static unsigned genIndices2D(std::vector<unsigned>* indexAccum, unsigned xCount, unsigned yCount);
    //static unsigned genIndices3D(std::vector<unsigned>* indexAccum, unsigned xCount, unsigned yCount, unsigned zCount);
#define POLY_FUNC_H
#endif

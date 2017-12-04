#ifndef GEOMETRY_H
    #include "geometry/Geometry.hpp"
    #define GEOMETRY_H
#endif

#ifndef POLY_TRAVERSE_H
    class GL4_PolyTraverse : public GL4_Object3D {
    public:
        void (*traverse)(std::vector<float>* xyzVals);
        void (*traverseIdx)(std::vector<float>* xyzVals, std::vector<unsigned int>* indices);
        void reset();
        void createXI();
        void create();
        void map(std::vector<float>* posAccum);
        void draw(GLenum drawMode);
        void draw(GLenum drawMode, unsigned int drawCount);
    private:
        unsigned int idxBff;
        bool isFed = false;
        bool isIdx = false;
        unsigned int indexCount;
        enum trvModes { trvDft, trvIdx };
        std::bitset<2> trvBits;
    };

#define POLY_TRAVERSE_H
#endif
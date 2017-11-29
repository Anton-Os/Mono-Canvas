class PLY_BumpGrid {
public:
    PLY_BumpGrid(GL4_PolyFunc* polyFunc, float rise_arg, float width_arg,
                       unsigned int xCount_arg, float height_arg, unsigned int yCount_arg) {
        rise = rise_arg;
        width = width_arg;
        xCount = xCount_arg;
        height = height_arg;
        yCount = yCount_arg;
        polyFunc->reset();
        create(polyFunc);
    }
    void create(GL4_PolyFunc* polyFunc);
    void setModeZ(int zMode);
private:
    int zMode = normal;
    enum zModes { normal, bumpy, cornerUp, peak };
    float rise;
    float width;
    unsigned int xCount;
    float height;
    unsigned int yCount;
};
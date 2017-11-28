class CartesianGrid_Eq {
public:
    CartesianGrid_Eq(GL4_PolyFunc* polyFunc, float width_arg, unsigned int xCount_arg, 
                     float height_arg, unsigned int yCount_arg) {
        width = width_arg;
        xCount = xCount_arg;
        height = height_arg;
        yCount = yCount_arg;
        polyFunc->reset();
        create(polyFunc);
    }
    void create(GL4_PolyFunc* polyFunc);
private:
    void xEquation(std::vector<float>* xVals);
    float yEquation(float);
    float zEquation(float, float);
    float width;
    unsigned int xCount;
    float height;
    unsigned int yCount;
};
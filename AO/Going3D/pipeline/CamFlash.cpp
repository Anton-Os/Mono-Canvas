#include "Common.h"

void CamFlash::setUniforms() {
    CamFlash::unifLoc[CF_UNIF::mvMatrix] = glGetUniformLocation(CamFlash::shaderProgID, "mvMatrix");
    if(CamFlash::unifLoc[CF_UNIF::mvMatrix] == -1) std::cerr << "CamFlash uniform issue: mvMatrix" << std::endl;
    CamFlash::unifLoc[CF_UNIF::mvMatrix] = glGetUniformLocation(CamFlash::shaderProgID, "mvpMatrix");
    if(CamFlash::unifLoc[CF_UNIF::mvMatrix] == -1) std::cerr << "CamFlash uniform issue: mvpMatrix" << std::endl;
    CamFlash::unifLoc[CF_UNIF::mvMatrix] = glGetUniformLocation(CamFlash::shaderProgID, "nMatrix");
    if(CamFlash::unifLoc[CF_UNIF::mvMatrix] == -1) std::cerr << "CamFlash uniform issue: nMatrix" << std::endl;
    CamFlash::unifLoc[CF_UNIF::mvMatrix] = glGetUniformLocation(CamFlash::shaderProgID, "camPos");
    if(CamFlash::unifLoc[CF_UNIF::mvMatrix] == -1) std::cerr << "CamFlash uniform issue: camPos" << std::endl;
}
#include "geometry/Tile.hpp"

static char error_initPhase[] = "Cannot perform before init phase";
static char error_createPhase[] = "Cannot perform after create phase";

void Tile::init(float height_arg, float width_arg){
    if(mCreatePhase) logError(__FILE__, __LINE__, error_createPhase);
    
    mHeight = height_arg;
    mWidth = width_arg;

    mInitPhase = true;
}

void Tile::create(GL4_Mesh* mesh, GL4_Vertex_Factory* factory){
    if(!mInitPhase) logError(__FILE__, __LINE__, error_initPhase);

    mesh->add_feed(factory->get_format(_GL4_Vertex_Feed_ID::pos_2f));
    mesh->add_feed(factory->get_format(_GL4_Vertex_Feed_ID::texCoord_2f));

    GLfloat coords[8] = { 
       -1 * mWidth / 2, -1 * mHeight / 2,
       mWidth / 2, -1 * mHeight / 2,
       -1 * mWidth / 2, mHeight / 2, 
       mWidth / 2, mHeight / 2
    };

    GLfloat texcoords[8] = { 
       GL4_TEXCOORD_S_MIN, GL4_TEXCOORD_T_MIN,
       GL4_TEXCOORD_S_MAX, GL4_TEXCOORD_T_MIN,
       GL4_TEXCOORD_S_MIN, GL4_TEXCOORD_T_MAX, 
       GL4_TEXCOORD_S_MAX, GL4_TEXCOORD_T_MAX
    };

    mesh->set_feed_data(_GL4_Vertex_Feed_ID::pos_2f, &coords[0], sizeof(GLfloat));
    mesh->set_feed_data(_GL4_Vertex_Feed_ID::texCoord_2f, &texcoords[0], sizeof(GLfloat));

    mCreatePhase = true;
}

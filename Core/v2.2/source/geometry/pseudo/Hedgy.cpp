#include "geometry/pseudo/Hedgy.hpp"

void Hedgy::create(GL4_Mesh* mesh, GL4_Vertex_Factory* factory){
    const GL4_Vertex_Format* pos_format = factory->get_format(_GL4_Vertex_Feed::pos_3f);
    const GL4_Vertex_Format* color_format = factory->get_format(_GL4_Vertex_Feed::color_4f);

    mesh->add_feed(pos_format);
    mesh->add_feed(color_format);

    float hedgyPos[] = {
        0.1f, -0.2f, 0.0f,
        0.4f, -0.7f, 0.2f,
        0.6f, 0.4f, 0.5f,
        -0.84f, 0.33f, 0.3f,
        0.92f, -0.8f, 0.62f,
        -0.01f, 0.1f, 0.33f,
        0.11f, 0.2f, 0.02f,
        0.51f, -0.9f, 0.11f,
        -0.56f, 0.61f, 0.47f,
    }; // 9 total

    GLubyte hedgyColor[] = {
        122, 50, 80, 255,
        40, 50, 80, 255,
        10, 50, 80, 255,
        50, 122, 80, 255,
        50, 122, 80, 255,
        50, 122, 80, 255,
        122, 80, 50, 255,
        122, 80, 50, 255,
        122, 80, 50, 255,
    }; // 9 total

    mesh->set_feed(0, &hedgyPos[0], sizeof(float));
    mesh->set_feed(1, &hedgyColor[0], sizeof(GLubyte));
}

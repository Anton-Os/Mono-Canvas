#include "geometry/pseudo/Hedgy.hpp"

void Hedgy::create(GL4_Mesh* mesh){
    GL4_Vertex_Format pos_format(0, 3, GL_ARRAY_BUFFER, GL_FLOAT, GL_STATIC_DRAW, GL_FALSE, vaoPtrModes::Default);
    GL4_Vertex pos;
    pos.format = pos_format;
    GL4_Vertex_Format color_format(1, 4, GL_ARRAY_BUFFER, GL_UNSIGNED_BYTE, GL_STATIC_DRAW, GL_TRUE, vaoPtrModes::Default);
    GL4_Vertex color;
    color.format = color_format;

    mesh->add_feed(&pos);
    mesh->add_feed(&color);

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

    mesh->run_feed(0, &hedgyPos[0], sizeof(float));
    mesh->run_feed(1, &hedgyColor[0], sizeof(float));
}

/* void Hedgy::create(GL4_Mesh* mesh, GL4_Vertex_Factory* factory){
} */
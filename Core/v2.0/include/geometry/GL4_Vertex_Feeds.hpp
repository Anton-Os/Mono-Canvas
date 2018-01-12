#ifndef GEOMETRY_H
    #include "Geometry.hpp"
#endif

#ifndef GL4_VERTEX_H
    #include "geometry/GL4_Vertex.hpp"
#endif

#ifndef GL4_VERTEX_FEEDS_H

// Implement a vertex for each type that could be potentialy fed to OpenGL
// Make it derived from GL4_Vertex.hpp

class GL4_Vertex_Feed {
public:
    void create(GL4_Vertex* vertex){
        count = set_count();
        vertex->count = count;
        feedID = set_feedID();
        vertex->feedID = feedID;
        target = set_target();
        vertex->target = target;
        type = set_type();
        vertex->type = type;
        usage = set_usage();
        vertex->usage = usage;
        normalized = set_normalized();
        vertex->normalized = normalized;
        vaoPtrMode = set_vaoPtrMode();
        vertex->vaoPtrMode = vaoPtrMode;
    }
    virtual GLint set_count(){ return 3; };
    virtual GLint set_feedID(){ return 0; };
    virtual GLenum set_target(){ return GL_ARRAY_BUFFER; };
    virtual GLenum set_type(){ return GL_FLOAT; }
    virtual GLenum set_usage(){ return GL_STATIC_DRAW; };
    virtual GLboolean set_normalized(){ return GL_FALSE; };
    virtual GLint set_vaoPtrMode(){ return vaoPtrModes::Default; };
private:
    GLint count;
    GLint feedID;
    GLenum target;
    GLenum type;
    GLenum usage;
    GLenum normalized;
    GLint vaoPtrMode;
};

class GL4_Vertex_Pos : public GL4_Vertex_Feed {
    GLint set_count() override { return 3; };
    GLint set_feedID() override { return 0; };
    GLenum set_target() override { return GL_ARRAY_BUFFER; };
    GLenum set_type() override { return GL_FLOAT; };
    GLenum set_usage() override { return GL_STATIC_DRAW; };
    GLboolean set_normalized() override { return GL_FALSE; };
    GLint set_vaoPtrMode() override { return vaoPtrModes::Default; };
};

#define GL4_VERTEX_FEEDS_H
#endif
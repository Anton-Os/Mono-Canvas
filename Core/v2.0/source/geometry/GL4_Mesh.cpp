#include "geometry/GL4_Mesh.hpp"

void GL4_Mesh_Quill::init(GLboolean* fed, GLboolean* idx, GLuint* v, GLuint* i){
    if(initPhase){
        std::cerr << "Cannot modify pointers after initialization, please invoke quill.reset()" << std::endl;
        return;
    }
    
    if(nullptr == fed || nullptr == idx || nullptr == v || nullptr == i){
        std::cerr << "Arguments provideds are null pointers" << std::endl;
        return;
    }

    if(*fed == false || *idx == false || *v == 0 || *i == 0){
        std::cerr << "Pointer values point to false and/or zero" << std::endl;
        return;
    }

    isFedPtr = fed;
    isIdxPtr = idx;
    vertexCountPtr = v;
    indexCountPtr = i;
    initPhase = true;
}

void GL4_Mesh::init(){
    if(vertices.empty()){
        std::cerr << "Vertex attributes are empty" << std::endl;
        return;
    }

    glGenVertexArrays(1, &VAO);

    std::vector<GLuint> buffers;
    buffers.resize(vertices.size());
    glGenBuffers(vertices.size(), buffers.data());

    for(unsigned v = 0; v < vertices.size(); v++) vertices[v].buffer = buffers[v];
}

void GL4_Mesh::feed(GLuint vAttrib, const void * data, size_t size){
    bool attribFound = false;
    for(unsigned v = 0; v < vertices.size(); v++){
        if(vertices[v].feedID == vAttrib){
            attribFound = true;
            break;
        }
    }

    if(!attribFound){
        std::cerr << "Requested vertex attribute does not exist" << std::endl;
        return;
    }

    glBindBuffer(vertices[vAttrib].target, vertices[vAttrib].buffer);
    glBufferData(vertices[vAttrib].target, size * vertexCount, data, vertices[vAttrib].usage);

    glBindVertexArray(VAO);
    if(vertices[vAttrib].vaoPtrMode == vaoPtrModes::Default)
        glVertexAttribPointer(vertices[vAttrib].feedID, vertices[vAttrib].count, vertices[vAttrib].type, vertices[vAttrib].normalized, 0, nullptr);
    else if(vertices[vAttrib].vaoPtrMode == vaoPtrModes::Integral)
        glVertexAttribIPointer(vertices[vAttrib].feedID, vertices[vAttrib].count, vertices[vAttrib].type, 0, nullptr);
    else if(vertices[vAttrib].vaoPtrMode == vaoPtrModes::Integral)
        glVertexAttribIPointer(vertices[vAttrib].feedID, vertices[vAttrib].count, vertices[vAttrib].type, 0, nullptr);

    glEnableVertexAttribArray(vertices[vAttrib].feedID);
    glBindVertexArray(0);

    if(!vertices[vAttrib].isFed){
        vertices[vAttrib].isFed = true;
        feedCounter--;
        if(feedCounter == 0) isFed = true;
    }
}
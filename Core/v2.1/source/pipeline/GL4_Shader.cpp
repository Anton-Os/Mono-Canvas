#include "pipeline/GL4_Shader.hpp"

static char error_glslIncomp[] = "Vertex format is GLSL incompatible";

void GL4_Shader::add_input(GL4_Vertex_Format* vertex){
    if(vertex->glsl_type.type.empty() || vertex->glsl_type.count == 0 || vertex->glsl_type.size == 0) logError(__FILE__, __LINE__, error_glslIncomp);
    inputs.push_back(vertex);
}

void GL4_Shader::create(const std::string& fileName){
    std::string extension;
    std::string shader_source;
    switch(stage){
        case GL4_Shader_Stage::vert :
            extension = ".vert";
            compose_vertex_shader(shader_source);
            break;
        case GL4_Shader_Stage::frag :
            extension = ".frag";
            break;
        case GL4_Shader_Stage::tesc :
            extension = ".tesc";
            break;
        case GL4_Shader_Stage::tese :
            extension = ".tese";
            break;
        case GL4_Shader_Stage::geom :
            extension = ".geom";
            break;
        case GL4_Shader_Stage::comp :
            extension = ".comp";
            break;
    }
    // shader_source = "Antons shader!";
    writeFile(fileName + extension, shader_source);
    ready = true;
}

void GL4_Shader::compose_vertex_shader(std::string& shader_source){
    shader_source.clear();
    // Header section
    shader_source.append("version " + std::to_string(version) + " core \n");
    shader_source.append(1, '\n');
    // Inputs section
    for(unsigned inputElem = 0; inputElem < inputs.size(); inputElem++)
        shader_source.append(write_input_entry(inputs[inputElem]->feedID, inputs[inputElem]->glsl_type.name, inputs[inputElem]->glsl_type.type));
    shader_source.append(1, '\n');
    for(unsigned outputElem = 0; outputElem < outputs.size(); outputElem++)
        shader_source.append(write_output_entry(outputs[outputElem]->feedID, outputs[outputElem]->glsl_type.name, outputs[outputElem]->glsl_type.type));
    shader_source.append(1, '\n');
    shader_source.append("void main() {\n");
    shader_source.append("\t gl_Position = vec4(0.0, 0.0, 0.0, 1.0); \n");
    shader_source.append(1, '}');
}

static std::string write_input_entry(GLint location, const std::string& name, const std::string& type){
    std::string line;
    line.append("layout(location=");
    line.append(std::to_string(location));
    line.append(") in " + type);
    line.append(1, ' ');
    line.append(name);
    line.append(1, ';');
    line.append(1, '\n');
    return line;
}

static std::string write_output_entry(GLint location, const std::string& name, const std::string& type){
    std::string line;
    line.append("layout(location=");
    line.append(std::to_string(location));
    line.append(") out " + type);
    line.append(1, ' ');
    line.append(name + "_out;");
    line.append(1, '\n');
    return line;
}
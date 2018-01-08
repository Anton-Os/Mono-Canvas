#include "Loaders.h"

#define PREF_GLSL_VERSION 440

#ifndef LOADERS_COMP_SHADERS_H

    struct Comp_Feed {
        bool isInput = true;
        unsigned id = 0;
        std::size_t size = sizeof(float);
        std::string typeName = "vec3";
        std::string name = "pos";
    };

    struct Comp_VertexShader {
        std::string name = "Shader";
        std::vector<Comp_Feed> feeds;
    };

    struct Comp_FragmentShader {
        std::string name = "Shader";
        std::vector<Comp_Feed> feeds;
    };

    class Comp_ShaderProg {
        Comp_ShaderProg(Comp_VertexShader* vertexShaderArg, Comp_FragmentShader* fragmentShaderArg){
            vertexShader = *vertexShaderArg;
            fragmentShader = *fragmentShaderArg;
            create();
        }
        unsigned version = PREF_GLSL_VERSION;
        Comp_VertexShader vertexShader;
        Comp_FragmentShader fragmentShader;
        void create();
    };

#define LOADERS_COMP_SHADERS_H
#endif
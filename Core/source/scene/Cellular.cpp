#include "Feeds.h"
#include "scene/Cellular.hpp"

void Cellular::gen_points(float thresh){
    if(thresh > 1.0f || thresh < 0.0f){
        std::cerr << "Threshold should be set between 0 and 1" << std::endl;
        return;
    }
    std::srand(time(NULL));
    float random;
    for(unsigned stateElem = 0; stateElem < Cellular::states.size(); stateElem++){
        random = static_cast<GLfloat>(std::rand()) / static_cast<GLfloat>(RAND_MAX);
        if(random < thresh){
            Cellular::states[stateElem] = 1;
        } else {
            Cellular::states[stateElem] = 0;
        }
    }
}

void Cellular::gen_points(Cellular_Picker* cellPicker){
    if(cellPicker->weights.empty() || cellPicker->states.empty() || 
        cellPicker->weights.size() != cellPicker->states.size()){
        std::cerr << "Weights and states cannot be empty and cannot vary in size" << std::endl;
        return;
    }

    std::srand(time(NULL));
    float totalWeight;
    for(unsigned stateElem = 0; stateElem < cellPicker->weights.size(); stateElem++)
        totalWeight += std::abs(cellPicker->weights[stateElem]);

    std::vector<float> weights;
    weights.resize(cellPicker->weights.size() + 1);
    weights[0] = 0.0f;

    for(unsigned stateElem = 0; stateElem < cellPicker->weights.size(); stateElem++){
       weights[stateElem + 1] = std::abs(weights[stateElem] + cellPicker->weights[stateElem] / totalWeight);
    }

    float random;
    float bounds[2];
    int correctState;
    Cellular::states.resize(cellPicker->states.size());
    for(unsigned weightElem = 0; weightElem < cellPicker->weights.size(); weightElem++){
        random = static_cast<GLfloat>(std::rand()) / static_cast<GLfloat>(RAND_MAX);
        correctState = cellPicker->defaultState;
        for(unsigned stateElem = 0; stateElem < cellPicker->weights.size(); stateElem++){
            bounds[0] = weights[stateElem];
            bounds[1] = weights[stateElem + 1];
            if(random >= bounds[0] && random <= bounds[1]){
                correctState = cellPicker->states[stateElem];
                break;
            }
        }
        Cellular::states[weightElem] = correctState;
    }
}

/* void Cellular::init(){
    GLuint buffer;

    glBindVertexArray(Cellular::VAO);

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    Cellular::stateBff = buffer;
} */

void Cellular::init() { return; }

void Cellular::feedStates(){
    glBindVertexArray(Cellular::VAO);
    GLuint buffer;
    glGenBuffers(1, &buffer);
    Cellular::stateBff = buffer;
    glBindBuffer(GL_ARRAY_BUFFER, Cellular::stateBff);
    glBufferData(GL_ARRAY_BUFFER, Cellular::states.size() * sizeof(GLint), Cellular::states.data(), GL_STATIC_DRAW);
    glVertexAttribIPointer(FEED_STATE_ID, FEED_STATE_COUNT, GL_INT, 0, (GLvoid*)0);
    glEnableVertexAttribArray(FEED_STATE_ID);
    glBindVertexArray(0);
}
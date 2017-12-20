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

    std::vector<float> clmpWeights;
    if(totalWeight > 1.0f){
        clmpWeights.resize(cellPicker->weights.size());
        for(unsigned stateElem = 0; stateElem < clmpWeights.size(); stateElem++)
            clmpWeights[stateElem] = std::abs(cellPicker->weights[stateElem]) / totalWeight;

    } else {
        clmpWeights.resize(cellPicker->weights.size() + 1);
        for(unsigned stateElem = 0; stateElem < clmpWeights.size(); stateElem++)
            clmpWeights[stateElem] = std::abs(cellPicker->weights[stateElem]);

        clmpWeights[cellPicker->weights.size() - 1] = 1.0f - totalWeight;
    }

    float random;
    float bounds[2] = {0.0f, clmpWeights[0]};
    for(unsigned weightElem = 0; weightElem < Cellular::states.size(); weightElem++){
        random = static_cast<GLfloat>(std::rand()) / static_cast<GLfloat>(RAND_MAX);
        for(unsigned stateElem = 0; stateElem < clmpWeights.size() - 1; stateElem++){
            if(random > bounds[0] && random <= bounds[1]){
                Cellular::states[stateElem] = cellPicker->states[stateElem];
                break;
            }
            bounds[0] += clmpWeights[stateElem];
            bounds[1] += clmpWeights[stateElem + 1];
        }
    }
}
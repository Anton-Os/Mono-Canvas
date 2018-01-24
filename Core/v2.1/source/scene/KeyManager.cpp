#include "scene/KeyManager.hpp"

static char error_xSwitchCallback[] = "Switch does not contain a callback function";
static char error_switchNoStates[] = "Switch does not have states associated";
static char error_xButtonCallback[] = "Button does not contain a callback function";
static char error_xCounterCallback[] = "Counter does not contain a callback function";

void KeyManager::add_switch(Key_Switch* keySwitch){
    if(keySwitch->callback == nullptr) logError(__FILE__, __LINE__, error_xSwitchCallback);
    if(keySwitch->states.empty()) logError(__FILE__, __LINE__, error_switchNoStates);

    switches.push_back(*keySwitch);
    id_counter++;
    keySwitch->handle = id_counter;
}

void KeyManager::add_button(Key_Button* keyButton){ 
    if(keyButton->callback == nullptr) logError(__FILE__, __LINE__, error_xButtonCallback);

    buttons.push_back(*keyButton); 
    id_counter++;
    keyButton->handle = id_counter;
}

void KeyManager::add_counter(Key_Counter* keyCounter){
    if(keyCounter->callback == nullptr) logError(__FILE__, __LINE__, error_xCounterCallback);

    counters.push_back(*keyCounter); 
    id_counter++;
    keyCounter->handle = id_counter;
}

void KeyManager::set_current(GLFWwindow* window){
    glfwSetWindowUserPointer(window, static_cast<void*>(this));
    glfwSetKeyCallback(window, callback_test);
}

void KeyManager::callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    for(unsigned switchElem = 0; switchElem < switches.size(); switchElem++){
        if(key == switches[switchElem].key && action == GLFW_PRESS) switches[switchElem].index++;
        if(switches[switchElem].index == switches[switchElem].states.size()) switches[switchElem].index = 0;

        switches[switchElem].state = switches[switchElem].states[switches[switchElem].index];
        
        switches[switchElem].callback(&switches[switchElem].state);
    }

    for(unsigned buttonElem = 0; buttonElem < buttons.size(); buttonElem++){
        if(key == buttons[buttonElem].key && action == GLFW_PRESS) buttons[buttonElem].val = true;
        else if(key == buttons[buttonElem].key && action == GLFW_RELEASE) buttons[buttonElem].val = false;

        buttons[buttonElem].callback(&buttons[buttonElem].val);
    }

    for(unsigned counterElem = 0; counterElem < counters.size(); counterElem++){
        if(key == counters[counterElem].incKey && action == GLFW_PRESS) counters[counterElem].num++;
        else if(key == counters[counterElem].decKey && action == GLFW_PRESS) counters[counterElem].num--;

        counters[counterElem].callback(&counters[counterElem].num);
    }
}
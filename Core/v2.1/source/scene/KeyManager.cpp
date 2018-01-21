#include "scene/KeyManager.hpp"

static char error_xSwitchCallback[] = "Switch does not contain a callback function";
static char error_switchNoStates[] = "Switch does not have states associated";
static char error_xButtonCallback[] = "Button does not contain a callback function";
static char error_xCounterCallback[] = "Counter does not contain a callback function";
// static char error_counterNoKeys[] = "Counter does not have key assignments";

void KeyManager::callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    for(unsigned switchElem = 0; switchElem < switches.size(); switchElem++){
        /* Assess the validity of the switch data */
        if(switches[switchElem].callback == nullptr) logError(__FILE__, __LINE__, error_xSwitchCallback);
        if(switches[switchElem].states.empty()) logError(__FILE__, __LINE__, error_switchNoStates);

        /* Check whether the switch has been modified */
        if(key == switches[switchElem].key && action == GLFW_PRESS) switches[switchElem].index++;
        if(switches[switchElem].index == switches[switchElem].states.size()) switches[switchElem].index = 0;

        /* Syncronization step, SHOULD BE MADE CONDITIONAL*/
        switches[switchElem].state = switches[switchElem].states[switches[switchElem].index];
        // switches[switchElem].state = states[switches[switchElem].index % switches[switchElem].states.size()];

        /* Executes callback specific to switch */
        switches[switchElem].callback(&switches[switchElem].state);
    }

    for(unsigned buttonElem = 0; buttonElem < buttons.size(); buttonElem++){
        /* Assess the validity of the button data */
        if(buttons[buttonElem].callback == nullptr) logError(__FILE__, __LINE__, error_xButtonCallback);

        /* Check whether the button has been modified */
        if(key == buttons[buttonElem].key && action == GLFW_PRESS) buttons[buttonElem].val = true;
        else if(key == buttons[buttonElem].key && action == GLFW_RELEASE) buttons[buttonElem].val = false;

        /* Executes callback specific to button */
        buttons[buttonElem].callback(&buttons[buttonElem].val);
    }

    for(unsigned counterElem = 0; counterElem < counters.size(); counterElem++){
        /* Assess the validity of the counter data */
        if(counters[counterElem].callback == nullptr) logError(__FILE__, __LINE__, error_xCounterCallback);
        // if(counters[counterElem].incKeys.empty() || counters[counterElem].decKeys.empty()) logError(__FILE__, __LINE__, error_xCounterCallback);

        /* Check whether the counter has been modified */
        if(key == counters[counterElem].incKey && action == GLFW_PRESS) counters[counterElem].num++;
        else if(key == counters[counterElem].decKey && action == GLFW_PRESS) counters[counterElem].num--;

        /* Executes callback specific to counter */
        counters[counterElem].callback(&counters[counterElem].num);
    }
}
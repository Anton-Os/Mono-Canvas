#ifndef ERROR_CODE_H
    #include "scene/ErrorCode.hpp"
#endif

#ifndef KEY_MANAGER_H
    #include <cstdio>
    #include <cstdlib>
    #include <vector>

    #include <GLFW/glfw3.h>

    typedef enum { swt, btn, ctr } Key_t;

    struct Key_Element {
        unsigned handle;
    };

    struct Key_Switch : public Key_Element {
        int state;
        unsigned index = 0;
        std::vector<int> states;
        int key;
        void(*callback)(int* s) = nullptr;
    };

    struct Key_Button : public Key_Element {
        bool val = false;
        int key;
        void(*callback)(bool* b) = nullptr;
    };

    struct Key_Counter : public Key_Element {
        int num;
        int incKey; int decKey;
        void(*callback)(int* n) = nullptr;
    };

    class KeyManager {
    public:
        void add_switch(Key_Switch* keySwitch);
        void add_button(Key_Button* keyButton);
        void add_counter(Key_Counter* keyCounter);
        void set_current(GLFWwindow* window);
    private:
        bool ready = false;
        unsigned id_counter = 0;
        std::vector<Key_Switch> switches;
        std::vector<Key_Button> buttons;
        std::vector<Key_Counter> counters;
        void callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void callback_test(GLFWwindow* window, int key, int scancode, int action, int mods){
            KeyManager* ptr = static_cast<KeyManager*>(glfwGetWindowUserPointer(window));
            ptr->callback(window, key, scancode, action, mods);
        };
    };

#define KEY_MANAGER_H
#endif
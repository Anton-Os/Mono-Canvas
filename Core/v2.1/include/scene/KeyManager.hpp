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
        Key_Element(unsigned* id){
            *id++;
            ID = *id;
        }
        unsigned ID;
    };

    struct Key_Switch : public Key_Element {
        Key_Switch(unsigned * id) : Key_Element(id) { }
        int state;
        unsigned index = 0;
        std::vector<int> states;
        int key;
        (*callback)(int* s) = nullptr;
    };

    struct Key_Button : public Key_Element {
        Key_Button(unsigned * id) : Key_Element(id) { }
        bool val = false;
        int key;
        (*callback)(bool* v) = nullptr;
    };

    struct Key_Counter : public Key_Element {
        Key_Counter(unsigned * id) : Key_Element(id) { }
        int num;
        int incKey;
        int decKey;
        (*callback)(int* v) = nullptr;
    };

    class KeyManager {
    public:
        void add_switch(Key_Switch* keySwitch);
        void add_button(Key_Button* keyButton);
        void add_counter(Key_Counter* keyCounter);
        void add_callback(unsigned ID);
        void add_callback(Key_t keyType, unsigned index);
    private:
        unsigned id_counter;
        std::vector<Key_Switch> switches;
        std::vector<Key_Button> buttons;
        std::vector<Key_Counter> counters;
        void callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    };
#define KEY_MANAGER_H
#endif
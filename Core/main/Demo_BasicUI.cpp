#include <iostream>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

namespace UI {
	int height = 1080;
	int width = 1320;
}

int main(int argc, char** argv) {
    Fl_Window *window = new Fl_Window(UI::width / 2.0f, UI::width / 2.0f);
    Fl_Box *box = new Fl_Box(20, 30, 300, 100, "Hello FLTK");
    box->box(FL_UP_BOX);
    box->labelfont(FL_BOLD+FL_ITALIC);
    box->labeltype(FL_SHADOW_LABEL);
    window->end();
    window->show(argc, argv);
	
    return Fl::run();
}

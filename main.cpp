#include <wx/wx.h>
#include "MainFrame.h"


class NoteApp : public wxApp {
public:
    bool OnInit() override {
        auto* frame = new MainFrame();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(NoteApp);

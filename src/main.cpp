#include <wx/wx.h>
#include <wx/app.h>
#include "MainFrame.h"

class MyApp : public wxApp
{
public:
    virtual bool OnInit() wxOVERRIDE
    {
        MainFrame *frame = new MainFrame();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
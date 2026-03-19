#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>

class MainFrame : public wxFrame
{
public:
    MainFrame();

private:
    wxTextCtrl *inputText;
    wxTextCtrl *encodedText;
    wxTextCtrl *decodedText;
    wxTextCtrl *statsText;

    void OnProcess(wxCommandEvent &event);
};

#endif

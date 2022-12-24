#include <wx/wxprec.h>
#include <wx/filedlg.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

enum { ID_Hello = 1, MENU_Open };

class MRIViewerFrame : public wxFrame
{
public:
    MRIViewerFrame();
    wxString CurrentDocPath;
    wxTextCtrl *MainEditBox;

private:
    void openMenu(wxCommandEvent& event);
    void OnHello(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
};

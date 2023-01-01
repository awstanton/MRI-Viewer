#include <wx/wxprec.h>
#include <wx/filedlg.h>
#include <wx/notebook.h>
#include <wx/splitter.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

enum { ID_Hello = wxID_HIGHEST + 1, MENU_Open, IMAGEPANEL_Paint, TEXT_Main };

class MRIViewerFrame : public wxFrame
{
public:
    MRIViewerFrame();
    wxString currentDocPath;
    wxTextCtrl *mainEditBox;
    wxSplitterWindow *mainPanel;
//    wxNotebook *imagePanel;
//    wxNotebook *sidePanel;

private:
    void openMenu(wxCommandEvent& event);
    void OnHello(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
};

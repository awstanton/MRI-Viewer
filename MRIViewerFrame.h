#include <wx/wxprec.h>
#include <wx/filedlg.h>
#include <wx/notebook.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

enum { MENU_Open = wxID_HIGHEST + 1, IMAGEPANEL_Paint, TEXT_Main };

class MRIViewerFrame : public wxFrame
{
public:
    MRIViewerFrame();
    wxMenuBar *mainMenuBar;
    wxMenu *fileMenu;
    wxMenu *actionMenu;
    wxNotebook *mainNotebook;
    wxString currentDocPath;
//    wxTextCtrl *mainEditBox;
//    wxNotebook *imagePanel;
//    wxNotebook *sidePanel;

private:
    void openMenu(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void initMenu();
};

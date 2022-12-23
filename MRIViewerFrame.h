#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

enum { ID_Hello = 1 };

class MRIViewerFrame : public wxFrame
{
public:
    MRIViewerFrame();

private:
    void OnHello(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
};

#include <wx/wx.h>
#include <wx/menu.h>

/*
Class will be a frame that gets embedded into the top of the main frame
Will have buttons with following events:
- open file

Once a file is opened, if any issues, a message is displayed in the side panel
if successful, the first slice is shown in the canvas
when a file is being shown in the canvas, the menu changes to allow navigating through the slices


*/


class TopMenu : public wxFrame
{
public:
    TopMenu(const wxString& title);

    void OnQuit(wxCommandEvent& event);

    wxMenuBar *topMenuBar;
    wxMenu *topMenu;
};


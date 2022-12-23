#include "TopMenu.h"

TopMenu::TopMenu(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(300, 200))
{
    topMenuBar = new wxMenuBar;
    topMenu = new wxMenu;

    topMenu->Append(1, wxT("&Open File"));

    topMenuBar->Append(topMenu, wxT("&Files"));

    SetMenuBar(topMenuBar);

    Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(TopMenu::OnQuit));

    Centre();
}

void TopMenu::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

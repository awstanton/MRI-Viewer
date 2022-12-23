#include "MRIViewerFrame.h"


MRIViewerFrame::MRIViewerFrame() : wxFrame(NULL, wxID_ANY, "Hello World")
{
    wxMenu *fileMenu = new wxMenu;
    wxMenu *helpMenu = new wxMenu;
    wxMenu *mainMenu = new wxMenu;
    wxMenuBar *mainMenuBar = new wxMenuBar;

    fileMenu->Append(ID_Hello, "&Hello...\tCtrl-H", "Help string", wxITEM_NORMAL);
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_EXIT);

    helpMenu->Append(wxID_ABOUT);

    mainMenuBar->Append(fileMenu, "File");
    mainMenuBar->Append(helpMenu, "Help");

    SetMenuBar(mainMenuBar);

    mainMenu->Append(1, wxT("Open File"));
    mainMenuBar->Append(mainMenu, wxT("Files"));

    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");

    Bind(wxEVT_MENU, &MRIViewerFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MRIViewerFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MRIViewerFrame::OnExit, this, wxID_EXIT);
}


void MRIViewerFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void MRIViewerFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a hello world example", "About Hello World", wxOK | wxICON_INFORMATION);
}

void MRIViewerFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello from wxWidgets!");
}

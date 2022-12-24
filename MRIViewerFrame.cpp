#include "MRIViewerFrame.h"

void MRIViewerFrame::openMenu(wxCommandEvent& WXUNUSED(event)) {
    wxFileDialog* OpenDialog = new wxFileDialog(
		this, _("Choose a file to open"), wxEmptyString, wxEmptyString,
		wxT("Text files (*.txt)|*.txt|C++ Source Files (*.cpp, *.cxx)|*.cpp;*.cxx| C Source files (*.c)|*.c|C header files (*.h)|*.h"), wxFD_OPEN, wxDefaultPosition);
    if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
	{
		CurrentDocPath = OpenDialog->GetPath();
		// Sets our current document to the file the user selected
		MainEditBox->LoadFile(CurrentDocPath); //Opens that file
		SetTitle(wxString("Edit - ") << OpenDialog->GetFilename()); // Set the Title to reflect the file open
	}

	// Clean up after ourselves
	OpenDialog->Destroy();
}


MRIViewerFrame::MRIViewerFrame() : wxFrame(NULL, wxID_ANY, "Hello World")
{
    wxMenu *fileMenu = new wxMenu;
    wxMenu *mainMenu = new wxMenu;
    wxMenuBar *mainMenuBar = new wxMenuBar;

    fileMenu->Append(wxID_ABOUT);
    fileMenu->Append(wxID_EXIT);

    mainMenu->Append(wxID_OPEN, wxT("&Open File"));
    mainMenu->Bind(wxEVT_MENU, &MRIViewerFrame::openMenu, this, wxID_OPEN);


    mainMenuBar->Append(fileMenu, wxT("&File"));
    mainMenuBar->Append(mainMenu, wxT("Files"));

    SetMenuBar(mainMenuBar);

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

#include "MRIViewerFrame.h"

void MRIViewerFrame::openMenu(wxCommandEvent& WXUNUSED(event)) {
    wxFileDialog* OpenDialog = new wxFileDialog(
		this, wxT("Choose a file to open"), wxEmptyString, wxEmptyString,
		wxT("Text files (*.txt)|*.txt|C++ Source Files (*.cpp)|*.cpp| C Source files (*.c)|*.c|C header files (*.h)|*.h"),
        wxFD_OPEN, wxDefaultPosition);
    if (OpenDialog->ShowModal() == wxID_OK) {
		CurrentDocPath = OpenDialog->GetPath();
		MainEditBox->LoadFile(CurrentDocPath);
		SetTitle(wxString("Edit - ") << OpenDialog->GetFilename());
	}

	OpenDialog->Destroy();
	return;
}


MRIViewerFrame::MRIViewerFrame() : wxFrame(NULL, wxID_ANY, "MRI-Viewer", wxPoint(0, 0), wxSize(2450, 1000))
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
    wxMessageBox("Slice scroll, independent components analysis, and Fourier analysis", "About MRI-Viewer", wxOK | wxICON_INFORMATION);
}

void MRIViewerFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello from wxWidgets!");
}

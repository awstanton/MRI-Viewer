#include "MRIViewerFrame.h"
#include "NIFile.h"


MRIViewerFrame::MRIViewerFrame() : wxFrame(NULL, wxID_ANY, "MRI-Viewer")
{
    initMenu();

    mainNotebook = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, wxT("main panel"));
    NIFile(mainNotebook, wxT("splitter name"), wxT("tab name"), wxT("image name"), wxT("text name"));

    Maximize();
}


void MRIViewerFrame::initMenu() {
    mainMenuBar = new wxMenuBar;
    fileMenu = new wxMenu;
    actionMenu = new wxMenu;

    fileMenu->Append(wxID_ABOUT);
    fileMenu->Append(wxID_EXIT);

    actionMenu->Append(MENU_Open, wxT("&Open File"));

    mainMenuBar->Append(fileMenu, wxT("&File"));
    mainMenuBar->Append(actionMenu, wxT("Actions"));

    SetMenuBar(mainMenuBar);

    actionMenu->Bind(wxEVT_MENU, &MRIViewerFrame::openMenu, this, MENU_Open);
    fileMenu->Bind(wxEVT_MENU, &MRIViewerFrame::OnAbout, this, wxID_ABOUT);
    fileMenu->Bind(wxEVT_MENU, &MRIViewerFrame::OnExit, this, wxID_EXIT);
}


void MRIViewerFrame::openMenu(wxCommandEvent& WXUNUSED(event))
{
    wxFileDialog* OpenDialog = new wxFileDialog(
		this, wxT("Choose a file to open"), wxEmptyString, wxEmptyString,
		wxT("Text files (*.txt)|*.txt|C++ Source Files (*.cpp)|*.cpp| C Source files (*.c)|*.c|C header files (*.h)|*.h"),
        wxFD_OPEN, wxDefaultPosition);
    if (OpenDialog->ShowModal() == wxID_OK) {
//        NIFile *niFile = new NIFile(OpenDialog->GetPath());
//        mainSplitter->


		currentDocPath = OpenDialog->GetPath();
//		mainEditBox->LoadFile(currentDocPath);
		SetTitle(wxString("Edit - ") << OpenDialog->GetFilename());
	}
}

void MRIViewerFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void MRIViewerFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("Slice scroll, independent components analysis, and Fourier analysis", "About MRI-Viewer", wxOK | wxICON_INFORMATION);
}

#include "MRIViewerFrame.h"
#include "ImagePanel.h"

void MRIViewerFrame::openMenu(wxCommandEvent& WXUNUSED(event)) {
    wxFileDialog* OpenDialog = new wxFileDialog(
		this, wxT("Choose a file to open"), wxEmptyString, wxEmptyString,
		wxT("Text files (*.txt)|*.txt|C++ Source Files (*.cpp)|*.cpp| C Source files (*.c)|*.c|C header files (*.h)|*.h"),
        wxFD_OPEN, wxDefaultPosition);
    if (OpenDialog->ShowModal() == wxID_OK) {
		currentDocPath = OpenDialog->GetPath();
		mainEditBox->LoadFile(currentDocPath);
		SetTitle(wxString("Edit - ") << OpenDialog->GetFilename());
	}

	return;
}


MRIViewerFrame::MRIViewerFrame() : wxFrame(NULL, wxID_ANY, "MRI-Viewer")
{
    wxMenu *fileMenu = new wxMenu;
    wxMenu *actionMenu = new wxMenu;
    wxMenuBar *mainMenuBar = new wxMenuBar;

    mainPanel = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D, wxT("Main Panel"));

//    wxFrame *frame = new wxFrame(NULL, wxID_ANY, wxT("Hello wxDC"), wxPoint(50,50), wxSize(800,600));
    wxNotebook *sidePanel = new wxNotebook(mainPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, wxT("Side Panel"));
    ImagePanel *imagePanel = new ImagePanel(mainPanel, wxT("favicon.ico"), wxBITMAP_TYPE_ICO);
    mainPanel->SetSashGravity(0.5);
    mainPanel->SplitVertically(sidePanel, imagePanel, 0);

//    imagePanel = new wxNotebook(mainPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, wxT("Image Panel"));
//    wxPanel *testPanel1 = new wxPanel(imagePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, wxT("file 1 panel 1"));
//    wxPanel *testPanel2 = new wxPanel(imagePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, wxT("file 1 panel 2"));
//    wxPanel *testPanel3 = new wxPanel(imagePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, wxT("file 2 panel 1"));
//    wxPanel *testPanel4 = new wxPanel(imagePanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, wxT("file 2 panel 2"));
//
//    imagePanel->AddPage(testPanel1, wxT("file 1 panel 1"));
//    imagePanel->AddPage(testPanel2, wxT("file 1 panel 2"));

//    mainPanel->AddPage(imagePanel, wxT("image panel"));
//    mainPanel->AddPage(sidePanel, wxT("side panel"));
//    mainPanel->SetPageText(0, wxT("This is the main panel"));

    fileMenu->Append(wxID_ABOUT);
    fileMenu->Append(wxID_EXIT);

    actionMenu->Append(MENU_Open, wxT("&Open File"));
    actionMenu->Bind(wxEVT_MENU, &MRIViewerFrame::openMenu, this, MENU_Open);

    mainMenuBar->Append(fileMenu, wxT("&File"));
    mainMenuBar->Append(actionMenu, wxT("Actions"));

    SetMenuBar(mainMenuBar);

//    mainEditBox = new wxTextCtrl(
//		this, TEXT_Main, _("Hi!"), wxDefaultPosition, wxDefaultSize,
//		wxTE_MULTILINE | wxTE_RICH , wxDefaultValidator, wxTextCtrlNameStr);

    Bind(wxEVT_MENU, &MRIViewerFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MRIViewerFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MRIViewerFrame::OnExit, this, wxID_EXIT);

    Maximize();
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

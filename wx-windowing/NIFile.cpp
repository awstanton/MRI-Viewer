#include "NIFile.h"
#include "ImagePanel.h"

NIFile::NIFile(wxNotebook* parent, nifti_image* niiImage, const wxString& splitterName, const wxString& fileName, const wxString& tabName, const wxString& imageName, const wxString& textName)
{
    splitter = new wxSplitterWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D, splitterName);
    parent->AddPage(splitter, tabName);

    imageNotebook = new wxNotebook(splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, imageName);
    textNotebook = new wxNotebook(splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, textName);

    splitter->SetSashGravity(0.5);
    splitter->SplitVertically(textNotebook, imageNotebook, 0);

    image = new wxImage();
    image->SetData((unsigned char*) niiImage->data);

    ImagePanel *imagePanel = new ImagePanel(imageNotebook, image);
    imageNotebook->AddPage(imagePanel, "image panel");
}


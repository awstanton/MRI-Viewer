#include <wx/splitter.h>
#include <wx/notebook.h>
#include <wx/chartype.h>
#include <nifti2_io.h>


class NIFile
{
public:
    NIFile(wxNotebook* parent, nifti_image* niiImage, const wxString& splitterName, const wxString& fileName, const wxString& tabName, const wxString& imageName, const wxString& textName);
private:
    wxSplitterWindow *splitter;
    wxNotebook *imageNotebook;
    wxNotebook *textNotebook;
    wxImage *image;
};

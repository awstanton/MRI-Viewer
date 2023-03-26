#include <wx/wx.h>
#include <wx/sizer.h>
#include <nifti2_io.h>
#include <wx/image.h>


class ImagePanel : public wxPanel
{
    wxImage image;

public:
    ImagePanel(wxWindow* parent, wxImage* image);

    void paintEvent(wxPaintEvent& evt);
    void paintNow();
    void render(wxDC& dc);
};


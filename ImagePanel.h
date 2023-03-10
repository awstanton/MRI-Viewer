#include <wx/wx.h>
#include <wx/sizer.h>


class ImagePanel : public wxPanel
{
    wxImage image;

public:
    ImagePanel(wxWindow* parent, wxString file, wxBitmapType format);

    void paintEvent(wxPaintEvent& evt);
    void paintNow();
    void render(wxDC& dc);
};


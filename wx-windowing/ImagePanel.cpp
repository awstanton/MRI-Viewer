#include "ImagePanel.h"

ImagePanel::ImagePanel(wxWindow* parent, wxImage* image) : wxPanel(parent)
{
    Bind(wxEVT_PAINT, &ImagePanel::paintEvent, this);
//    image.LoadFile(file, format);
    Refresh(false);
}


void ImagePanel::paintEvent(wxPaintEvent& evt)
{
    wxPaintDC dc(this);
    render(dc);

}

void ImagePanel::paintNow()
{
    wxClientDC dc(this);
    render(dc);

}


void ImagePanel::render(wxDC& dc)
{
    dc.DrawBitmap(image, 0, 0, false);
}

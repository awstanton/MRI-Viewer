#include "ImagePanel.h"

ImagePanel::ImagePanel(wxWindow* parent, wxString file, wxBitmapType format) : wxPanel(parent)
{
    Bind(wxEVT_PAINT, &ImagePanel::paintEvent, this);
    image.LoadFile(file, format);
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

//BEGIN_EVENT_TABLE(ImagePanel, wxPanel)
//// some useful events
///*
// EVT_MOTION(wxImagePanel::mouseMoved)
// EVT_LEFT_DOWN(wxImagePanel::mouseDown)
// EVT_LEFT_UP(wxImagePanel::mouseReleased)
// EVT_RIGHT_DOWN(wxImagePanel::rightClick)
// EVT_LEAVE_WINDOW(wxImagePanel::mouseLeftWindow)
// EVT_KEY_DOWN(wxImagePanel::keyPressed)
// EVT_KEY_UP(wxImagePanel::keyReleased)
// EVT_MOUSEWHEEL(wxImagePanel::mouseWheelMoved)
// */
//
//// catch paint events
//EVT_PAINT(ImagePanel::paintEvent)
//END_EVENT_TABLE()

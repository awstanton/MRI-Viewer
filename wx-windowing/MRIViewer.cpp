#include "MRIViewer.h"
#include "MRIViewerFrame.h"

bool MRIViewer::OnInit()
{
    wxInitAllImageHandlers();
    MRIViewerFrame *frame = new MRIViewerFrame();
    frame->Show(true);
    SetTopWindow(frame);
    return true;
}

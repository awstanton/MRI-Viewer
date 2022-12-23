#include "MRIViewer.h"
#include "MRIViewerFrame.h"

bool MRIViewer::OnInit()
{
    MRIViewerFrame *frame = new MRIViewerFrame();
    frame->Show(true);
    return true;
}

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "gui.h"
#include "frame.h"

bool gui::OnInit() {
    frame *frame = new MyFrame();
    frame->Show(true);
    return true;
}
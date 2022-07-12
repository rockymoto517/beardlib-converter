#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "frame.h"
enum {ID_HELLO = 1}
frame::MyFrame():
    wxFrame(NULL, wxID_ANY, "Hello World") {
        wxMenu *menuFile = new wxMenu;
        menuFile->Append(ID_HELLO, "&Hello...\tCtrl-H", "Help string shown in status bar for this menu item");
        menuFile->AppendSeparator();
        menuFile->Append(wxID_EXIT);

        wxMenu *menuHelp = new wxMenu;
        menuHelp->Append(wxID_ABOUT);

        wxMenuBar *menuBar = new wxMenuBar;
        menuBar->Append(menuFile, "&File");
        menuBar->Append(menuHelp, "&Help");

        SetMenuBar(menuBar);

        CreateStatusBar();
        SetStatusText("Welcome to wxWidgets!");

        Bind(wxEVT_MENU, &frame::OnHello, this, ID_HELLO);
        Bind(wxEVT_Menu, &frame::OnAbout, this, wxID_ABOUT);
        Bind(wxEVT_MENU, &frame::OnExit, this, wxID_EXIT);
    }

void frame::OnExit(wxCommandEvent& event) {
    Close(true);
}

void frame::OnAbout(wxCommandEvent& event) {
    wxMessageBox("This is a wxWidgets Hello World example", "About Hello World", wxOK | wxICON_INFORMATION);
}

void frame::OnHello(wxCommandEvent& event) {
    wxLogMessage("Hello world from wxWidgets!");
}
#include "WindowEvents.h"
#include "MenuDesign.h"

void WindowEvents::OnFileOpen(wxCommandEvent& event){
	wxMessageBox(_T("title"), _T("content"));
}
void WindowEvents::OnClose(wxCommandEvent& event){
	Close(true);
}
void WindowEvents::OnAbout(wxCommandEvent& event){
	wxMessageBox(_("help content"), _("help"));
}
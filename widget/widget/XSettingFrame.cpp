#include <wx/wxprec.h>
#include "XSettingFrame.h"

XSettingFrame::XSettingFrame(wxWindow* parent) :wxFrame(parent, wxID_ANY, wxT("ÉèÖÃ"), wxDefaultPosition, \
	wxSize(400,300)) {
	this->SetIcon(wxIcon(wxT("icon.png"), wxBITMAP_TYPE_PNG));

}

XSettingFrame::~XSettingFrame() {
}
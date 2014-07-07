#include "XInitFrame.h"
#include "resources.h"
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/statbmp.h>



XInitFrame::XInitFrame() :wxFrame(NULL,wxID_ANY,"") {
	wxInitAllImageHandlers();

	this->SetWindowStyle(wxNO_BORDER | wxSTAY_ON_TOP);
	this->SetSize(wxSize(400, 300));
	this->SetIcon(wxIcon(PATH_ICON_PNG,wxBITMAP_TYPE_PNG));

	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	wxPanel* panel = new wxPanel(this);
	panel->SetSizer(sizer);
	panel->SetSize(wxSize(400, 300));
	wxImage img(PATH_INIT_JPG, wxBITMAP_TYPE_JPEG);
	img.Rescale(400, 300);
	wxStaticBitmap* bmp = new wxStaticBitmap(panel, wxID_ANY, wxBitmap(img), wxDefaultPosition, wxSize(400, 300));
	sizer->Add(bmp);

}


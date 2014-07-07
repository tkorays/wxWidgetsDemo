#include <wx/wxprec.h>
#include "XFrame.h"
#include <wx/image.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/statbmp.h>
#include "XSettingFrame.h"
#include "XInitFrame.h"

BEGIN_EVENT_TABLE(XFrame,wxFrame)

END_EVENT_TABLE()

XFrame::XFrame(wxSize size, wxString icon_png_, wxString title_) :\
wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, size) {
	this->SetWindowStyle(wxNO_BORDER);
	wxInitAllImageHandlers();
	title = title_;
	icon_png = icon_png_;
	this->SetIcon(wxIcon(icon_png, wxBITMAP_TYPE_PNG));


	// 代表整个窗口
	wxBoxSizer* master_sizer = new wxBoxSizer(wxVERTICAL); // 整个窗口的sizer
	wxPanel* master_panel = new wxPanel(this);
	master_panel->SetSize(size);
	master_panel->SetSizer(master_sizer);

	// 代表header
	wxBoxSizer* header_sizer = new wxBoxSizer(wxHORIZONTAL);
	wxPanel* header_panel = new wxPanel(master_panel);
	header_panel->SetBackgroundColour(wxColor(0, 122, 204));
	header_panel->SetSize(size.GetWidth(), 60);
	header_panel->SetSizer(header_sizer);
	header_panel->Connect(wxEVT_LEFT_DOWN,wxMouseEventHandler(XFrame::OnHeaderLeftDown),NULL,this);
	header_panel->Connect(wxEVT_MOTION, wxMouseEventHandler(XFrame::OnHeaderLeftDrag), NULL, this);
	header_panel->Connect(wxEVT_LEFT_UP, wxMouseEventHandler(XFrame::OnHeaderLeftUp), NULL, this);
	master_sizer->Add(header_panel, 0, wxEXPAND);

	// icon
	wxImage img(icon_png, wxBITMAP_TYPE_PNG);
	img.Rescale(30, 30);
	wxStaticBitmap* icon_bmp = new wxStaticBitmap(header_panel, wxID_ANY, wxBitmap(img),\
		wxPoint(24,15));
	header_sizer->Add(icon_bmp, 0, wxALIGN_LEFT);

	// caption
	wxStaticText* caption = new wxStaticText(header_panel, wxID_ANY, title, \
		wxPoint(70,20),wxSize(150,20));
	caption->SetForegroundColour(*wxWHITE);
	header_sizer->Add(caption, 0, wxALIGN_LEFT);

	/////////////////////////////////////
	// 菜单

	wxImage closeimg("close.png", wxBITMAP_TYPE_PNG);
	closeimg.Rescale(32, 32);
	wxStaticBitmap* close_btn = new wxStaticBitmap(header_panel, ID_CLOSE_BTN,wxBitmap(closeimg),\
		wxPoint(size.GetWidth()-60,14));
	close_btn->Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(XFrame::OnCloseBtn));
	header_sizer->Add(close_btn);

	wxImage settingimg("setting.png", wxBITMAP_TYPE_PNG);
	settingimg.Rescale(32, 32);
	wxStaticBitmap* setting_btn = new wxStaticBitmap(header_panel, ID_CLOSE_BTN, wxBitmap(settingimg), \
		wxPoint(size.GetWidth() - 110, 14));
	header_sizer->Add(setting_btn);
	setting_btn->Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(XFrame::OnSetting));

	wxImage autoimg("auto.png", wxBITMAP_TYPE_PNG);
	autoimg.Rescale(32, 32);
	wxStaticBitmap* auto_btn = new wxStaticBitmap(header_panel, ID_CLOSE_BTN, wxBitmap(autoimg), \
		wxPoint(size.GetWidth() - 160, 14));
	header_sizer->Add(auto_btn);

	wxImage userimg("user.png", wxBITMAP_TYPE_PNG);
	userimg.Rescale(32, 32);
	wxStaticBitmap* user_btn = new wxStaticBitmap(header_panel, ID_CLOSE_BTN, wxBitmap(userimg), \
		wxPoint(size.GetWidth() - 210, 14));
	header_sizer->Add(user_btn);

	//////////////////////////////////////////////////////////////////////
	// 代表主体
	main_sizer = new wxBoxSizer(wxHORIZONTAL);
	main_panel = new wxPanel(master_panel);
	main_panel->SetPosition(wxPoint(0, 60));
	main_panel->SetBackgroundColour(*wxWHITE);
	main_panel->SetSize(size.GetWidth(), size.GetHeight() - 110);
	main_panel->SetSizer(main_sizer);
	main_sizer->SetMinSize(wxSize(size.GetWidth(), size.GetHeight() - 110));
	master_sizer->Add(main_panel, 0, wxEXPAND);

	wxBoxSizer* left_sizer = new wxBoxSizer(wxVERTICAL);
	wxPanel* left_panel = new wxPanel(main_panel, wxID_ANY, wxDefaultPosition, wxSize(320,size.GetHeight() - 110));
	left_panel->SetSizer(left_sizer);
	left_panel->SetBackgroundColour(wxColor(32,32,32));
	main_sizer->Add(left_panel);

	wxPanel* left_top = new wxPanel(left_panel, wxID_ANY, wxDefaultPosition, wxSize(320, size.GetHeight() - 110 - 240));
	left_bottom = new wxPanel(left_panel, wxID_ANY, wxPoint(0, size.GetHeight() - 110 - 240), wxSize(320, 240));
	left_bottom->SetBackgroundColour(wxColor(32, 32, 32));
	left_sizer->Add(left_top);
	left_sizer->Add(left_bottom);

	wxBoxSizer* right_sizer = new wxBoxSizer(wxVERTICAL);
	wxPanel* right_panel = new wxPanel(main_panel, wxID_ANY, wxPoint(320,0), wxSize(size.GetWidth() - 320, size.GetHeight() - 110));
	right_panel->SetSizer(right_sizer);
	right_panel->SetBackgroundColour(*wxWHITE);
	main_sizer->Add(right_panel);



	// footer
	wxBoxSizer* footer_sizer = new wxBoxSizer(wxHORIZONTAL);
	wxPanel* footer_panel = new wxPanel(master_panel);
	footer_panel->SetBackgroundColour(wxColor(0, 122, 204));
	footer_panel->SetSize(size.GetWidth(), 50);
	footer_panel->SetPosition(wxPoint(0, size.GetHeight() - 50));
	footer_panel->SetSizer(footer_sizer);
	master_sizer->Add(footer_panel, 0, wxEXPAND);


	master_sizer->Fit(main_panel);

}

void XFrame::OnCloseBtn(wxMouseEvent& event) {
	Sleep(300);
	Close(true);
	exit(0);
}

void XFrame::OnHeaderLeftDown(wxMouseEvent& event) {
	//this->CaptureMouse();
	wxPoint pos = this->ClientToScreen(event.GetPosition());
	wxPoint origin = this->GetPosition();
	offset.x = pos.x - origin.y;
	offset.y = pos.y - origin.y;
}

void XFrame::OnHeaderLeftDrag(wxMouseEvent& event) {
	wxPoint pt = event.GetPosition();
	if (event.Dragging() && event.LeftIsDown()) {
		wxPoint pos = this->ClientToScreen(pt);
		this->Move(pos.x - offset.x, pos.y - offset.y);
	}
}

void XFrame::OnHeaderLeftUp(wxMouseEvent& event) {
	if (this->HasCapture()) {
		this->ReleaseMouse();
	}
}

void XFrame::OnSetting(wxMouseEvent& event) {
	setting_frame = new XSettingFrame(this);
	setting_frame->Show();
	setting_frame->SetPosition(wxPoint(100, 100));
}
#include <wx/wxprec.h>
#include <wx/app.h>
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/statbmp.h>
#include <wx/effects.h>
#include <wx/dc.h>
#include <wx/buffer.h>
#pragma warning(disable:4996)

#define ID_HEADER_PANEL 1
#define APP_WIN_WIDTH 1200
#define APP_WIN_HEIGHT 700

class MyApp : public wxApp {
public:
	virtual bool OnInit();
};
IMPLEMENT_APP(MyApp)

class MainFrame :public wxFrame {
private:
	
public:
	MainFrame();
	void DesignHeader(wxWindow* parent);
	DECLARE_EVENT_TABLE();
};

BEGIN_EVENT_TABLE(MainFrame,wxFrame)

END_EVENT_TABLE()


MainFrame::MainFrame() :wxFrame(NULL, wxID_ANY, "", wxDefaultPosition, wxSize(APP_WIN_WIDTH, APP_WIN_HEIGHT)) {
	this->SetWindowStyle(wxNO_BORDER); // 无border
	wxInitAllImageHandlers();
	this->SetIcon(wxIcon("icon.png", wxBITMAP_TYPE_PNG));

	//this->SetBackgroundStyle(wxBG_STYLE_CUSTOM);


	// 代表整个窗口
	wxBoxSizer* master_sizer = new wxBoxSizer(wxVERTICAL); // 整个窗口的sizer
	wxPanel* master_panel = new wxPanel(this);
	master_panel->SetSize(wxSize(APP_WIN_WIDTH, APP_WIN_HEIGHT));
	master_panel->SetSizer(master_sizer);
	
	
	/*
	wxBoxSizer* ss = new wxBoxSizer(wxHORIZONTAL);
	wxImage img("bg.png", wxBITMAP_TYPE_PNG);
	wxStaticBitmap* bitmap = new wxStaticBitmap(master_panel, wxID_ANY, wxBitmap(img));
	bitmap->SetSizer(ss);
	*/

	
	// 代表header
	wxBoxSizer* header_sizer = new wxBoxSizer(wxHORIZONTAL);
	wxPanel* header_panel = new wxPanel(master_panel);
	header_panel->SetBackgroundColour(wxColor(0,122,204));
	header_panel->SetSize(APP_WIN_WIDTH, 60);
	header_panel->SetSizer(header_sizer);
	master_sizer->Add(header_panel, 0, wxEXPAND);

	// 代表主体
	wxBoxSizer* main_sizer = new wxBoxSizer(wxHORIZONTAL);
	wxPanel* main_panel = new wxPanel(master_panel);
	main_panel->SetPosition(wxPoint(0, 60));
	main_panel->SetBackgroundColour(wxColor(255, 255, 255));
	main_panel->SetSize(APP_WIN_WIDTH, APP_WIN_HEIGHT-110);
	main_panel->SetSizer(main_sizer);
	master_sizer->Add(main_panel, 0, wxEXPAND);

	// footer
	wxBoxSizer* footer_sizer = new wxBoxSizer(wxHORIZONTAL);
	wxPanel* footer_panel = new wxPanel(master_panel);
	footer_panel->SetBackgroundColour(wxColor(0, 122, 204));
	footer_panel->SetSize(APP_WIN_WIDTH, 50);
	footer_panel->SetPosition(wxPoint(0, APP_WIN_HEIGHT - 50));
	footer_panel->SetSizer(footer_sizer);
	master_sizer->Add(footer_panel, 0, wxEXPAND);
	
	
	master_sizer->Fit(main_panel);
}
void MainFrame::DesignHeader(wxWindow* parent) {
	wxPanel* header_panel = new wxPanel(parent, ID_HEADER_PANEL, wxDefaultPosition, wxSize(50,0));
}


bool MyApp::OnInit() {
	MainFrame* mf = new MainFrame();
	mf->Center();
	mf->Show();
	return true;
}

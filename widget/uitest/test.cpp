#include <wx/wxprec.h>
#include <wx/app.h>
#include <XFrame.h>
#pragma comment(lib,"widget.lib")

class MyApp :public wxApp {
public:
	virtual  bool OnInit();
};
IMPLEMENT_APP(MyApp)
class MyFrame :public XFrame {
public:
	MyFrame();
};
MyFrame::MyFrame() :XFrame(wxSize(1200, 700), wxT("icon.png"), wxT("����������������")) {

}

bool MyApp::OnInit() {
	MyFrame* f = new MyFrame();
	f->Center();
	f->Show();
	return true;
}
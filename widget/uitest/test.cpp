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

	DECLARE_EVENT_TABLE();
};
MyFrame::MyFrame() :XFrame(wxSize(1200, 700), wxT("icon.png"), wxT("四轴飞行器控制面板")) {

}

BEGIN_EVENT_TABLE(MyFrame,XFrame)


END_EVENT_TABLE()

bool MyApp::OnInit() {
	MyFrame* f = new MyFrame();
	f->Center();
	f->SetTransparent(0);
	f->Show();
	for (int i = 0; i < 50; i++) {
		f->SetTransparent(i+206);
		Sleep(i / 10);
	}

	return true;
}
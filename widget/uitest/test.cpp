#include <wx/wxprec.h>
#include <wx/app.h>
#include <XFrame.h>
#include <wx/dcclient.h>
#pragma comment(lib,"widget.lib")
#include <opencv2/opencv.hpp>
#include <cv_link_all.h>
#include "helper.h"

HANDLE hVideo;
cv::VideoCapture cap;

class MyApp :public wxApp {
public:
	virtual  bool OnInit();
};
IMPLEMENT_APP(MyApp)
class MyFrame :public XFrame {
public:
	MyFrame();
	void OnCloseWindow(wxCloseEvent& event);
	

	DECLARE_EVENT_TABLE();
};
MyFrame::MyFrame() :XFrame(wxSize(1200, 700), wxT("icon.png"), wxT("四轴飞行器控制面板")) {
	
}
void MyFrame::OnCloseWindow(wxCloseEvent& event) {
	cap.release();
	CloseHandle(hVideo);
	Close(TRUE);
	exit(0);
}

BEGIN_EVENT_TABLE(MyFrame,XFrame)
EVT_CLOSE(MyFrame::OnCloseWindow)
END_EVENT_TABLE()

DWORD WINAPI video_test(void* data) {
	MyFrame* f = (MyFrame*)data;
	wxClientDC dc(f->left_bottom);
	cap.open(0);
	cv::Mat img;
	cap >> img;
	while (cap>>img,!img.empty()) {
		IplImage image = img.operator IplImage();
		wxImage wximg = wx_from_cv(&image);
		wximg.Rescale(320, 240);
		dc.DrawBitmap(wxBitmap(wximg), wxDefaultPosition);
	}
	
	return 0;
}

bool MyApp::OnInit() {
	
	MyFrame* f = new MyFrame();
	f->Center();
	f->SetTransparent(0);
	f->Show();
	for (int i = 0; i < 50; i++) {
		f->SetTransparent(i+206);
		Sleep(i / 10);
	}
	DWORD tid;
	hVideo = CreateThread(NULL, 0, video_test, f, 0, &tid);
	
	return true;
}